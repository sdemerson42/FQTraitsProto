#include "HeroBase.h"
#include "Profession.h"
#include "Traits.h"

void Hero::setAttrib(HeroAttrib ha, unsigned int val)
{
	if (val > AttMax) val = AttMax;

	switch (ha)
	{
	case HeroAttrib::Affability:
		m_aff = val;
		break;
	case HeroAttrib::Alignment:
		m_align = val;
		break;
	case HeroAttrib::Divine:
		m_div = val;
		break;
	case HeroAttrib::Gear:
		m_gear = val;
		break;
	case HeroAttrib::Health:
		m_health = val;
		break;
	case HeroAttrib::Level:
		m_lev = val;
		break;
	case HeroAttrib::Logic:
		m_logic = val;
		break;
	case HeroAttrib::Lore:
		m_lore = val;
		break;
	case HeroAttrib::Luck:
		m_luck = val;
		break;
	case HeroAttrib::Magical:
		m_mag = val;
		break;
	case HeroAttrib::MentalTough:
		m_mTough = val;
		break;
	case HeroAttrib::Morale:
		m_morale = val;
		break;
	case HeroAttrib::Nature:
		m_nat = val;
		break;
	case HeroAttrib::Physical:
		m_phys = val;
		break;
	case HeroAttrib::PhysTough:
		m_pTough = val;
		break;
	case HeroAttrib::Reputation:
		m_rep = val;
		break;
	case HeroAttrib::Rogue:
		m_rogue = val;
		break;
	};
}

void Hero::modAttrib(HeroAttrib ha, int val)
{
	int mval = (int)getAttrib(ha);
	mval += val;
	if (mval < 0) mval = 0;
	setAttrib(ha, mval);
}

unsigned int Hero::getAttrib(HeroAttrib ha) const
{
	switch (ha)
	{
	case HeroAttrib::Affability:
		return m_aff;
		break;
	case HeroAttrib::Alignment:
		return m_align;
		break;
	case HeroAttrib::Divine:
		return m_div;
		break;
	case HeroAttrib::Gear:
		return m_gear;
		break;
	case HeroAttrib::Health:
		return m_health;
		break;
	case HeroAttrib::Level:
		return m_lev;
		break;
	case HeroAttrib::Logic:
		return m_logic;
		break;
	case HeroAttrib::Lore:
		return m_lore;
		break;
	case HeroAttrib::Luck:
		return m_luck;
		break;
	case HeroAttrib::Magical:
		return m_mag;
		break;
	case HeroAttrib::MentalTough:
		return m_mTough;
		break;
	case HeroAttrib::Morale:
		return m_morale;
		break;
	case HeroAttrib::Nature:
		return m_nat;
		break;
	case HeroAttrib::Physical:
		return m_phys;
		break;
	case HeroAttrib::PhysTough:
		return m_pTough;
		break;
	case HeroAttrib::Reputation:
		return m_rep;
		break;
	case HeroAttrib::Rogue:
		return m_rogue;
		break;
	};
	return 0;
}

void Hero::setReputation(const std::string &name, unsigned int val)
{
	auto *p = &m_reputationMap[name];
	*p = val;
	if (*p > AttMax) *p = AttMax;
}

void Hero::modReputation(const std::string &name, int val)
{
	int mval = m_reputationMap[name];
	mval += val;
	if (mval < 0) mval = 0;
	setReputation(name, (unsigned int)mval);
}

unsigned int Hero::getReputation(const std::string &name) const
{
	auto p = m_reputationMap.find(name);
	if (p != end(m_reputationMap))
		return p->second;

	return AttMax / 2;
}

void Hero::setName(const std::string &name)
{
	m_name = name;
}

const std::string &Hero::getName() const
{
	return m_name;
}

void Hero::setGender(char gender)
{
	m_gender = gender;
}

char Hero::getGender() const
{
	return m_gender;
}

void Hero::initialize(const std::string &name, char gender, const Profession &prof)
{
	const auto &titles = prof.titles();
	const auto &attrib = prof.attrib();

	int x = rand() % titles.size();
	setName(name + " the " + titles[x]);
	setGender(gender);

	for (const auto &data : attrib)
	{
		unsigned int val = rand() % (data.vMax - data.vMin + 1) + data.vMin;
		setAttrib(data.attrib, val);
	}


	m_health = m_pTough;
	m_morale = (int)(.5f * (float)AttMax);
	m_lev = 1;
	m_active = true;
}

HeroAttrib Hero::getBestCoreAttrib() const
{
	HeroAttrib ha{ HeroAttrib::Physical };
	if (getAttrib(HeroAttrib::Magical) > getAttrib(ha))
		ha = HeroAttrib::Magical;
	if (getAttrib(HeroAttrib::Rogue) > getAttrib(ha))
		ha = HeroAttrib::Rogue;
	if (getAttrib(HeroAttrib::Divine) > getAttrib(ha))
		ha = HeroAttrib::Divine;
	if (getAttrib(HeroAttrib::Nature) > getAttrib(ha))
		ha = HeroAttrib::Nature;

	return ha;
}

//Physical, Magical, Rogue, Divine, Nature, Lore, Logic, Luck, Gear, PhysTough, MentalTough, Alignment, Affability,
//Health, Morale, Level, Reputation
