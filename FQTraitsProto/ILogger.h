#pragma once

#include <string>

class ILogger
{
public:
	virtual ~ILogger()
	{}
	virtual void log(const std::string &) = 0;
protected:
	std::string parse(const std::string &s);
};
