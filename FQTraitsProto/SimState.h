#pragma once

#include <vector>
#include <memory>
#include "Profession.h"

class SimState
{
public:
	SimState();
	~SimState();
private:
	std::vector<std::unique_ptr<Profession>> m_profession;
};
