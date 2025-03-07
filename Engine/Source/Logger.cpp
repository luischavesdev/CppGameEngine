#include <iostream>
#include "Logger.h"

void Logger::Log(const std::string& message)
{
	std::cout << message << "\n";
}
