#pragma once

#include "ILogger.h"
#include <fstream>
#include <iostream>

class DualLogger : public ILogger
{
public:
	DualLogger(const std::string &fName) :
		m_fName{ fName }
	{}
	void log(const std::string &s) override
	{
		std::ofstream ofs{ m_fName, std::ios_base::app };
		ofs << s;
		std::cout << s;
	}
private:
	std::string m_fName;
};
