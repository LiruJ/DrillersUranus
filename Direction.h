#ifndef DIRECTION_H
#define DIRECTION_H

// Data includes.
#include "Point.h"

// Typedef includes.
#include <cstdlib>

// Utility includes.
#include "Random.h"

// Forward declaration.
struct Direction;

/// <summary> Represents a direction. </summary>
enum Directions { None = -1, Left, Up, Right, Down };

/// <summary> Represents a direction with various functions. </summary>
struct Direction
{
	/// <summary> The underlying <see cref="Directions"/> value. </summary>
	Directions m_value;

	/// <summary> Creates a new <see cref="Direction"/> from the given <see cref="Directions"/> value. </summary>
	/// <param name="_value"></param>
	Direction(Directions _value) : m_value(_value) { }

	bool operator==(const Direction& _other) const { return m_value == _other.m_value; }
	bool operator!=(const Direction& _other) const { return m_value != _other.m_value; }

	bool operator==(const Directions& _other) const { return m_value == _other; }
	bool operator!=(const Directions& _other) const { return m_value != _other; }

	/// <summary> Gets the <see cref="Direction"/> opposite. </summary>
	/// <returns> The opposite <see cref="Direction"/>. </returns>
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

	/// <summary> Gets the <see cref="Direction"/> to the left. </summary>
	/// <returns> The left <see cref="Direction"/>. </returns>
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

	/// <summary> Gets the <see cref="Direction"/> to the right. </summary>
	/// <returns> The right <see cref="Direction"/>. </returns>
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

	/// <summary> Gets the <see cref="Point"/> representing this <see cref="Direction"/> as a move. </summary>
	/// <returns> The normal of this <see cref="Direction"/>. </returns>
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

	/// <summary> Gets a random <see cref="Direction"/>. </summary>
	/// <returns> The random <see cref="Direction"/>. </returns>
	inline static Direction GetRandom() { return Direction((Directions)Random::RandomBetween(0, 3)); }

	/// <summary> Gets the <see cref="Direction"/> that is looking at the given position the most. </summary>
	/// <param name="_position"> The position that is looking. </param>
	/// <param name="_lookAt"> The position that is being looked at. </param>
	/// <returns> The <see cref="Direction"/> that is looking the most at the given position. </returns>
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