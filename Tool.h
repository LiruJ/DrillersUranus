#ifndef TOOL_H
#define TOOL_H

namespace Minigames
{
	struct Tool
	{
		/// <summary> The size of this tool's effect in tiles. </summary>
		unsigned char m_size;

		/// <summary> How many layers are destroyed at a time with this tool. </summary>
		unsigned char m_power;

		Tool(const unsigned char _size, const unsigned char _power) : m_size(_size), m_power(_power) {}
	};
}
#endif