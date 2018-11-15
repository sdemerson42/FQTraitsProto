#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Profession.h"
#include "HeroBase.h"

class ILogger;

class SimState
{
public:
	SimState();
	~SimState();
	void execute();
private:
	std::vector<Profession> m_profession;
	struct HeroNameData
	{
		std::string name;
		char gender;
	};
	std::vector<HeroNameData> m_heroName;
	std::unique_ptr<ILogger> m_logger;
	std::vector<Hero> m_hero;
};
