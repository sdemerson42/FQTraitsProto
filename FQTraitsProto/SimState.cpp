#include "SimState.h"
#include <fstream>
#include <iostream>
#include "ConsoleLogger.h"
#include "Encounters.h"

SimState::SimState()
{
	// Set up logger

	m_logger = std::make_unique<ConsoleLogger>();

	// Load Data

	m_logger->log("SimState initializing...\n");
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
	m_logger->log("Professions loaded...\n");

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
	m_logger->log("Hero names loaded...\n");
}

SimState::~SimState()
{
	m_logger->log("SimState destructing...\n");
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
		m_hero.push_back(h);
	}

	m_logger->log("\n==== Hero Roster ====\n\n");
	for (const auto &h : m_hero)
	{
		m_logger->log(h.getName() + '\n');
	}
}

void SimState::createParty()
{
	m_party.initialize(&m_hero[0], &m_hero[1], &m_hero[2], &m_hero[3], 10);
	m_logger->log("Party morale: " + std::to_string(m_party.getMorale()));
	m_logger->log("\nParty health: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Health)));
	m_logger->log("\nParty Level: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Level)));
	m_logger->log("\nParty Gear: " + std::to_string(m_party.getPartyAttrib(HeroAttrib::Gear)));
}

void SimState::createEncounters()
{
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 1, m_logger.get(), "Goblins"));
}

void SimState::execute()
{
	createHeroRoster(4);
	createParty();
	createEncounters();
}