#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

#include <vector>

class TileMap
{
public:
	TileMap(unsigned short, unsigned short);

	TileMap(TileMap&) = delete;
	TileMap& operator=(const TileMap&) = delete;

	inline unsigned short	GetWidth()										const	{ return m_width; }
	inline unsigned short	GetHeight()										const	{ return m_height; }
	inline unsigned short	GetArea()										const	{ return m_width * m_height; }

	inline Tile				GetTileAt(const Point _position)				const	{ return m_data[_position.x][_position.y]; }
	inline unsigned char	GetTileIDAt(const Point _position)				const	{ return m_data[_position.x][_position.y].m_prosperity; }
	inline unsigned char	GetTileProsperityAt(const Point _position)		const	{ return m_data[_position.x][_position.y].m_prosperity; }

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

	void					FillCell(Point, unsigned short);
	inline void				FillCellWithRandomFloor(const Point _position)			{ FillCell(_position, SpriteData::GetRandomFloor()); }
	inline void				FillCellWithRandomWall(const Point _position)			{ FillCell(_position, SpriteData::GetRandomPlainWall()); }

	void					SetCellProsperity(Point, unsigned char);

	void					SetCellVisiblity(Point, bool);

	void					FillArea(Point, Point, unsigned short);
	void					FillAreaWithRandomFloor(Point, Point);
	void					FillAreaWithRandomWall(Point, Point);

	void					Reset();
private:
	/// <summary> The map data. </summary>
	std::vector<std::vector<Tile>>	m_data;

	/// <summary> The width of the tile data. </summary>
	unsigned short					m_width;

	/// <summary> The height of the tile data. </summary>
	unsigned short					m_height;
};
#endif