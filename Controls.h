#ifndef CONTROLS_H
#define CONTROLS_H

// Typedef includes.
#include <stdint.h>

namespace Controls
{
	/// <summary> Represents a command that the player can make. </summary>
	enum Command { None = -1, MoveLeft, MoveUp, MoveRight, MoveDown, Interact, Swing };

	/// <summary> Represents an input method. </summary>
	class Controls
	{
	public:
		virtual ~Controls() {}

		/// <summary> Gets the key associated with the given <see cref="Command"/>. </summary>
		/// <param name="_command"> The <see cref="Command"/>. </param>
		/// <returns> The key associated with the given <see cref="Command"/>. </returns>
		virtual int32_t		GetKeyForCommand(Command _command) = 0;

		/// <summary> Gets the command associated with the given key code. </summary>
		/// <param name="_keycode"> The key code. </param>
		/// <returns> The command associated with the given key code. </returns>
		virtual Command		GetCommandFromKey(int32_t _keycode) = 0;
	};
}
#endif