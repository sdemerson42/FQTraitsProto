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

		for (auto tp : h.getTraits())
		{
			tp->initialize(&h);
		}

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
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 4, m_logger.get(), "Goblins"));
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 5, m_logger.get(), "Troglodytes"));
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 6, m_logger.get(), "Dullards"));
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 7, m_logger.get(), "Zombies"));
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 8, m_logger.get(), "Trolls"));
	m_encounter.push_back(std::make_unique<GenericCombatEncounter>(HeroAttrib::Physical, 9, m_logger.get(), "Real Bastards"));
}

void SimState::createTraits()
{
	m_trait.push_back(std::make_unique<TraitCowardly>());
	m_trait.push_back(std::make_unique<TraitGoody>());
	m_trait.push_back(std::make_unique<TraitHotheaded>());
	m_trait.push_back(std::make_unique<TraitKlepto>());
	m_trait.push_back(std::make_unique<TraitVengeful>());

	//m_trait.push_back(std::make_unique<TraitEgotistical>());
	//m_trait.push_back(std::make_unique<TraitSkeptical>());
	m_trait.push_back(std::make_unique<TraitBossy>());
	m_trait.push_back(std::make_unique<TraitBloodthirsty>());
	m_trait.push_back(std::make_unique<TraitPious>());

	m_trait.push_back(std::make_unique<TraitHaunted>());
	m_trait.push_back(std::make_unique<TraitDiplomatic>());


	upLog("Traits created...\n");
}

void SimState::runSim(int level, int size, HeroAttrib primaryAttrib, HeroAttrib secondaryAttrib)
{
	upLog("\nBeginning simulation...\n\n");

	int day = 0;

	while (day < size)
	{

		upLog("Day " + std::to_string(day + 1) + ":\n\n");

		// Select and play an Encounter

		int incIndex;
		while (true)
		{
			incIndex = rand() % m_encounter.size();
			if (abs(level - (int)m_encounter[incIndex]->getLevel()) <= 5)
				break;
		}

		auto incidents = m_encounter[incIndex]->resolve(&m_party);
		// (Remove Incident card from deck)
		m_encounter.erase(std::begin(m_encounter) + incIndex);

		// Campfire Traits behavior...

		upLog("\nThat evening 'round the campfire:\n\n");

		for (auto hp : m_party.getActiveRoster())
			for (auto tp : hp->getTraits())
				tp->doIncidentPhase(hp, &m_party, incidents);

		// Resolve Incidents...

		for (int i = 0; i < incidents.size(); ++i)
		{
			incidents[i]->resolve(&m_party, incidents);
		}
		
		// Failure checks...

		if (m_party.getActiveRoster().size() == 0)
		{
			upLog("\n\n*** The party has been destroyed ***\n\n");
			return;
		}

		if (m_party.getPartyAttrib(HeroAttrib::Morale) < Hero::AttMax * 4 / 5)
		{
			upLog("\n\n*** The party is too disheartened to continue and abandons the quest ***\n\n");
			return;
		}

		upLog("{The party eventually goes to sleep/Guard is posted and the party rests/The party dines on disgusting rations and turns in for the night}.\n\n");
		
		++day;
	}

	// Victory!

	upLog("\n\n*** The party is victorious! ***\n\n");
	
}

void SimState::execute()
{
	IncidentBase::setLogger(m_logger.get());
	TraitBase::setLogger(m_logger.get());
	createTraits();
	createHeroRoster(4);
	createParty();
	createEncounters();
	runSim(5, 5, HeroAttrib::Physical, HeroAttrib::Magical);
}