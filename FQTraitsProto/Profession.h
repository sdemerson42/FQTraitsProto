#pragma once

#include <vector>
#include <string>
#include "Globals.h"
#include <iostream>

class Profession
{
	friend std::istream &operator>>(std::istream &ist, Profession &prof);
public:
	const std::string &name() const
	{
		return m_name;
	}
	const std::vector<std::string> &titles() const
	{
		return m_title;
	}
	const std::vector<unsigned int> &attrib() const
	{
		return m_attrib;
	}
private:
	std::string m_name;
	std::vector<std::string> m_title;
	std::vector<unsigned int> m_attrib;
};
