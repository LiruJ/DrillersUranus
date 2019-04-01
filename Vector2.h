#ifndef VECTOR2_H
#define VECTOR2_H

// Utility includes.
#include <math.h>

/// <summary> Represents a mathematical vector2. </summary>
struct Vector2
{
	/// <summary> The x value. </summary>
	double_t x;

	/// <summary> The y value. </summary>
	double_t y;

	/// <summary> Creates an empty vector with both values set to <c>0</c>. </summary>
	Vector2() : x(0), y(0) {}

	/// <summary> Creates a new vector with the given value. </summary>
	/// <param name="_xy"> The value to use for both the x and the y. </param>
	Vector2(const double_t _xy) :x(_xy), y(_xy) {}

	/// <summary> Creates a new vector with the given x and y. </summary>
	/// <param name="_x"> The x. </param>
	/// <param name="_y"> The y. </param>
	Vector2(const double_t _x, const double_t _y) : x(_x), y(_y) {}

	/// <summary> Creates a new unit vector pointing based on the given angle. </summary>
	/// <param name="_angle"> The angle in radians. </param>
	/// <returns> A unit vector pointing based on the given angle. </returns>
	inline static Vector2 fromRadians(const double_t _angle) { return Vector2(cos(_angle), sin(_angle)); }

	Vector2 operator+(const Vector2& _vector2)	const	{ return Vector2(x + _vector2.x,	y + _vector2.y); }
	Vector2 operator+(const double_t _value)	const	{ return Vector2(x + _value,			y + _value); }
		
	Vector2& operator+=(const Vector2& _vector2)		{ x += _vector2.x;	y += _vector2.y;	return *this; }
	Vector2& operator+=(const double_t _value)			{ x += _value;		y += _value;			return *this; }

	Vector2 operator-(const Vector2& _vector2)	const	{ return Vector2(x - _vector2.x,	y - _vector2.y); }
	Vector2 operator-(const double_t _value)	const	{ return Vector2(x - _value,			y - _value); }

	Vector2& operator-=(const Vector2& _vector2)		{ x -= _vector2.x;	y -= _vector2.y;	return *this; }
	Vector2& operator-=(const double_t _value)			{ x -= _value;		y -= _value; }

	Vector2 operator*(const Vector2& _vector2)	const	{ return Vector2(x * _vector2.x,	y * _vector2.y); }
	Vector2 operator*(const double_t _value)	const	{ return Vector2(x * _value,			y * _value); }

	Vector2& operator*=(const Vector2& _vector2)		{ x *= _vector2.x;	y *= _vector2.y;	return *this; }
	Vector2& operator*=(const double_t _value)			{ x *= _value;		y *= _value;			return *this; }

	Vector2 operator/(const Vector2& _vector2)	const	{ return Vector2(x / _vector2.x,	y / _vector2.y); }
	Vector2 operator/(const double_t _value)	const	{ return Vector2(x / _value,			y / _value); }

	Vector2& operator/=(const Vector2& _vector2)		{ x /= _vector2.x;	y /= _vector2.y;	return *this; }
	Vector2& operator/=(const double_t _value)			{ x /= _value;		y /= _value;			return *this; }

	/// <summary> Calculates the length. </summary>
	/// <returns> The calculated length. </returns>
	inline double_t Length()					const	{ return sqrt(LengthSquared()); }

	/// <summary> Calculates the length squared by not getting the square root. </summary>
	/// <returns> The length squared. </returns>
	inline double_t LengthSquared()				const	{ return pow(x, 2) + pow(y, 2); }

	/// <summary> Calculates the normalised vector. </summary>
	/// <returns> The normalised vector. </returns>
	inline Vector2 Unit()						const	{ return *this / Length(); }
};
#endif