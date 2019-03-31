#ifndef TOOL_H
#define TOOL_H

// Typedef includes.
#include <stdint.h>

namespace Minigames
{
	/// <summary> Represents a tool used in the mining minigame. </summary>
	struct Tool
	{
		/// <summary> The size of this <see cref="Tool"/>'s effect in tiles. </summary>
		uint8_t m_size;

		/// <summary> How many layers are destroyed at a time with this <see cref="Tool"/>. </summary>
		uint8_t m_power;

		/// <summary> Creates a new <see cref="Tool"/> with the given size and power. </summary>
		/// <param name="_size"> The size of the tool's effect. </param>
		/// <param name="_power"> The power of the tool. </param>
		Tool(const uint8_t _size, const uint8_t _power) : m_size(_size), m_power(_power) {}
	};
}
#endif