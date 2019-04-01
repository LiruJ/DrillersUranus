#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

// Derived includes.
#include "Logger.h"

// Utility includes.
#include <iostream>

namespace Logging
{
	/// <summary> Represents a logger that logs to the standard console. </summary>
	class ConsoleLogger : public Logger
	{
	public:
		/// <summary> Logs the given string to the standard console. </summary>
		/// <param name="_input"> The string to log. </param>
		virtual void Log(std::string _input) { std::cout << _input << std::endl; }
	};
}
#endif