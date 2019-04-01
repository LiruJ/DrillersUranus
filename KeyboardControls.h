#ifndef KEYBOARDCONTROLS_H
#define KEYBOARDCONTROLS_H

// Derived includes.
#include "Controls.h"

// Utility includes.
#include <map>
#include <string>

namespace Controls
{
	/// <summary> Represents an all keyboard control scheme. </summary>
	class KeyboardControls : public Controls
	{
	public:
		/// <summary> Creates a standard keyboard input scheme with no bindings. </summary>
		KeyboardControls() : m_keyCodeToCommands(std::map<int32_t, Command>()), m_commandToKeyCodes(std::map<Command, int32_t>()) {}

		/// <summary> Loads key bindings from the file at the given file path. </summary>
		/// <param name="_filePath"> The path of the bindings file. </param>
		void					LoadFromFile(std::string _filePath);

		/// <summary> Gets the key associated with the given command. </summary>
		/// <param name="_command"> The <see cref="Command"/>. </param>
		/// <returns> The key associated with the given command. </returns>
		inline virtual int32_t	GetKeyForCommand(const Command _command)								{ return (m_commandToKeyCodes.find(_command) == m_commandToKeyCodes.end()) ? -1 : m_commandToKeyCodes[_command]; }

		/// <summary> Gets the <see cref="Command"/> associated with the given key code. </summary>
		/// <param name="_keycode"> The key code. </param>
		/// <returns> The command associated with the given key code. </returns>
		inline virtual Command	GetCommandFromKey(const int32_t _keycode)								{ return (m_keyCodeToCommands.find(_keycode) == m_keyCodeToCommands.end()) ? Command::None : m_keyCodeToCommands[_keycode]; }
		
		/// <summary> Binds the given <see cref="Command"/> to the given key code. </summary>
		/// <param name="_command"> The <see cref="Command"/>. </param>
		/// <param name="_keycode"> The key code. </param>
		void					BindCommandToKey(const Command _command, const int32_t _keycode)		{ m_commandToKeyCodes[_command] = _keycode; m_keyCodeToCommands[_keycode] = _command; }

		/// <summary> Unbinds the given <see cref="Command"/> from the given key code. </summary>
		/// <param name="_command"> The <see cref="Command"/>. </param>
		/// <param name="_keycode"> The key code. </param>
		void					UnbindCommandFromKey(const Command _command, const int32_t _keycode)	{ m_commandToKeyCodes.erase(_command); m_keyCodeToCommands.erase(_keycode); }
	private:
		/// <summary> The game commands mapped by key code. </summary>
		std::map<int32_t, Command> m_keyCodeToCommands;

		/// <summary> The key codes mapped by command. </summary>
		std::map<Command, int32_t> m_commandToKeyCodes;
	};
}
#endif