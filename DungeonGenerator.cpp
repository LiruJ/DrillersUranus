#include "DungeonGenerator.h"

// Data includes.
#include "Rectangle.h"

// Utility includes.
#include "Random.h"
#include <queue>

/// <summary> Generates a dungeno on the given map and sets the given start and end positions. </summary>
/// <param name="_map"> The map on which to generate. </param>
/// <param name="_start"> The spawn point game object. </param>
/// <param name="_end"> The exit point game object. </param>
void MapGeneration::DungeonGenerator::Generate(WorldObjects::TileMap& _map, GameObjects::MapObject& _start, GameObjects::MapObject& _end)
{
	// Set the map reference to the given map and reset it.
	m_map = &_map;
	m_map->Reset();

	// These functions are pretty self-explanatory.
	placeRooms(c_roomAmount, _end);
	generateMaze(_start);
	breakWalls();
	removeDeadEnds(_start.GetTilePosition());
	generateGems();
}

/// <summary> Places the given amount of rooms, and the given exit point in one of them. </summary>
/// <param name="_numberOfRooms"> The amount of rooms to place. </param>
/// <param name="_end"> The exit point. </param>
void MapGeneration::DungeonGenerator::placeRooms(const uint8_t _numberOfRooms, GameObjects::MapObject& _end)
{
	// Place the given amount of rooms.
	for (int32_t room = 0; room < _numberOfRooms; room++)
	{
		// Keep trying to place the room until no more attempts can be made.
		for (int32_t attempt = 0; attempt < c_maxRoomAttempts; attempt++)
		{
			// Randomise the width and height of the room, ensuring they are odd.
			int32_t width = Random::RandomBetween(c_minRoomWidth, c_maxRoomWidth);
			int32_t height = Random::RandomBetween(c_minRoomHeight, c_maxRoomHeight);
			if (width % 2 == 0)		{ width--; }
			if (height % 2 == 0)	{ height--; }

			// Randomises the position, ensuring there are at least 3 cells between the room and the sides of the map and are odd.
			int32_t x = Random::RandomBetween(3, m_map->GetWidth() - width - 3);
			int32_t y = Random::RandomBetween(3, m_map->GetHeight() - height - 3);
			if (x % 2 == 0)			{ x--; }
			if (y % 2 == 0)			{ y--; }
			
			// If the area is clear, create a room here.
			if (m_map->AreaIsBlocked(Rectangle(x - 1, y - 1, width + 1, height + 1)))
			{
				// Fill the area with a floor.
				m_map->FillAreaWithRandomFloor(Rectangle(x, y, width, height));

				// If the exit point has not been set yet, set it to a random point within the room, away from any walls.
				if (_end.GetTilePosition() == Point(0, 0)) { _end.SetTilePosition(Point(Random::RandomBetween(x + 1, x + width - 1), Random::RandomBetween(y + 1, y + height - 1))); }

				// Break out of the attempt loop.
				break;
			}
		}
	}
}

/// <summary> Generates a maze that fills the map from the given start. </summary>
/// <param name="_start"> The spawn game object. </param>
void MapGeneration::DungeonGenerator::generateMaze(GameObjects::MapObject& _start)
{
	// Start at a random side of the map.
	Direction startingDirection = Direction::GetRandom();

	// The position whence the maze starts.
	int32_t spawnX, spawnY;

	// If the side is left or right.
	if (startingDirection == Directions::Left || startingDirection == Directions::Right)
	{
		// Chooses a random Y position from which to start, and ensures it's odd.
		spawnY = Random::RandomBetween(1, m_map->GetHeight() - 2);
		if (spawnY % 2 == 0) spawnY--;

		// Sets the X of the spawn based the starting direction.
		spawnX = (startingDirection == Directions::Left) ? 0 : m_map->GetWidth() - 1;
	}
	else
	{
		// Chooses a random X position from which to start, and ensures it's odd.
		spawnX = Random::RandomBetween(1, m_map->GetWidth() - 2);
		if (spawnX % 2 == 0) spawnX--;

		// Sets the Y of the spawn based on the starting direction.
		spawnY = (startingDirection == Directions::Up) ? 0 : m_map->GetHeight() - 1;
	}

	// Set the spawn point.
	_start.SetTilePosition(Point(spawnX, spawnY));

	// Starts the recursive visit function from the spawn.
	visitCell(Point(spawnX, spawnY) + startingDirection.GetOpposite().GetNormal(), startingDirection);
}

/// <summary> Removes a certain amount of dead ends from the map, excluding the spawn. </summary>
/// <param name="_spawn"> The spawn position. </param>
void MapGeneration::DungeonGenerator::removeDeadEnds(const Point _spawnPosition)
{
	// Create a vector to store the positions of the dead ends.
	std::vector<Point> deadEnds(0);

	// Go over every cell and add every dead end to the vector.
	for (int32_t x = 0; x < m_map->GetWidth(); x++)
	{
		for (int32_t y = 0; y < m_map->GetHeight(); y++)
		{
			if (isCellDeadEnd(Point(x, y), _spawnPosition)) { deadEnds.push_back(Point(x, y)); }
		}
	}

	// Shuffle the dead ends vector.
	std::random_shuffle(deadEnds.begin(), deadEnds.end());

	// Calculate how many corridors must be left.
	uint32_t corridorsToLeave = m_corridorAmount * c_percentageOfCorridorsToLeave;

	// Keep adding walls until there are no dead ends left or the desired amount of corridors are left.
	while (m_corridorAmount > corridorsToLeave && !deadEnds.empty())
	{
		// Gets the current dead end and pops it off the vector.
		Point deadEnd = deadEnds.back();
		deadEnds.pop_back();

		// Sets this dead end to a wall and decrements the corridor count.
		m_map->FillCell(deadEnd, SpriteData::GetRandomPlainWall());
		m_corridorAmount--;
		
		// Check to see if the removal of this dead end created any more, and add them to the vector.
		if (isCellDeadEnd(deadEnd + Direction(Directions::Left).GetNormal(),	_spawnPosition)) deadEnds.push_back(deadEnd + Direction(Directions::Left).GetNormal());
		if (isCellDeadEnd(deadEnd + Direction(Directions::Up).GetNormal(),		_spawnPosition)) deadEnds.push_back(deadEnd + Direction(Directions::Up).GetNormal());
		if (isCellDeadEnd(deadEnd + Direction(Directions::Right).GetNormal(),	_spawnPosition)) deadEnds.push_back(deadEnd + Direction(Directions::Right).GetNormal());
		if (isCellDeadEnd(deadEnd + Direction(Directions::Down).GetNormal(),	_spawnPosition)) deadEnds.push_back(deadEnd + Direction(Directions::Down).GetNormal());
	}
}

/// <summary> Breaks a certain amount of walls that have at least one empty side. </summary>
void MapGeneration::DungeonGenerator::breakWalls()
{
	// Create a vector to store the breakable walls.
	std::vector<Point> breakableWalls(0);

	// Go over every cell, leaving a 1 thick border, and add every breakable wall to the vector.
	for (int32_t x = 1; x < m_map->GetWidth() - 1; x++)
	{
		for (int32_t y = 1; y < m_map->GetHeight() -1; y++)
		{
			if (getAdjacentFloorCellsAmount(Point(x, y)) > 1) { breakableWalls.push_back(Point(x, y)); }
		}
	}

	// Shuffle the breakable walls vector.
	std::random_shuffle(breakableWalls.begin(), breakableWalls.end());

	// Calculate how many walls to break.
	int32_t wallsToBreak = breakableWalls.size() * c_percentageOfWallsToBreak;
	int32_t brokenWalls = 0;

	// Keeps breaking walls until the limit is reached or no more breakable walls are left.
	while (wallsToBreak > brokenWalls && !breakableWalls.empty())
	{
		// Gets the current breakable wall and pops it off the vector.
		Point breakableWall = breakableWalls.back();
		breakableWalls.pop_back();

		// Sets this wall to a floor and increases the broken walls count.
		m_map->FillCell(breakableWall, SpriteData::GetRandomFloor());
		brokenWalls++;
	}
}

/// <summary> Fills the map with random gems. </summary>
void MapGeneration::DungeonGenerator::generateGems()
{
	// Set the remaining prosperity based on the area of the map and average prosperity per cell.
	int32_t remainingProsperity = m_map->GetArea() * c_averageProsperityPerCell;

	// Repeat until the remaining prosperity is 0.
	while (remainingProsperity > 0)
	{
		// Pick a random cell on the map.
		Point randomCell = Point(Random::RandomBetween(1, m_map->GetWidth() - 2), Random::RandomBetween(1, m_map->GetHeight() - 2));

		// If the cell has a wall, add some random prosperity to it.
		if (m_map->IsCellBlockedAndInRange(randomCell)) 
		{
			// Make sure the prosperity doesn't overflow.
			int32_t prosperityToAdd = Random::RandomBetween(0, UCHAR_MAX - m_map->GetTileAt(randomCell).m_prosperity);

			// Add the prosperity to the cell, then subtract that prosperity from the remaining prosperity.
			m_map->SetCellProsperity(randomCell, prosperityToAdd);
			remainingProsperity -= prosperityToAdd;
		}
	}
}

/// <summary> Visits the given cell from the given direction in order to carve it out as a cave corridor. </summary>
/// <param name="_position"> The position to visit. </param>
/// <param name="_from"> The direction whence the visit came. </param>
void MapGeneration::DungeonGenerator::visitCell(const Point _position, const Direction _from)
{
	// If this cell is invalid, return straight away.
	if (!isCellValidMazeNode(_position)) { return; }

	// Turn this cell and the cell behind it into a floor.
	m_map->FillCell(_position, SpriteData::GetRandomFloor());
	m_map->FillCell(_position + _from.GetNormal(), SpriteData::GetRandomFloor());

	// 2 corridors were made, so increase the count by 2.
	m_corridorAmount += 2;

	// Create a queue to hold the next possible moves.
	std::queue<Direction> possibleDirections = std::queue<Direction>();

	// Get the direction facing forwards.
	Direction to = _from.GetOpposite();

	// Roll to go left, right, or straight first.
	float leftRoll = Random::RandomScalar();
	float straightRoll = Random::RandomScalar();

	// If the straight roll was successful, add it first.
	if (straightRoll > c_chanceToBend) { possibleDirections.push(to); }

	// Add the left and right based on the roll.
	possibleDirections.push(((leftRoll > 50) ? to.GetLeft() : to.GetRight()));
	possibleDirections.push(((leftRoll > 50) ? to.GetRight() : to.GetLeft()));

	// If the straight roll was unsuccessful, add it last.
	if (straightRoll <= c_chanceToBend) { possibleDirections.push(to); }

	// Visit each cell in the rolled order.
	while (!possibleDirections.empty())
	{
		// Visit the cell then pop it off the queue.
		visitCell(_position + possibleDirections.front().GetNormal() * 2, possibleDirections.front().GetOpposite());
		possibleDirections.pop();
	}
}

/// <summary> Finds if the given position is valid for the maze. </summary>
/// <param name="_position"> The position to check. </param>
/// <returns> <c>true</c> if the maze can use this cell; otherwise, <c>false</c>. </returns>
bool MapGeneration::DungeonGenerator::isCellValidMazeNode(const Point _position)
{
	// If the cell is out of range, it is invalid, so return false.
	if (!m_map->IsCellInRange(_position)) { return false; }

	// If any of the adjacent cells are clear, this cell is invalid, so return false; otherwise return true.
	return	!(m_map->IsCellClearAndInRange(_position + Direction(Directions::Left).GetNormal()) || m_map->IsCellClearAndInRange(_position + Direction(Directions::Right).GetNormal())
			|| m_map->IsCellClearAndInRange(_position + Direction(Directions::Down).GetNormal()) || m_map->IsCellClearAndInRange(_position + Direction(Directions::Up).GetNormal()));
}

/// <summary> Gets the amount of floors adjacent to the given position. </summary>
/// <param name="_position"> The position to check. </param>
/// <returns> The number of adjacent floors to the given position. </returns>
int32_t MapGeneration::DungeonGenerator::getAdjacentFloorCellsAmount(const Point _position)
{
	// Keep track of the amount of empty sides.
	uint8_t emptySideAmount = 0;

	// For each empty side, increase the counter by 1.
	if (m_map->IsCellClearAndInRange(_position + Direction(Directions::Left).GetNormal()))	{ emptySideAmount++; }
	if (m_map->IsCellClearAndInRange(_position + Direction(Directions::Up).GetNormal()))		{ emptySideAmount++; }
	if (m_map->IsCellClearAndInRange(_position + Direction(Directions::Right).GetNormal()))	{ emptySideAmount++; }
	if (m_map->IsCellClearAndInRange(_position + Direction(Directions::Down).GetNormal()))	{ emptySideAmount++; }

	// return the amount of empty sides.
	return emptySideAmount;
}
