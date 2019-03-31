#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

#include <vector>

class TileMap
{
public:
	TileMap(uint16_t, uint16_t);

	TileMap(TileMap&) = delete;
	TileMap& operator=(const TileMap&) = delete;

	inline uint16_t	GetWidth()										const	{ return m_width; }
	inline uint16_t	GetHeight()										const	{ return m_height; }
	inline uint16_t	GetArea()										const	{ return m_width * m_height; }

	inline Tile				GetTileAt(const Point _position)				const	{ return m_data[_position.x][_position.y]; }
	inline uint8_t	GetTileIDAt(const Point _position)				const	{ return m_data[_position.x][_position.y].m_prosperity; }
	inline uint8_t	GetTileProsperityAt(const Point _position)		const	{ return m_data[_position.x][_position.y].m_prosperity; }

	inline bool				CellInRange(const Point _position)				const	{ return _position.x >= 0 && _position.x < m_width && _position.y >= 0 && _position.y < m_height; }

	inline bool				CellInPlayableArea(const Point _position)		const	{ return (_position.x > 0 && _position.x < m_width - 1 && _position.y > 0 && _position.y < m_height - 1); }

	inline bool				CellIsClear(const Point _position)				const	{ return SpriteData::IsFloor(m_data[_position.x][_position.y].m_ID); }
	inline bool				CellIsClearAndInRange(const Point _position)	const	{ return CellInRange(_position) && CellIsClear(_position); }

	/// <summary> Checks if the given position is within the playable bounds of the map. </summary>
	/// <param name="_position"> The position to check. </param>
	/// <returns> <c>true</c> if the cell is valid, <c>false</c> otherwise. </returns>
	inline bool				CellIsBlocked(const Point _position)			const	{ return SpriteData::IsWall(m_data[_position.x][_position.y].m_ID); }
	inline bool				CellIsBlockedAndInRange(const Point _position)	const	{ return CellInRange(_position) && CellIsBlocked(_position); }

	bool					AreaIsClear(Point, Point);
	bool					AreaIsBlocked(Point, Point);

	void					FillCell(Point, uint16_t);
	inline void				FillCellWithRandomFloor(const Point _position)			{ FillCell(_position, SpriteData::GetRandomFloor()); }
	inline void				FillCellWithRandomWall(const Point _position)			{ FillCell(_position, SpriteData::GetRandomPlainWall()); }

	void					SetCellProsperity(Point, uint8_t);

	void					SetCellVisiblity(Point, bool);

	void					FillArea(Point, Point, uint16_t);
	void					FillAreaWithRandomFloor(Point, Point);
	void					FillAreaWithRandomWall(Point, Point);

	void					Reset();
private:
	/// <summary> The map data. </summary>
	std::vector<std::vector<Tile>>	m_data;

	/// <summary> The width of the tile data. </summary>
	uint16_t					m_width;

	/// <summary> The height of the tile data. </summary>
	uint16_t					m_height;
};
#endif