#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Profession.h"
#include "HeroBase.h"
#include "Party.h"

class ILogger;
class EncounterBase;
class TraitBase;

class SimState
{
public:
	SimState();
	~SimState();
	void execute();
	void upLog(const std::string &) const;
private:
	void createHeroRoster(int total);
	void createParty();
	void createEncounters();
	void createTraits();
	void runSim(int level, int size, HeroAttrib primaryAttrib, HeroAttrib secondaryAttrib);
	std::vector<Profession> m_profession;
	struct HeroNameData
	{
		std::string name;
		char gender;
	};
	std::vector<HeroNameData> m_heroName;
	std::unique_ptr<ILogger> m_logger;
	std::vector<Hero> m_hero;
	Party m_party;
	std::vector<std::unique_ptr<EncounterBase>> m_encounter;
	std::vector<std::unique_ptr<TraitBase>> m_trait;
};
