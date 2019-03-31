#include "DungeonGenerator.h"
#include "Random.h"

#include <queue>

void MapGeneration::DungeonGenerator::Generate(TileMap& _map, MapObject& _start, MapObject& _end)
{
	// Set the map to the given map.
	m_map = &_map;

	m_map->Reset();

	placeRooms(c_roomAmount, _end);

	generateMaze(_start);

	breakWalls();

	removeDeadEnds(_start);

	generateGems();
}

void MapGeneration::DungeonGenerator::placeRooms(const unsigned char _numberOfRooms, MapObject& _end)
{
	// Place the given amount of rooms.
	for (int room = 0; room < _numberOfRooms; room++)
	{
		// Keep trying to place the room until no more attempts can be made.
		for (int attempt = 0; attempt < c_maxRoomAttempts; attempt++)
		{
			// Randomise the width and height of the room, ensuring they are odd.
			int width = Random::RandomBetween(c_minRoomWidth, c_maxRoomWidth);
			int height = Random::RandomBetween(c_minRoomHeight, c_maxRoomHeight);
			if (width % 2 == 0)		{ width--; }
			if (height % 2 == 0)	{ height--; }

			// Randomises the position, ensuring there are at least 3 cells between the room and the sides of the map and are odd.
			int x = Random::RandomBetween(3, m_map->GetWidth() - width - 3);
			int y = Random::RandomBetween(3, m_map->GetHeight() - height - 3);
			if (x % 2 == 0)			{ x--; }
			if (y % 2 == 0)			{ y--; }
			
			// If the area is clear, create a room here.
			if (m_map->AreaIsBlocked(Point(x - 1, y - 1), Point(width + 1, height + 1)))
			{
				// Fill the area with a floor.
				m_map->FillAreaWithRandomFloor(Point(x, y), Point(width, height));

				// If the exit point has not been set yet, set it to a random point within the room, away from any walls.
				if (_end.GetTilePosition() == Point(0, 0)) { _end.SetTilePosition(Point(Random::RandomBetween(x + 1, x + width - 1), Random::RandomBetween(y + 1, y + height - 1))); }

				// Break out of the attempt loop.
				break;
			}
		}
	}
}

void MapGeneration::DungeonGenerator::generateMaze(MapObject& _start)
{
	// Start at a random side of the map.
	Direction startingDirection = Direction::GetRandom();

	// The position whence the maze starts.
	int spawnX, spawnY;

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

void MapGeneration::DungeonGenerator::removeDeadEnds(MapObject& _spawn)
{
	// Create a vector to store the positions of the dead ends.
	std::vector<Point> deadEnds(0);

	// Go over every cell and add every dead end to the vector.
	for (int x = 0; x < m_map->GetWidth(); x++)
	{
		for (int y = 0; y < m_map->GetHeight(); y++)
		{
			if (cellIsDeadEnd(Point(x, y), _spawn)) { deadEnds.push_back(Point(x, y)); }
		}
	}

	// Shuffle the dead ends vector.
	std::random_shuffle(deadEnds.begin(), deadEnds.end());

	// Calculate how many corridors must be left.
	unsigned int corridorsToLeave = m_corridorAmount * c_percentageOfCorridorsToLeave;

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
		if (cellIsDeadEnd(deadEnd + Direction(Directions::Left).GetNormal(), _spawn))	deadEnds.push_back(deadEnd + Direction(Directions::Left).GetNormal());
		if (cellIsDeadEnd(deadEnd + Direction(Directions::Up).GetNormal(), _spawn))		deadEnds.push_back(deadEnd + Direction(Directions::Up).GetNormal());
		if (cellIsDeadEnd(deadEnd + Direction(Directions::Right).GetNormal(), _spawn))	deadEnds.push_back(deadEnd + Direction(Directions::Right).GetNormal());
		if (cellIsDeadEnd(deadEnd + Direction(Directions::Down).GetNormal(), _spawn))	deadEnds.push_back(deadEnd + Direction(Directions::Down).GetNormal());
	}
}

void MapGeneration::DungeonGenerator::breakWalls()
{
	// Create a vector to store the breakable walls.
	std::vector<Point> breakableWalls(0);

	// Go over every cell, leaving a 1 thick border, and add every breakable wall to the vector.
	for (int x = 1; x < m_map->GetWidth() - 1; x++)
	{
		for (int y = 1; y < m_map->GetHeight() -1; y++)
		{
			if (getAdjacentFloorCellsAmount(Point(x, y)) > 1) { breakableWalls.push_back(Point(x, y)); }
		}
	}

	// Shuffle the breakable walls vector.
	std::random_shuffle(breakableWalls.begin(), breakableWalls.end());

	// Calculate how many walls to break.
	int wallsToBreak = breakableWalls.size() * c_percentageOfWallsToBreak;
	int brokenWalls = 0;

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

void MapGeneration::DungeonGenerator::generateGems()
{
	// Set the remaining prosperity based on the area of the map and average prosperity per cell.
	int remainingProsperity = m_map->GetArea() * c_averageProsperityPerCell;

	// Repeat until the remaining prosperity is 0.
	while (remainingProsperity > 0)
	{
		// Pick a random cell on the map.
		Point randomCell = Point(Random::RandomBetween(1, m_map->GetWidth() - 2), Random::RandomBetween(1, m_map->GetHeight() - 2));

		// If the cell has a wall, add some random prosperity to it.
		if (m_map->CellIsBlockedAndInRange(randomCell)) 
		{
			// Make sure the prosperity doesn't overflow.
			int prosperityToAdd = Random::RandomBetween(0, UCHAR_MAX - m_map->GetTileProsperityAt(randomCell));

			// Add the prosperity to the cell, then subtract that prosperity from the remaining prosperity.
			m_map->SetCellProsperity(randomCell, prosperityToAdd);
			remainingProsperity -= prosperityToAdd;
		}
	}
}

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

bool MapGeneration::DungeonGenerator::isCellValidMazeNode(const Point _position)
{
	// If the cell is out of range, it is invalid, so return false.
	if (!m_map->CellInRange(_position)) { return false; }

	// If any of the adjacent cells are clear, this cell is invalid, so return false; otherwise return true.
	return	!(m_map->CellIsClearAndInRange(_position + Direction(Directions::Left).GetNormal()) || m_map->CellIsClearAndInRange(_position + Direction(Directions::Right).GetNormal())
			|| m_map->CellIsClearAndInRange(_position + Direction(Directions::Down).GetNormal()) || m_map->CellIsClearAndInRange(_position + Direction(Directions::Up).GetNormal()));
}

int MapGeneration::DungeonGenerator::getAdjacentFloorCellsAmount(const Point _position)
{
	// Keep track of the amount of empty sides.
	unsigned char emptySideAmount = 0;

	// For each empty side, increase the counter by 1.
	if (m_map->CellIsClearAndInRange(_position + Direction(Directions::Left).GetNormal()))	{ emptySideAmount++; }
	if (m_map->CellIsClearAndInRange(_position + Direction(Directions::Up).GetNormal()))		{ emptySideAmount++; }
	if (m_map->CellIsClearAndInRange(_position + Direction(Directions::Right).GetNormal()))	{ emptySideAmount++; }
	if (m_map->CellIsClearAndInRange(_position + Direction(Directions::Down).GetNormal()))	{ emptySideAmount++; }

	// return the amount of empty sides.
	return emptySideAmount;
}
