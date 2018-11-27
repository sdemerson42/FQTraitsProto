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
	Hero *getHeroWithTrait(const std::string &);
	int getMorale() const;
	unsigned int getBestAttribTotal() const;
	void activateParty();
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
