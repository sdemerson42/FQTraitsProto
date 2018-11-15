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

	ist >> s;
	ad.attrib = HeroAttrib::Physical;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Magical;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Rogue;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Divine;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Nature;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Lore;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Logic;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Luck;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Gear;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::PhysTough;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::MentalTough;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Alignment;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);
	ist >> s;
	ad.attrib = HeroAttrib::Affability;
	ad.value = stoi(s);
	prof.m_attrib.push_back(ad);

	return ist;
}

//Physical, Magical, Rogue, Divine, Nature, Lore, Logic, Luck, Gear, PhysTough, MentalTough, Alignment, Affability,
//Health, Morale, Level, Reputation