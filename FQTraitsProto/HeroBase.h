#pragma once

#include "Globals.h"
#include <string>
#include <map>

class Profession;

class Hero
{
public:
	void initialize(const std::string &, char, const Profession &);
	void setAttrib(HeroAttrib, unsigned int);
	void modAttrib(HeroAttrib, int);
	unsigned int getAttrib(HeroAttrib) const;
	void setReputation(const std::string &, unsigned int);
	void modReputation(const std::string &, int);
	unsigned int getReputation(const std::string &) const;
	void setName(const std::string &);
	const std::string &getName() const;
	void setGender(char);
	char getGender() const;
private:
	std::string m_name;
	char m_gender;
	std::map<std::string, unsigned int> m_reputationMap;
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
};

