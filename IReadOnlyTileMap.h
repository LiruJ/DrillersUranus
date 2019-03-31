#ifndef IREADONLYTILEMAP_H
#define IREADONLYTILEMAP_H

// Data includes.
#include "Tile.h"
#include "Point.h"
#include "Rectangle.h"

// Typedef includes.
#include <stdint.h>

namespace WorldObjects
{
	/// <summary> Represents a read-only interface of the <see cref="TileMap"/> </summary>
	class IReadOnlyTileMap
	{
	public:
		/// <summary> Gets the width of the data. </summary>
		/// <returns> The width of the data. </returns>
		virtual uint16_t	GetWidth() = 0;

		/// <summary> Gets the height of the data. </summary>
		/// <returns> The height of the data. </returns>
		virtual uint16_t	GetHeight() = 0;

		/// <summary> Gets the area of the data. </summary>
		/// <returns> The width multiplied by the height of the data. </returns>
		virtual uint16_t	GetArea() = 0;

		/// <summary> Gets the <see cref="Tile"/> at the given position. </summary>
		/// <param name="_position"> The position whence to get the <see cref="Tile"/>. </param>
		/// <returns> The <see cref="Tile"/> at the given position. </returns>
		virtual Tile		GetTileAt(Point _position) = 0;

		/// <summary> Returns <c>true</c> if the given position is in range; otherwise, <c>false</c>. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is in range; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellInRange(Point _position) = 0;

		/// <summary> Returns <c>true</c> if the given position is in the playable range; otherwise, <c>false</c>. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is in the playable range; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellInPlayableArea(Point _position) = 0;

		/// <summary> Checks if the <see cref="Tile"/> at the given position is empty. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is empty; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellClear(Point _position) = 0;

		/// <summary> Checks if the <see cref="Tile"/> at the given position is empty and on the map. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is empty and on the map; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellClearAndInRange(Point _position) = 0;

		/// <summary> Checks if the <see cref="Tile"/> at the given position is blocked. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is blocked; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellBlocked(Point _position) = 0;

		/// <summary> Checks if the <see cref="Tile"/> at the given position is blocked and on the map. </summary>
		/// <param name="_position"> The position to check. </param>
		/// <returns> <c>true</c> if the given position is blocked and on the map; otherwise, <c>false</c>. </returns>
		virtual bool		IsCellBlockedAndInRange(Point _position) = 0;

		/// <summary> Finds if the given area is floored. </summary>
		/// <param name="_area"> The area to check. </param>
		/// <returns> <c>true</c> if not a single blocked cell exists within the given area, <c>false</c> otherwise. </returns>
		virtual bool		AreaIsClear(Rectangle _area) = 0;

		/// <summary> Finds if the given area is walled. </summary>
		/// <param name="_area"> The area to check. </param>
		/// <returns> <c>true</c> if not a single clear cell exists within the given area, <c>false</c> otherwise. </returns>
		virtual bool		AreaIsBlocked(Rectangle _area) = 0;
	};
}
#endif