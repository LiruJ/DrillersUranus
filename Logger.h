#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Logging
{
	class Logger
	{
	public:
		virtual ~Logger() {}
		
		virtual void Log(std::string _input) = 0;
	};
}

#endif
