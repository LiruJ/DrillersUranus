#include "ConsoleLogger.h"

#include <iostream>

/// <summary> Writes to the console logger. </summary>
/// <param name="_input"> The string to write. </param>
void Logging::ConsoleLogger::Log(std::string _input)
{
	std::cout << _input << std::endl;
}
