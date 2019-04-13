#ifndef RECTANGLE_H
#define RECTANGLE_H

// Data includes.
#include "Point.h"

// Typedef includes.
#include <stdint.h>

/// <summary> Represents a rectangle. </summary>
struct Rectangle
{
	/// <summary> The x position. </summary>
	int32_t x;

	/// <summary> The y position. </summary>
	int32_t y;

	/// <summary> The width. </summary>
	int32_t w;

	/// <summary> The height. </summary>
	int32_t h;

	/// <summary> Creates a <see cref="Rectangle"/> from the given position and size. </summary>
	/// <param name="_position"> The position. </param>
	/// <param name="_size"> The size. </param>
	Rectangle(const Point _position, const Point _size) : x(_position.x), y(_position.y), w(_size.x), h(_size.y) {}

	/// <summary> Creates a <see cref="Rectangle"/> from the given positions and sizes. </summary>
	/// <param name="_x"> The x position. </param>
	/// <param name="_y"> The y position. </param>
	/// <param name="_w"> The width. </param>
	/// <param name="_h"> The height. </param>
	Rectangle(const int32_t _x, const int32_t _y, const int32_t _w, const int32_t _h) : x(_x), y(_y), w(_w), h(_h) {}

	/// <summary> Finds if the given position is within this <see cref="Rectangle"/>. </summary>
	/// <param name="_position"> The position to check. </param>
	/// <returns> <c>true</c> if the point is inside this <see cref="Rectangle"/>, <c>false</c> otherwise. </returns>
	inline bool IsPointInside(const Point _position) const { return _position.x >= x && _position.x < GetMaxX() && _position.y >= y && _position.y < GetMaxY(); }

	inline bool Intersects(const Rectangle _other) const { return (_other.x < x + w && x < _other.x + _other.w && _other.y < y + h && y < _other.y + _other.h); }

	/// <summary> Gets the x position of the right side of this <see cref="Rectangle"/>. </summary>
	/// <returns> The right hand side x position. </returns>
	inline int32_t GetMaxX() const { return x + w; }

	/// <summary> Gets the y position of the bottom side of this <see cref="Rectangle"/>. </summary>
	/// <returns> The bottom side y position. </returns>
	inline int32_t GetMaxY() const { return y + h; }
};

#endif