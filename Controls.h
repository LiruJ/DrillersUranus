#ifndef CONTROLS_H
#define CONTROLS_H

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

		virtual int			GetKeyForCommand(Command) = 0;
		virtual Command		GetCommandFromKey(int) = 0;
	};
}
#endif