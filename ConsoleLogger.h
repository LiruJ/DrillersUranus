#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Logger.h"

namespace Logging
{
	class ConsoleLogger : public Logger
	{
	public:


		virtual void Log(std::string _input);
	};


}
#endif