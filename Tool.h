#ifndef TOOL_H
#define TOOL_H

// Typedef includes.
#include <stdint.h>

namespace Minigames
{
	struct Tool
	{
		/// <summary> The size of this tool's effect in tiles. </summary>
		uint8_t m_size;

		/// <summary> How many layers are destroyed at a time with this tool. </summary>
		uint8_t m_power;

		Tool(const uint8_t _size, const uint8_t _power) : m_size(_size), m_power(_power) {}
	};
}
#endif