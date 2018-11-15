#pragma once

#include "ILogger.h"
#include <iostream>

class ConsoleLogger : public ILogger
{
public:
	void log(const std::string &s) override
	{
		std::cout << s;
	}
};
