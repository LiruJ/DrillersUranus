#include "TileMap.h"



TileMap::TileMap(const uint16_t _width, const uint16_t _height) : m_width(_width), m_height(_height)
{
	// Initialise the rows and columns.
	m_data = std::vector<std::vector<Tile>>(m_width);
	for (int32_t x = 0; x < m_width; x++) { m_data[x] = std::vector<Tile>(m_height); }
}

/// <summary> Finds if the given area is floored. </summary>
/// <param name="_position"> The top-left corner of the area to check. </param>
/// <param name="_size"> The size of the area to check. </param>
/// <returns> <c>true</c> if not a single blocked cell exists within the given area, <c>false</c> otherwise. </returns>
bool TileMap::AreaIsClear(const Point _position, const Point _size)
{
	// Check each cell in the area, if any are blocked, return false.
	for (int32_t x = _position.x; x < _position.x + _size.x; x++)
	{
		for (int32_t y = _position.y; y < _position.y + _size.y; y++) { if (CellIsBlockedAndInRange(Point(x, y))) { return false; } }
	}

	// If every cell is clear, the area is clear.
	return true;
}

/// <summary> Finds if the given area is walled. </summary>
/// <param name="_position"> The top-left corner of the area to check. </param>
/// <param name="_size"> The size of the area to check. </param>
/// <returns> <c>true</c> if not a single clear cell exists within the given area, <c>false</c> otherwise. </returns>
bool TileMap::AreaIsBlocked(const Point _position, const Point _size)
{
	// Check each cell in the area, if any are clear, return false.
	for (int32_t x = _position.x; x < _position.x + _size.x; x++)
	{
		for (int32_t y = _position.y; y < _position.y + _size.y; y++) { if (CellIsClearAndInRange(Point(x, y))) { return false; } }
	}

	// If every cell is blocked, the area is blocked.
	return true;
}

/// <summary> Fills the cell at the given position with the given ID. </summary>
/// <param name="_position"> The position of the cell. </param>
/// <param name="_ID"> The new ID of the cell. </param>
void TileMap::FillCell(const Point _position, const uint16_t _ID)
{
	// If the cell is out of range, do nothing.
	if (!CellInRange(_position)) { return; }

	// Fill the cell at the given position with the given ID, also set the prosperity to 0 as floors cannot be mined.
	m_data[_position.x][_position.y].m_ID = _ID;
	SetCellProsperity(_position, 0);
}

/// <summary> Sets the prosperity of the given cell with the given value. </summary>
/// <param name="_position"> The position of the cell. </param>
/// <param name="_prosperity"> the new prosperity of the cell. </param>
void TileMap::SetCellProsperity(const Point _position, const uint8_t _prosperity)
{
	// If the cell is out of range, do nothing.
	if (!CellInRange(_position)) { return; }

	// Fill the cell at the given position with the given ID.
	m_data[_position.x][_position.y].m_prosperity = _prosperity;
}

void TileMap::SetCellVisiblity(const Point _position, const bool _visibility)
{
	// If the cell is out of range, do nothing.
	if (!CellInRange(_position)) { return; }

	// Set the visibility of the cell at the given position with the given value.
	m_data[_position.x][_position.y].m_visibility = _visibility;
}

/// <summary> Fills every cell within the given area with the given ID. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
/// <param name="_ID"> The ID with which to fill the area. </param>
void TileMap::FillArea(const Point _position, const Point _size, const uint16_t _ID)
{
	for (int32_t x = _position.x; x < _position.x + _size.x; x++)
	{
		for (int32_t y = _position.y; y < _position.y + _size.y; y++) { FillCell(Point(x, y), _ID); }
	}
}

/// <summary> Fills every cell within the given area with a random floor. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
void TileMap::FillAreaWithRandomFloor(const Point _position, const Point _size)
{
	for (int32_t x = _position.x; x < _position.x + _size.x; x++)
	{
		for (int32_t y = _position.y; y < _position.y + _size.y; y++) { FillCellWithRandomFloor(Point(x, y)); }
	}
}

/// <summary> Fills every cell within the given area with a random wall. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
void TileMap::FillAreaWithRandomWall(const Point _position, const Point _size)
{
	for (int32_t x = _position.x; x < _position.x + _size.x; x++)
	{
		for (int32_t y = _position.y; y < _position.y + _size.y; y++) { FillCellWithRandomWall(Point(x, y)); }
	}
}

void TileMap::Reset()
{
	for (int32_t x = 0; x < m_width; x++)
	{
		for (int32_t y = 0; y < m_height; y++) 
		{
			FillCellWithRandomWall(Point(x, y));
			SetCellProsperity(Point(x, y), 0);
			SetCellVisiblity(Point(x, y), false);
		}
	}
}
