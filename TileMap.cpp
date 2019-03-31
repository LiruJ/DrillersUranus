#include "TileMap.h"

/// <summary> Creates a new <see cref="TileMap"/> with the given width and height. </summary>
/// <param name="_width"> The width of the data. </param>
/// <param name="_height"> The height of the data. </param>
WorldObjects::TileMap::TileMap(const uint16_t _width, const uint16_t _height) : m_width(_width), m_height(_height)
{
	// Initialise the rows and columns.
	m_data = std::vector<std::vector<Tile>>(m_width);
	for (int32_t x = 0; x < m_width; x++) { m_data[x] = std::vector<Tile>(m_height); }
}

/// <summary> Finds if the given area is floored. </summary>
/// <param name="_area"> The area to check. </param>
/// <returns> <c>true</c> if not a single blocked cell exists within the given area, <c>false</c> otherwise. </returns>
bool WorldObjects::TileMap::AreaIsClear(const Rectangle _area)
{
	// Check each cell in the area, if any are blocked, return false.
	for (int32_t x = _area.x; x < _area.GetMaxX(); x++)
	{
		for (int32_t y = _area.y; y < _area.GetMaxY(); y++) 
		{
			if (IsCellBlockedAndInRange(Point(x, y))) { return false; }
		}
	}

	// If every cell is clear, the area is clear.
	return true;
}

/// <summary> Finds if the given area is walled. </summary>
/// <param name="_area"> The area to check. </param>
/// <returns> <c>true</c> if not a single clear cell exists within the given area, <c>false</c> otherwise. </returns>
bool WorldObjects::TileMap::AreaIsBlocked(const Rectangle _area)
{
	// Check each cell in the area, if any are clear, return false.
	for (int32_t x = _area.x; x < _area.GetMaxX(); x++)
	{
		for (int32_t y = _area.y; y < _area.GetMaxY(); y++)
		{
			if (IsCellClearAndInRange(Point(x, y))) { return false; } 
		}
	}

	// If every cell is blocked, the area is blocked.
	return true;
}

/// <summary> Fills the cell at the given position with the given ID. </summary>
/// <param name="_position"> The position of the cell. </param>
/// <param name="_ID"> The new ID of the cell. </param>
void WorldObjects::TileMap::FillCell(const Point _position, const uint16_t _ID)
{
	// If the cell is out of range, do nothing.
	if (!IsCellInRange(_position)) { return; }

	// Fill the cell at the given position with the given ID, also set the prosperity to 0 as floors cannot be mined.
	m_data[_position.x][_position.y].m_ID = _ID;
	SetCellProsperity(_position, 0);
}

/// <summary> Sets the prosperity of the given cell with the given value. </summary>
/// <param name="_position"> The position of the cell. </param>
/// <param name="_prosperity"> the new prosperity of the cell. </param>
void WorldObjects::TileMap::SetCellProsperity(const Point _position, const uint8_t _prosperity)
{
	// If the cell is out of range, do nothing.
	if (!IsCellInRange(_position)) { return; }

	// Fill the cell at the given position with the given ID.
	m_data[_position.x][_position.y].m_prosperity = _prosperity;
}

/// <summary> Sets the visibility of the given cell with the given value. </summary>
/// <param name="_position"> The position of the cell. </param>
/// <param name="_visibility"> the new visibility of the cell. </param>
void WorldObjects::TileMap::SetCellVisiblity(const Point _position, const bool _visibility)
{
	// If the cell is out of range, do nothing.
	if (!IsCellInRange(_position)) { return; }

	// Set the visibility of the cell at the given position with the given value.
	m_data[_position.x][_position.y].m_visibility = _visibility;
}

/// <summary> Fills every cell within the given area with the given ID. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
/// <param name="_ID"> The ID with which to fill the area. </param>
void WorldObjects::TileMap::FillArea(const Rectangle _area, const uint16_t _ID)
{
	for (int32_t x = _area.x; x < _area.GetMaxX(); x++)
	{
		for (int32_t y = _area.y; y < _area.GetMaxY(); y++)
		{
			FillCell(Point(x, y), _ID); 
		}
	}
}

/// <summary> Fills every cell within the given area with a random floor. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
void WorldObjects::TileMap::FillAreaWithRandomFloor(const Rectangle _area)
{
	for (int32_t x = _area.x; x < _area.GetMaxX(); x++)
	{
		for (int32_t y = _area.y; y < _area.GetMaxY(); y++)
		{
			FillCellWithRandomFloor(Point(x, y)); 
		}
	}
}

/// <summary> Fills every cell within the given area with a random wall. </summary>
/// <param name="_position"> The top-left corner of the area to fill. </param>
/// <param name="_size"> The size of the area to fill. </param>
void WorldObjects::TileMap::FillAreaWithRandomWall(const Rectangle _area)
{
	for (int32_t x = _area.x; x < _area.GetMaxX(); x++)
	{
		for (int32_t y = _area.y; y < _area.GetMaxY(); y++)
		{
			FillCellWithRandomWall(Point(x, y)); 
		}
	}
}

/// <summary> Resets the data. </summary>
void WorldObjects::TileMap::Reset()
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
