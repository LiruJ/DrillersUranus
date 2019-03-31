#ifndef TEXTUREBOUND_H
#define TEXTUREBOUND_H

// Data includes.
#include "Point.h"

#include "SDL.h"

namespace Graphics
{
	struct TextureBound
	{
		TextureBound(const Point _position, const Point _size) : x(_position.x), y(_position.y), w(_size.x), h(_size.y) {}
		TextureBound(const int32_t _x, const int32_t _y, const int32_t _w, const int32_t _h) : x(_x), y(_y), w(_w), h(_h) {}

		operator SDL_Rect() const { SDL_Rect rect; rect.x = x; rect.y = y; rect.w = w; rect.h = h; return rect; }

		int32_t x;
		int32_t y;
		int32_t w;
		int32_t h;
	};
}
#endif