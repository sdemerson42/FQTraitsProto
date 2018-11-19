#include "Party.h"
#include "HeroBase.h"

void Party::initialize(Hero *h1, Hero *h2, Hero *h3, Hero *h4, unsigned int supplies)
{
	m_roster.clear();
	m_roster.push_back(h1);
	m_roster.push_back(h2);
	m_roster.push_back(h3);
	m_roster.push_back(h4);

	for (auto h : m_roster)
	{
		for (auto oh : m_roster)
		{
			if (oh != h)
			{
				h->setReputation(oh->getName(), Hero::AttMax / 2);
			}
		}
	}

	m_loot = 0;
	m_supplies = supplies;
}

int Party::getMorale() const
{
	int morale{ 0 };
	for (auto p : m_roster)
		morale += p->getAttrib(HeroAttrib::Morale);

	for (auto h : m_roster)
	{
		for (auto oh : m_roster)
		{
			if (h != oh)
			{
				auto rep = h->getReputation(oh->getName());
				if (rep <= (int)(0.25f * (float)Hero::AttMax))
					morale -= 5;
				if (rep >= (int)(0.75f * (float)Hero::AttMax))
					morale += 5;
			}
		}
	}
	return morale;
}

void Party::updateLoot(int value)
{
	m_loot += value;
}

std::vector<Hero *> &Party::getRoster()
{
	return m_roster;
}

unsigned int Party::getPartyAttrib(HeroAttrib ha) const
{
	unsigned int r = 0;
	for (auto p : m_roster)
		r += p->getAttrib(ha);
	return r;
}
