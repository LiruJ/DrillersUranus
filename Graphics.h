#ifndef GRAPHICS_H
#define GRAPHICS_H

// Data includes.
#include "Point.h"
#include "Rectangle.h"

namespace Graphics
{
	class Graphics
	{
	public:
		virtual ~Graphics() {}

		virtual void Clear(uint8_t, uint8_t, uint8_t) = 0;
		virtual void Clear(uint8_t, uint8_t, uint8_t, uint8_t) = 0;
		virtual void Present() = 0;

		virtual void Draw(uint16_t, uint16_t, Point) = 0;
		virtual void Draw(uint16_t, uint16_t, Point, float) = 0;
		
		virtual void Draw(uint16_t, uint16_t, Rectangle) = 0;
		virtual void Draw(uint16_t, uint16_t, Rectangle, float) = 0;

		virtual void Draw(uint16_t, uint16_t, Rectangle, Rectangle) = 0;

		int m_framesPerSecond = 30;
	};
}
#endif