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

std::istream &operator>>(std::istream &ist, Profession &prof)
{
	std::string s;
	if (!(ist >> s))
	{
		return ist;
	}

	prof.m_name = s;
	while (true)
	{
		ist >> s;
		if (s == "*") break;
		prof.m_title.emplace_back(s);
	}

	for (int i = 0; i < (int)HeroAttrib::Total - 4; ++i)
	{
		ist >> s;
		prof.m_attrib.push_back(std::stoi(s));
	}

	return ist;
}

//Physical, Magical, Rogue, Divine, Nature, Lore, Logic, Luck, Gear, PhysTough, MentalTough, Alignment, Affability,
//Health, Morale, Level, Reputation