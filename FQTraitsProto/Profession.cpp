#include "Profession.h"

std::istream &operator >> (std::istream &ist, Profession &prof)
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