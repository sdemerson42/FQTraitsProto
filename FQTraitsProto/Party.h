#pragma once

#include <vector>
#include "HeroBase.h"

class Hero;

class Party
{
public:
	void initialize(Hero *h1, Hero *h2, Hero *h3, Hero *h4, unsigned int supplies);
	void updateMorale();
	void updateHealth();
	void updateLoot(int value);
	std::vector<Hero *> &getRoster();
	unsigned int getMorale() const
	{
		return m_morale;
	}
	unsigned int getLoot() const
	{
		return m_loot;
	}
	unsigned int getSupplies() const
	{
		return m_supplies;
	}
	unsigned int getHealth() const
	{
		return m_health;
	}
private:
	std::vector<Hero *> m_roster;
	unsigned int m_morale;
	unsigned int m_loot;
	unsigned int m_supplies;
	unsigned int m_health;
};
