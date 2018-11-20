#pragma once

#include "Incident.h"

class Hero;

class IncidentTheft : public IncidentBase
{
public:
	IncidentTheft(Hero *thief, Hero *observer) :
		m_thief{ thief }, m_observer{ observer }
	{}
	std::string resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_thief;
	Hero *m_observer;
};

class IncidentWounded : public IncidentBase
{
public:
	IncidentWounded(Hero *wounded) :
		m_wounded{ wounded }
	{}
	std::string resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_wounded;
};
