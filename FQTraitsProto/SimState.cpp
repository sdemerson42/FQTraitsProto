#include "SimState.h"
#include <fstream>
#include <iostream>

SimState::SimState()
{
	std::cout << "SimState initializing...\n";
	std::ifstream ifs{ "Data/Professions.txt" };
	while (true)
	{
		Profession prof;
		ifs >> prof;
		if (!ifs) break;
		m_profession.push_back(std::make_unique<Profession>(prof));
	}
	std::cout << "Professions loaded...\n";
}

SimState::~SimState()
{
	std::cout << "SimState destructing...\n";
}