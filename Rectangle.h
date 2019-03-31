#ifndef RECTANGLE_H
#define RECTANGLE_H

// Data includes.
#include "Point.h"

// Typedef includes.
#include <stdint.h>

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
	bool IsPointInside(const Point _position) const { return _position.x >= x && _position.x < x + w && _position.y >= y && _position.y < y + h; }
};

#endif