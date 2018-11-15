#include "SimState.h"
#include <fstream>
#include <iostream>
#include "ConsoleLogger.h"

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

void SimState::execute()
{
	for (int i = 0; i < 4; ++i)
	{
		Hero h;
		int x = rand() % m_heroName.size();
		int y = rand() % m_profession.size();
		h.initialize(m_heroName[x].name, m_heroName[x].gender, m_profession[y]);
		m_hero.push_back(h);
	}

	m_logger->log("\n==== Hero Roster ====\n\n");
	for (const auto &h : m_hero)
	{
		m_logger->log(h.getName() + '\n');
	}
}