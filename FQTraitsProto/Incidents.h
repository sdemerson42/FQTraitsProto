#pragma once

#include "Incident.h"

class Hero;

class IncidentTheft : public IncidentBase
{
public:
	IncidentTheft(Hero *thief, Hero *observer) :
		m_thief{ thief }, m_observer{ observer }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_thief;
	Hero *m_observer;
};

class IncidentWounded : public IncidentBase
{
public:
	IncidentWounded(Hero *wounded, bool serious = false) :
		m_wounded{ wounded }, m_serious{ serious }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_wounded;
	bool m_serious;
};

class IncidentFlee : public IncidentBase
{
public:
	IncidentFlee(Hero *hero) :
		m_hero{ hero }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_hero;
};

class IncidentPartyInfighting : public IncidentBase
{
public:
	IncidentPartyInfighting(Hero *att, Hero *wound, bool fatal) :
		m_attacker{ att }, m_wounded{ wound }, m_fatal{ fatal }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_attacker;
	Hero *m_wounded;
	bool m_fatal;
};
