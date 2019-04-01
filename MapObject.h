#ifndef MAPOBJECT_H
#define MAPOBJECT_H

// Derived includes.
#include "IReadOnlyMapObject.h"

// Data includes.
#include "Point.h"

// Utility includes.
#include "SpriteData.h"

// Typedef includes.
#include <stdint.h>

namespace GameObjects
{
	/// <summary> Represents an object on the map. </summary>
	class MapObject : public IReadOnlyMapObject
	{
	public:
		/// <summary> Creates an empty <see cref="MapObject"/>. </summary>
		MapObject() : m_tilePosition(Point(0, 0)) {}

		/// <summary> Creates a <see cref="MapObject"/> with the given sprite ID. </summary>
		/// <param name="_spriteID"></param>
		MapObject(const uint8_t _spriteID) : m_tilePosition(Point(0, 0)), m_spriteID(_spriteID) {}

		/// <summary> Gets the tile position of this object on the map. </summary>
		/// <returns> The tile position of this object on the map. </returns>
		virtual Point GetTilePosition()						{ return m_tilePosition; }

		/// <summary> Gets the tile position of this object on the map. </summary>
		/// <param name="_position"> The new tile position. </param>
		inline void SetTilePosition(const Point _position)	{ m_tilePosition = _position; }

		virtual void Draw(Point);
	protected:
		/// <summary> The position of this object on the map. </summary>
		Point	m_tilePosition;

		/// <summary> The ID of this object's sprite. </summary>
		uint8_t	m_spriteID = 0;
	};
}
#endif