#include "SimState.h"
#include <fstream>
#include <iostream>
#include "ConsoleLogger.h"
#include "Encounters.h"
#include "Traits.h"

SimState::SimState()
{
	// Set up logger

	m_logger = std::make_unique<ConsoleLogger>();

	// Load Data

	upLog("SimState initializing...\n");
	std::ifstream ifs{ "Data/Professions.txt" };
	while (true)
	{
		Profession prof;
		ifs >> prof;
		if (!ifs)
		{
			ifs.clear();
			break;
		}
		m_profession.push_back(prof);
	}
	upLog("Professions loaded...\n");

	ifs.close();
	ifs.open("Data/HeroNames.txt");

	while (true)
	{
		std::string s;
		if (!(ifs >> s))
		{
			ifs.clear();
			break;
		}
		HeroNameData data;
		data.name = s;
		ifs >> data.gender;
		m_heroName.push_back(data);
	}
	upLog("Hero names loaded...\n");
}

SimState::~SimState()
{
	upLog("SimState destructing...\n");
}

void SimState::upLog(const std::string &s) const
{
	m_logger->log(s);
}

void SimState::createHeroRoster(int total)
{
	m_hero.clear();

	for (int i = 0; i < total; ++i)
	{
		Hero h;
		int x = rand() % m_heroName.size();
		int y = rand() % m_profession.size();
		h.initialize(m_heroName[x].name, m_heroName[x].gender, m_profession[y]);
		m_heroName.erase(begin(m_heroName) + x);

		int z = rand() % m_trait.size();
		h.addTrait(m_trait[z].get());

		m_hero.push_back(h);
	}

	upLog("\n==== Hero Roster ====\n\n");
	for (const auto &h : m_hero)
	{
		upLog(h.getName() + '\n');
		auto tl = h.getTraits();
		for (auto tp : tl)
			upLog("(" + tp->name() + ")\n");
	}
}

void SimState::createParty()
{
	m_party.initialize(&m_hero[0], &m_hero[1], &m_hero[2], &m_hero[3], 10);
	upLog("Party morale: " + std::to_string(m_party.getMorale()));
	upLog("\nParty health: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Health)));
	upLog("\nParty Level: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Level)));
	upLog("\nParty Gear: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Gear)));
}

void SimState::createEncounters()
{
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 1, m_logger.get(), "Goblins"));
}

void SimState::createTraits()
{
	m_trait.push_back(std::make_unique<TraitCowardly>());
	m_trait.push_back(std::make_unique<TraitGoody>());
	m_trait.push_back(std::make_unique<TraitHotheaded>());
	m_trait.push_back(std::make_unique<TraitKlepto>());
	upLog("Traits created...\n");
}

void SimState::execute()
{
	createTraits();
	createHeroRoster(4);
	createParty();
	createEncounters();

	upLog("\nBeginning simulation...\n\nDay 1 in the dungeon:");
	auto incidents = m_encounter[0]->resolve(&m_party);

	upLog("\n\nThat evening 'round the campfire:\n");

	for (auto &upi : incidents)
	{
		auto s = upi->resolve(&m_party, incidents);
		upLog(s);
	}
}