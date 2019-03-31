#ifndef TILE_H
#define TILE_H

// Typedef includes.
#include <stdint.h>

namespace WorldObjects
{
	struct Tile
	{
		/// <summary> The ID. </summary>
		/// <remarks> Uses 7 bits, so ranges from <c>0</c> to <c>127</c>. </remarks>
		uint8_t m_ID : 7;

		/// <summary> <c>true</c> if this tile has been discovered by the player; otherwise, <c>false</c>. </summary>
		bool m_visibility : 1;

		/// <summary> The prosperity level. </summary>
		uint8_t m_prosperity : 8;

		/// <summary> Creates a blank tile. </summary>
		Tile() : m_ID(0), m_prosperity(0), m_visibility(false) {}
	};
}
#endif