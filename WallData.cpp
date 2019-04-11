#include "WallData.h"

// Data includes.
#include "Direction.h"

// Utility includes.
#include "Random.h"

/// <summary> Creates a new <see cref="WallData"/> with the given width and height. </summary>
/// <param name="_width"> The width of the data. </param>
/// <param name="_height"> The height of the data. </param>
Minigames::WallData::WallData(const uint8_t _width, const uint8_t _height) : m_width(_width), m_height(_height), m_bounds(0, 0, _width, _height)
{
	// Initialise the rows and columns.
	m_data = std::vector<std::vector<uint8_t>>(m_width);
	for (int32_t x = 0; x < m_width; x++) { m_data[x] = std::vector<uint8_t>(m_height); }
}

/// <summary> Generates a random cave wall. </summary>
void Minigames::WallData::Generate()
{
	// Reset the data to the minimum value.
	reset();

	// Create a random number of bumps.
	uint8_t numberOfBumps = Random::RandomBetween(4, 6);
	for (int32_t i = 0; i < numberOfBumps; i++) { generateBump((c_maxValue - numberOfBumps) + i); }
}

/// <summary> Resets the data to the minimum value. </summary>
void Minigames::WallData::reset()
{
	for (int32_t x = 0; x < m_width; x++)
	{
		for (int32_t y = 0; y < m_height; y++)
		{
			m_data[x][y] = c_minValue;
		}
	}
}

/// <summary> Generates a random bump on the cave wall from the given height. </summary>
/// <param name="_height"> The starting height of the bump. </param>
void Minigames::WallData::generateBump(const uint8_t _height)
{
	// Set the current height to the given height.
	uint8_t currentHeight = _height;

	// Much like the cavern generation, start at a random place and randomly move around.
	Point currentPosition(Random::RandomBetween(0, m_width - 1), Random::RandomBetween(0, m_height - 1));
	Point nextPosition;

	// Every time a placement cannot be made, increment this by 1 to prevent an infinite loop.
	int32_t currentAttempts = 0;

	// Keep going until a certain height is reached.
	while (currentHeight > c_minValue && currentAttempts < c_maxAttempts)
	{
		// Only set the tile if it is lower than the current height, otherwise increment the attempt counter.
		if (m_data[currentPosition.x][currentPosition.y] < currentHeight)
		{
			// Set the tile.
			m_data[currentPosition.x][currentPosition.y] = currentHeight;

			// Roll to go down one layer and reset the attempt counter.
			if (Random::RandomScalar() < c_downChance && currentHeight > 0) { currentHeight--; currentAttempts = 0; }
		}
		else { currentAttempts++; }

		// Keep going in a random direction until a valid move is found.
		do { nextPosition = currentPosition + Direction::GetRandom().GetNormal(); } while (!m_bounds.IsPointInside(nextPosition));

		// Make the move.
		currentPosition = nextPosition;
	}
}
