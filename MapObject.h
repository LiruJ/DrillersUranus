#ifndef MAPOBJECT_H
#define MAPOBJECT_H

// Graphical includes.
#include "SpriteData.h"

// Interface includes.
#include "IReadOnlyMapObject.h"

class MapObject : public IReadOnlyMapObject
{
public:
	MapObject() : m_tilePosition(Point(0, 0)) {}
	MapObject(const unsigned char _spriteID) : m_tilePosition(Point(0, 0)), m_spriteID(_spriteID) {}
	~MapObject() {}

	virtual Point GetTilePosition()										{ return m_tilePosition; }
	virtual void inline SetTilePosition(const Point _position)			{ m_tilePosition = _position; }

	virtual void Draw(Point);

protected:
	Point			m_tilePosition;
	unsigned char	m_spriteID = 0;
};
#endif