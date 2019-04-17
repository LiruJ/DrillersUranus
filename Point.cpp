#include "Point.h"

/// <summary> Gets every <see cref="Point"/> covered by a line going from the start to the end positions. </summary>
/// <param name="_start"> The start position. </param>
/// <param name="_end"> The end position. </param>
/// <returns> A list of points covered by a line between the given start and end positions. </returns>
std::vector<Point> Point::getCoveredPoints(const Vector2 _start, const Vector2 _end)
{
	// Makes a new list for the visited cell positions.
	std::vector<Point> visitedCells;

	// The distance between the start and end positions.
	float_t xDist = abs((_start - _end).x);
	float_t yDist = abs((_start - _end).y);

	// How many grid tiles to check based on the distance.
	uint16_t steps = 1 + xDist + yDist;

	// If the end position is to the right of the start, increment right, otherwise go left.
	int8_t xInc = (_end.x > _start.x) ? 1 : -1;
	int8_t yInc = (_end.y > _start.y) ? 1 : -1;

	// Error is positive when the closest tile is on the x axis and negative on the y axis.
	float_t error = xDist - yDist;

	// The X and Y to change, begins at the start position.
	float_t x = _start.x;
	float_t y = _start.y;

	// Visits every point between the start and end positions.
	for (; steps > 0; --steps)
	{
		// Add this point to the list of points.
		visitedCells.push_back(Point(x, y));

		// If error is positive, go right and decrease error by the y distance. This eventually causes error to be negative.
		if (error > 0)
		{
			x += xInc;
			error -= yDist;
		}
		else
		{
			y += yInc;
			error += xDist;
		}
	}

	// Return the final list.
	return visitedCells;
}
