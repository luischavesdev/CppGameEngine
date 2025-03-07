#pragma once
#include <string>

class Logger
{
public:
	static void Log(const std::string& message);
};

#define CUSTOM_LOGGER(...) Logger::Log(__VA_ARGS__)

#ifdef RELEASE
#define CUSTOM_LOGGER
#endif