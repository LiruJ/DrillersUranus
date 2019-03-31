#ifndef CONTROLS_H
#define CONTROLS_H

// Typedef includes.
#include <stdint.h>

namespace Controls
{
	enum Command
	{
		None = -1, MoveLeft, MoveUp, MoveRight, MoveDown, Interact, Swing
	};

	class Controls
	{
	public:
		virtual ~Controls() {}

		virtual int32_t		GetKeyForCommand(Command) = 0;
		virtual Command		GetCommandFromKey(int32_t) = 0;
	};
}
#endif