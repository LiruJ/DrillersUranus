#ifndef POINT_H
#define POINT_H

// Typedef includes.
#include <stdint.h>
#include <cmath>

struct Point
{
	int32_t x;
	int32_t y;
	
	/// <summary> Creates an empty <see cref="Point"/>. </summary>
	Point() : x(0), y(0) {}

	/// <summary> Creates a <see cref="Point"/> with the given x and y values. </summary>
	/// <param name="_x"> The x value. </param>
	/// <param name="_y"> The y value. </param>
	Point(const int32_t _x, const int32_t _y) : x(_x), y(_y) {}

	/// <summary> Creates a <see cref="Point"/> with the given x and y values. </summary>
	/// <param name="_x"> The x value. </param>
	/// <param name="_y"> The y value. </param>
	/// <remarks> Defines behaviour for floats, otherwise multiple warnings are generated about data loss. </remarks>
	Point(const float_t _x, const float_t _y) : x((int32_t)_x), y((int32_t)_y) {}

	/// <summary> Creates a <see cref="Point"/> with the given x and y value. </summary>
	/// <param name="_xy"> The x and y value. </param>
	Point(const int32_t _xy) : x(_xy), y(_xy) {}

	/// <summary> Creates a <see cref="Point"/> with the given x and y value. </summary>
	/// <param name="_xy"> The x and y value. </param>
	/// <remarks> Defines behaviour for floats, otherwise multiple warnings are generated about data loss. </remarks>
	Point(const float_t _xy) : x((int32_t)_xy), y((int32_t)_xy) {}

	bool operator==(const Point& _other)	const	{ return (x == _other.x && y == _other.y); }
	bool operator!=(const Point& _other)	const	{ return (x != _other.x || y != _other.y); }

	Point operator+(const Point& _point)	const	{ return Point(x + _point.x,			y + _point.y); }
	Point operator+(const int32_t _value)	const	{ return Point(x + _value,				y + _value); }

	Point& operator+=(const Point& _point)			{ x += _point.x;						y += _point.y;	return *this; }
	Point& operator+=(const int32_t _value)			{ x += _value;							y += _value;	return *this; }

	Point operator-(const Point& _point)	const	{ return Point(x - _point.x,			y - _point.y); }
	Point operator-(const int32_t _value)	const	{ return Point(x - _value,				y - _value); }

	Point& operator-=(const Point& _point)			{ x -= _point.x;						y -= _point.y;	return *this; }
	Point& operator-=(const int32_t _value)			{ x -= _value;							y -= _value;	return *this; }

	Point operator*(const Point& _point)	const	{ return Point(x * _point.x,			y * _point.y); }
	Point operator*(const int32_t _value)	const	{ return Point(x * _value,				y * _value); }
	Point operator*(const float_t _value)	const	{ return Point((int32_t)(x * _value),	(int32_t)(y * _value)); }

	Point& operator*=(const Point& _point)			{ x *= _point.x;						y *= _point.y;	return *this; }
	Point& operator*=(const int32_t _value)			{ x *= _value;							y *= _value;	return *this; }
	Point& operator*=(const float_t _value)			{ x = (int32_t)(x * _value);			y = (int32_t)(y * _value); return *this; }

	Point operator/(const Point& _point)	const	{ return Point(x / _point.x,			y / _point.y); }
	Point operator/(const int32_t _value)	const	{ return Point(x / _value,				y / _value); }
	Point operator/(const float_t _value)	const	{ return Point((int32_t)(x / _value),	(int32_t)(y / _value)); }

	Point& operator/=(const Point& _point)			{ x /= _point.x;						y /= _point.y;	return *this; }
	Point& operator/=(const int32_t _value)			{ x /= _value;							y /= _value;	return *this; }
	Point& operator/=(const float_t _value)			{ x = (int32_t)(x / _value);			y = (int32_t)(y /_value);	return *this; }
};

#endif