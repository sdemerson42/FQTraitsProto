#pragma once

#include "Globals.h"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Traits.h"

class Profession;

class Hero
{
public:
	void initialize(const std::string &, char, const Profession &);
	void setAttrib(HeroAttrib, unsigned int);
	void modAttrib(HeroAttrib, int);
	unsigned int getAttrib(HeroAttrib) const;
	void setReputation(const std::string &, unsigned int);
	void modReputation(const std::string &, int, bool init = false);
	unsigned int getReputation(const std::string &) const;
	void setName(const std::string &);
	const std::string &getName() const;
	void setGender(char);
	char getGender() const;
	std::string gp(const std::string &s) const
	{
		if (s == "1")
		{
			return m_gender == 'M' ? "he" : "she";
		}
		if (s == "2")
		{
			return m_gender == 'M' ? "him" : "her";
		}
		if (s == "p")
		{
			return m_gender == 'M' ? "his" : "her";
		}
		if (s == "1c")
		{
			return m_gender == 'M' ? "He" : "She";
		}
		if (s == "2c")
		{
			return m_gender == 'M' ? "Him" : "Her";
		}
		if (s == "pc")
		{
			return m_gender == 'M' ? "His" : "Her";
		}
		return "";
	}
	HeroAttrib getBestCoreAttrib() const;
	unsigned int getBestCoreAttribValue() const;
	void addTrait(TraitBase *tp)
	{
		m_trait.push_back(tp);
	}
	const std::vector<TraitBase *> &getTraits() const
	{
		return m_trait;
	}
	bool hasTrait(const std::string &tname) const
	{
		for (auto tp : m_trait)
			if (tp->name() == tname)
				return true;
		return false;
	}
	
	bool getActive() const
	{
		return m_active;
	}
	void setActive(bool state)
	{
		m_active = state;
	}

	static const unsigned int AttMax = 25;
private:
	std::string m_name;
	char m_gender;
	std::map<std::string, unsigned int> m_reputationMap;
	std::vector<TraitBase *> m_trait;
	// Attributes
	unsigned int m_phys;
	unsigned int m_mag;
	unsigned int m_rogue;
	unsigned int m_div;
	unsigned int m_nat;
	unsigned int m_lore;
	unsigned int m_logic;
	unsigned int m_luck;
	unsigned int m_gear;
	unsigned int m_pTough;
	unsigned int m_mTough;
	unsigned int m_align;
	unsigned int m_aff;
	unsigned int m_health;
	unsigned int m_morale;
	unsigned int m_lev;
	unsigned int m_rep;

	bool m_active;
};

