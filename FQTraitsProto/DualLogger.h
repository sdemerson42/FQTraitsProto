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
		auto ss = parse(s);
		std::ofstream ofs{ m_fName, std::ios_base::app };
		ofs << ss;
		std::cout << ss;
	}
private:
	std::string m_fName;
};
