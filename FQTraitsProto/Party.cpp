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

				// Modify based on Affability and Alignment differences

				int affMod = ((int)oh->getAttrib(HeroAttrib::Affability) - ((int)Hero::AttMax / 2)) / 3;
				int alMod = abs((int)((int)oh->getAttrib(HeroAttrib::Alignment) - (int)h->getAttrib(HeroAttrib::Alignment)));
				alMod = (2 - (alMod / 4));

				h->modReputation(oh->getName(), affMod, true);
				h->modReputation(oh->getName(), alMod, true);
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
		if (p->getActive())
			morale += p->getAttrib(HeroAttrib::Morale);

	for (auto h : m_roster)
	{
		for (auto oh : m_roster)
		{
			if (h != oh && h->getActive() && oh->getActive())
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

std::vector<Hero *> Party::getActiveRoster()
{
	std::vector<Hero *> r;
	for (auto p : m_roster)
		if (p->getActive())
			r.push_back(p);
	return r;
}

Hero *Party::getActiveHeroWithTrait(const std::string &trait)
{
	for (auto p : m_roster)
		if (p->hasTrait(trait) && p->getActive())
			return p;
	return nullptr;
}

unsigned int Party::getPartyAttrib(HeroAttrib ha) const
{
	unsigned int r = 0;
	for (auto hp : m_roster)
		if (hp->getActive())
			r += hp->getAttrib(ha);
	return r;
}

unsigned int Party::getBestAttribTotal() const
{
	unsigned int r{ 0 };
	for (auto hp : m_roster)
		if (hp->getActive())
			r += hp->getBestCoreAttribValue();
	return r;
}

void Party::activateParty()
{
	for (auto hp : m_roster)
		hp->setActive(true);
}

void Party::modAttrib(HeroAttrib attrib, int val)
{
	for (auto hp : getActiveRoster())
	{
		hp->modAttrib(attrib, val);
	}
}
