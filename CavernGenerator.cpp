#include "CavernGenerator.h"
#include "Random.h"
#include "Direction.h"

void MapGeneration::CavernGenerator::Generate(TileMap& _map, MapObject& _start, MapObject& _end)
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
	int desiredFloors = _map.GetArea() * c_minPercentageOfMapToCarve + ((c_maxPercentageOfMapToCarve - c_minPercentageOfMapToCarve) * Random::RandomScalar());
	int currentFloors = 0;
	
	// Keep carving away until the desired amount of floors are made.
	while (desiredFloors > currentFloors)
	{
		// If this cell is a wall, turn it into a random floor and increase the floor counter.
		if (_map.CellIsBlockedAndInRange(position)) { _map.FillCell(position, SpriteData::GetRandomFloor()); currentFloors++; }

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
		} while (!_map.CellInPlayableArea(nextPosition));

		// Move to the next position.
		position = nextPosition;
	}

	// Generate the gems.
	generateGems(_map);

	// Set the exit point to the end position and carve it out.
	_end.SetTilePosition(position);
	_map.FillCellWithRandomFloor(position);
}

void MapGeneration::CavernGenerator::generateGems(TileMap& _map)
{
	// Set the remaining prosperity based on the area of the map and average prosperity per cell.
	int remainingProsperity = _map.GetArea() * c_averageProsperityPerCell;

	// Repeat until the remaining prosperity is 0.
	while (remainingProsperity > 0)
	{
		// Pick a random cell on the map, avoiding the edges.
		Point randomCell = Point(Random::RandomBetween(1, _map.GetWidth() - 2), Random::RandomBetween(1, _map.GetHeight() - 2));

		// If the cell has a wall, add some random prosperity to it.
		if (_map.CellIsBlockedAndInRange(randomCell))
		{
			// Make sure the prosperity doesn't overflow.
			int prosperityToAdd = Random::RandomBetween(0, UCHAR_MAX - _map.GetTileProsperityAt(randomCell));

			// Add the prosperity to the cell, then subtract that prosperity from the remaining prosperity.
			_map.SetCellProsperity(randomCell, prosperityToAdd);
			remainingProsperity -= prosperityToAdd;
		}
	}
}