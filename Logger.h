#ifndef LOGGER_H
#define LOGGER_H

// Utility includes.
#include <string>

namespace Logging
{
	/// <summary> Represents a logging system. </summary>
	class Logger
	{
	public:
		virtual ~Logger() {}
		
		/// <summary> Logs the given string. </summary>
		/// <param name="_input"> The string to log. </param>
		virtual void Log(std::string _input) = 0;
	};
}

#endif
