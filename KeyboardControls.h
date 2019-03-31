#ifndef KEYBOARDCONTROLS_H
#define KEYBOARDCONTROLS_H

#include "Controls.h"

#include <map>
#include <string>

namespace Controls
{
	class KeyboardControls : public Controls
	{
	public:
		KeyboardControls() : m_keyCodeToCommands(std::map<int32_t, Command>()), m_commandToKeyCodes(std::map<Command, int32_t>()) {}

		void						LoadFromFile(std::string);

		inline virtual int32_t			GetKeyForCommand(const Command _command)							{ return (m_commandToKeyCodes.find(_command) == m_commandToKeyCodes.end()) ? -1 : m_commandToKeyCodes[_command]; }
		inline virtual Command		GetCommandFromKey(const int32_t _keycode)								{ return (m_keyCodeToCommands.find(_keycode) == m_keyCodeToCommands.end()) ? Command::None : m_keyCodeToCommands[_keycode]; }
		
		void						BindCommandToKey(const Command _command, const int32_t _keycode)		{ m_commandToKeyCodes[_command] = _keycode; m_keyCodeToCommands[_keycode] = _command; }

		void						UnbindCommandFromKey(const Command _command, const int32_t _keycode)	{ m_commandToKeyCodes.erase(_command); m_keyCodeToCommands.erase(_keycode); }
	private:
		/// <summary> The game commands mapped by key code. </summary>
		std::map<int32_t, Command> m_keyCodeToCommands;

		/// <summary> The key codes mapped by command. </summary>
		std::map<Command, int32_t> m_commandToKeyCodes;
	};
}
#endif