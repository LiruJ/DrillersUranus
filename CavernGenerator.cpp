#include "CavernGenerator.h"

// Data includes.
#include "Direction.h"

// Utility includes.
#include "Random.h"

/// <summary> Generates a cavern on the given map and sets the given start and end positions. </summary>
/// <param name="_map"> The map on which to generate. </param>
/// <param name="_start"> The spawn point game object. </param>
/// <param name="_end"> The exit point game object. </param>
void MapGeneration::CavernGenerator::Generate(WorldObjects::TileMap& _map, GameObjects::MapObject& _start, GameObjects::MapObject& _end)
{
	// Reset the map.
	_map.Reset();

	// Set the spawn point to a random cell on the map.
	_start.SetTilePosition(Point(Random::RandomBetween(1, _map.GetWidth() - 2), Random::RandomBetween(1, _map.GetHeight() - 2)));

	// Start at the spawn, work out the next position, and keep track of the map's centre.
	Point position = _start.GetTilePosition();
	Point nextPosition;
	Point mapCentre = Point(_map.GetWidth() / 2, _map.GetHeight() / 2);

	// Calculate the amount of floors desired and track how many floors have been placed.
	int32_t desiredFloors = _map.GetArea() * c_minPercentageOfMapToCarve + ((c_maxPercentageOfMapToCarve - c_minPercentageOfMapToCarve) * Random::RandomScalar());
	int32_t currentFloors = 0;
	
	// Keep carving away until the desired amount of floors are made.
	while (desiredFloors > currentFloors)
	{
		// If this cell is a wall, turn it into a random floor and increase the floor counter.
		if (_map.IsCellBlockedAndInRange(position)) { _map.FillCell(position, SpriteData::GetRandomFloor()); currentFloors++; }

		// Calculate the distance from the centre of the map, and scale the weight accordingly.
		Point distanceFromCentre = position - mapCentre;
		float centreChance = ((float)std::max(abs(distanceFromCentre.x), abs(distanceFromCentre.y)) / std::max(mapCentre.x, mapCentre.y)) * c_centreWeight;

		// Keep trying to move until a valid position is found.
		do
		{
			// Roll to move towards the centre of the map a bit more.
			if (position != mapCentre && Random::RandomScalar() < centreChance) { nextPosition = position + Direction::GetLookAt(position, mapCentre).GetNormal(); }

			// Otherwise go in a random direction.
			else { nextPosition = position + Direction::GetRandom().GetNormal(); }
		} while (!_map.IsCellInPlayableArea(nextPosition));

		// Move to the next position.
		position = nextPosition;
	}

	// Generate the gems.
	generateGems(_map);

	// Set the exit point to the end position and carve it out.
	_end.SetTilePosition(position);
	_map.FillCellWithRandomFloor(position);
}

/// <summary> Fills the map with random gems. </summary>
/// <param name="_map"> The map to fill. </param>
void MapGeneration::CavernGenerator::generateGems(WorldObjects::TileMap& _map)
{
	// Set the remaining prosperity based on the area of the map and average prosperity per cell.
	int32_t remainingProsperity = _map.GetArea() * c_averageProsperityPerCell;

	// Repeat until the remaining prosperity is 0.
	while (remainingProsperity > 0)
	{
		// Pick a random cell on the map, avoiding the edges.
		Point randomCell = Point(Random::RandomBetween(1, _map.GetWidth() - 2), Random::RandomBetween(1, _map.GetHeight() - 2));

		// If the cell has a wall, add some random prosperity to it.
		if (_map.IsCellBlockedAndInRange(randomCell))
		{
			// Make sure the prosperity doesn't overflow.
			int32_t prosperityToAdd = Random::RandomBetween(0, UCHAR_MAX - _map.GetTileAt(randomCell).m_prosperity);

			// Add the prosperity to the cell, then subtract that prosperity from the remaining prosperity.
			_map.SetCellProsperity(randomCell, prosperityToAdd);
			remainingProsperity -= prosperityToAdd;
		}
	}
}