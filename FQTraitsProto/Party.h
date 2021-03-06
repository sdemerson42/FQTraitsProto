#pragma once

#include <vector>
#include "Globals.h"

class Hero;

class Party
{
public:
	void initialize(Hero *h1, Hero *h2, Hero *h3, Hero *h4, unsigned int supplies);
	void updateLoot(int value);
	std::vector<Hero *> &getRoster();
	std::vector<Hero *> getActiveRoster();
	Hero *getActiveHeroWithTrait(const std::string &);
	Hero *getHeroWithBestAttrib(HeroAttrib attrib);
	int getMorale() const;
	unsigned int getBestAttribTotal() const;
	void activateParty();
	void modAttrib(HeroAttrib attrib, int val);
	void addLoot(unsigned int val)
	{
		m_loot += val;
	}
	unsigned int getLoot() const
	{
		return m_loot;
	}
	unsigned int getSupplies() const
	{
		return m_supplies;
	}
	unsigned int getPartyAttrib(HeroAttrib) const;
private:
	std::vector<Hero *> m_roster;
	unsigned int m_loot;
	unsigned int m_supplies;
};
