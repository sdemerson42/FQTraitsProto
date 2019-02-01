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
	IncidentPartyInfighting(Hero *att, Hero *def) :
		m_att{ att }, m_def{ def }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_att;
	Hero *m_def;
};

class IncidentDeath : public IncidentBase
{
public:
	IncidentDeath(Hero *dead) :
		m_dead{ dead }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_dead;
};

class IncidentPoison : public IncidentBase
{
public:
	IncidentPoison(Hero *poisoned) :
		m_poisoned{ poisoned }
	{}
	void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) override;
private:
	Hero *m_poisoned;
};

