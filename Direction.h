#ifndef DIRECTION_H
#define DIRECTION_H

#include "Point.h"
#include "Random.h"

#include <cstdlib>

// Forward declaration.
struct Direction;

enum Directions : char
{
	None = -1, Left, Up, Right, Down
};

struct Direction
{
	Direction(Directions _value) : m_value(_value) { }

	Directions m_value;

	bool operator==(const Direction& _other) const { return m_value == _other.m_value; }
	bool operator!=(const Direction& _other) const { return m_value != _other.m_value; }

	bool operator==(const Directions& _other) const { return m_value == _other; }
	bool operator!=(const Directions& _other) const { return m_value != _other; }

	inline Direction GetOpposite() const
	{
		switch (m_value)
		{
		case Left:	{ return Directions::Right; }
		case Up:	{ return Directions::Down; }
		case Right: { return Directions::Left; }
		case Down:	{ return Directions::Up; }
		case None:	{ return Directions::None; }
		default:	{ return Directions::None; }
		}
	}

	inline Direction GetLeft() const
	{
		switch (m_value)
		{
		case Left: { return Directions::Down; }
		case Up: { return Directions::Left; }
		case Right: { return Directions::Up; }
		case Down: { return Directions::Right; }
		case None: { return Directions::None; }
		default: { return Directions::None; }
		}
	}

	inline Direction GetRight() const
	{
		switch (m_value)
		{
		case Left: { return Directions::Up; }
		case Up: { return Directions::Right; }
		case Right: { return Directions::Down; }
		case Down: { return Directions::Left; }
		case None: { return Directions::None; }
		default: { return Directions::None; }
		}
	}

	inline Point GetNormal() const
	{
		switch (m_value)
		{
		case Left:	{ return Point(-1, 0); }
		case Up:	{ return Point(0, -1); }
		case Right: { return Point(1, 0); }
		case Down:	{ return Point(0, 1); }
		case None:	{ return Point(); }
		default:	{ return Point(); }
		}
	}

	inline static Direction GetRandom() { return Direction((Directions)Random::RandomBetween(0, 3)); }

	inline static Direction GetLookAt(const Point _position, const Point _lookAt)
	{
		// Calculate the difference between the points, if there is none, throw an error.
		Point difference = _position - _lookAt;
		if (difference.x == 0 && difference.y == 0) throw std::exception("Cannot look at self.");

		// Return based on the difference.
		if (difference.x <= 0 && difference.y <= 0)			return (difference.x < difference.y)		? Direction(Directions::Right)	: Direction(Directions::Down);
		else if (difference.x <= 0 && difference.y >= 0)	return (abs(difference.x) > difference.y)	? Direction(Directions::Right)	: Direction(Directions::Up);
		else if (difference.x >= 0 && difference.y <= 0)	return (difference.x > abs(difference.y))	? Direction(Directions::Left)	: Direction(Directions::Down);
		else												return (difference.x > difference.y)		? Direction(Directions::Left)	: Direction(Directions::Up);
	}
};
#endif