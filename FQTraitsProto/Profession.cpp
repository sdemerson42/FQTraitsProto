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

	Profession::AttribData ad;

	std::string s2;

	ist >> s >> s2;
	ad.attrib = HeroAttrib::Physical;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Magical;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Rogue;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Divine;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Nature;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Lore;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Logic;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Luck;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Gear;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::PhysTough;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::MentalTough;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Alignment;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);
	ist >> s >> s2;
	ad.attrib = HeroAttrib::Affability;
	ad.vMin = stoi(s);
	ad.vMax = stoi(s2);
	prof.m_attrib.push_back(ad);

	return ist;
}

//Physical, Magical, Rogue, Divine, Nature, Lore, Logic, Luck, Gear, PhysTough, MentalTough, Alignment, Affability,
//Health, Morale, Level, Reputation