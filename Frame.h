#ifndef FRAME_H
#define FRAME_H

// Data includes.
#include "Point.h"

namespace UserInterface
{
	class Frame
	{
	public:
		Frame() : m_windowPosition(Point(0, 0)), m_windowSize(Point(0, 0)), m_spriteID(0) {}
		Frame(const Point _position, const Point _size, const unsigned short _spriteID) : m_windowPosition(_position), m_windowSize(_size), m_spriteID(_spriteID) {}

		virtual void Draw();

	protected:
		unsigned short m_spriteID;

		Point m_windowPosition;
		Point m_windowSize;
	};
}
#endif