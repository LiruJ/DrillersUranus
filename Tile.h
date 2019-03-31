#ifndef TILE_H
#define TILE_H

// Graphical includes.
#include "SpriteData.h"
#include "Graphics.h"

// Data includes.
#include "Point.h"

struct Tile
{
	uint8_t m_ID : 7;
	bool m_visibility : 1;
	uint8_t m_prosperity : 8;

	Tile() : m_ID(0), m_prosperity(0), m_visibility(false) {}

	void inline Destroy() { m_ID = 0; m_prosperity = 0; }

	void Draw(Point, Point);
};
#endif