#ifndef TILEMAP_H
#define TILEMAP_H

// Derived includes.
#include "IReadOnlyTileMap.h"

// Data includes.
#include "Tile.h"
#include "Point.h"
#include "Rectangle.h"

// Utility includes.
#include "SpriteData.h"
#include <vector>

// Typedef includes.
#include <stdint.h>

namespace WorldObjects
{
	/// <summary> Represents a 2D <see cref="Tile"/>-based map. </summary>
	class TileMap : public IReadOnlyTileMap
	{
	public:
		TileMap(uint16_t, uint16_t);

		TileMap(TileMap&) = delete;
		TileMap& operator=(const TileMap&) = delete;

		/// <summary> Gets the width of the data. </summary>
		/// <returns> The width of the data. </returns>
		virtual uint16_t	GetWidth()										{ return m_width; }

		/// <summary> Gets the height of the data. </summary>
		/// <returns> The height of the data. </returns>
		virtual uint16_t	GetHeight()										{ return m_height; }

		/// <summary> Gets the area of the data. </summary>
		/// <returns> The width multiplied by the height of the data. </returns>
		virtual uint16_t	GetArea()										{ return m_width * m_height; }

		/// <summary> Gets the <see cref="Tile"/> at the given position. </summary>
		/// <param name="_position"> The position whence to get the <see cref="Tile"/>. </param>
		/// <returns> The <see cref="Tile"/> at the given position. </returns>
		virtual Tile		GetTileAt(const Point _position)				{ return m_data[_position.x][_position.y]; }

		/// <summary> Returns <c>true</c> if the given position is in range; otherwise, <c>false</c>. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is in range; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellInRange(const Point _position)			{ return _position.x >= 0 && _position.x < m_width && _position.y >= 0 && _position.y < m_height; }

		/// <summary> Returns <c>true</c> if the given position is in the playable range; otherwise, <c>false</c>. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is in the playable range; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellInPlayableArea(const Point _position)		{ return (_position.x > 0 && _position.x < m_width - 1 && _position.y > 0 && _position.y < m_height - 1); }

		/// <summary> Checks if the <see cref="Tile"/> at the given position is empty. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is empty; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellClear(const Point _position)				{ return SpriteData::IsFloor(m_data[_position.x][_position.y].m_ID); }
		
		/// <summary> Checks if the <see cref="Tile"/> at the given position is empty and on the map. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is empty and on the map; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellClearAndInRange(const Point _position)	{ return IsCellInRange(_position) && IsCellClear(_position); }

		/// <summary> Checks if the <see cref="Tile"/> at the given position is blocked. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is blocked; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellBlocked(const Point _position)			{ return SpriteData::IsWall(m_data[_position.x][_position.y].m_ID); }
		
		/// <summary> Checks if the <see cref="Tile"/> at the given position is blocked and on the map. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is blocked and on the map; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellBlockedAndInRange(const Point _position)	{ return IsCellInRange(_position) && IsCellBlocked(_position); }

		virtual bool		AreaIsClear(Rectangle);
		
		virtual bool		AreaIsBlocked(Rectangle);

		void				FillCell(Point, uint16_t);
		
		/// <summary> Fills the <see cref="Tile"/> at the given position with a random floor. </summary>
		/// <param name="_position"> The position to change. </param>
		inline void			FillCellWithRandomFloor(const Point _position)	{ FillCell(_position, SpriteData::GetRandomFloor()); }
		
		/// <summary> Fills the <see cref="Tile"/> at the given position with a random wall. </summary>
		/// <param name="_position"> The position to change. </param>
		inline void			FillCellWithRandomWall(const Point _position)	{ FillCell(_position, SpriteData::GetRandomPlainWall()); }

		void				SetCellProsperity(Point, uint8_t);

		void				SetCellVisiblity(Point, bool);

		void				FillArea(Rectangle, uint16_t);
		
		void				FillAreaWithRandomFloor(Rectangle);
		
		void				FillAreaWithRandomWall(Rectangle);

		void				Reset();
	private:
		/// <summary> The map data. </summary>
		std::vector<std::vector<Tile>>	m_data;

		/// <summary> The width of the tile data. </summary>
		uint16_t						m_width;

		/// <summary> The height of the tile data. </summary>
		uint16_t						m_height;
	};
}
#endif