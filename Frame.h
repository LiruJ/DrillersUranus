#ifndef FRAME_H
#define FRAME_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

// Typedef includes.
#include <stdint.h>

namespace UserInterface
{
	/// <summary> Represents a plain UI frame with no extra behaviour. </summary>
	class Frame
	{
	public:
		/// <summary> Creates an empty <see cref="Frame"/>. </summary>
		Frame() : m_screenPosition(Point(0, 0)), m_screenSize(Point(0, 0)), m_screenBounds(Rectangle(0, 0, 0, 0)), m_spriteID(0) {}

		/// <summary> Creates a <see cref="Frame"/> at the given position with the given size and sprite ID. </summary>
		/// <param name="_position"> The position. </param>
		/// <param name="_size"> the size. </param>
		/// <param name="_spriteID"> The sprite ID. </param>
		Frame(const Point _position, const Point _size, const uint16_t _spriteID) : m_screenPosition(_position), m_screenSize(_size), m_screenBounds(_position, _size), m_spriteID(_spriteID) {}

		virtual void Draw();
	protected:
		/// <summary> The ID of the sprite that should be drawn. </summary>
		uint16_t m_spriteID;

		/// <summary> The position. </summary>
		Point m_screenPosition;

		/// <summary> The size. </summary>
		Point m_screenSize;

		/// <summary> The bounds. </summary>
		Rectangle m_screenBounds;
	};
}
#endif