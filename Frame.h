#ifndef FRAME_H
#define FRAME_H

// Data includes.
#include "Point.h"

// Typedef includes.
#include <stdint.h>

namespace UserInterface
{
	class Frame
	{
	public:
		Frame() : m_windowPosition(Point(0, 0)), m_windowSize(Point(0, 0)), m_spriteID(0) {}
		Frame(const Point _position, const Point _size, const uint16_t _spriteID) : m_windowPosition(_position), m_windowSize(_size), m_spriteID(_spriteID) {}

		virtual void Draw();

	protected:
		uint16_t m_spriteID;

		Point m_windowPosition;
		Point m_windowSize;
	};
}
#endif