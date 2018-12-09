#pragma once

#include "TraitBase.h"

#include "Incidents.h"
#include "Party.h"

class TraitKlepto : public TraitBase
{
public:
	TraitKlepto() :
		TraitBase{ "Kleptomaniac" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
	void initialize(Hero *) override;
};

class TraitHotheaded : public TraitBase
{
public:
	TraitHotheaded() :
		TraitBase{ "Hotheaded" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
};

class TraitCowardly : public TraitBase
{
public:
	TraitCowardly() :
		TraitBase{ "Cowardly" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
};

class TraitGoody : public TraitBase
{
public:
	TraitGoody() :
		TraitBase{ "Goody Two Shoes" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
};

class TraitVengeful : public TraitBase
{
public:
	TraitVengeful() :
		TraitBase{ "Vengeful" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

class TraitEgotistical : public TraitBase
{
public:
	TraitEgotistical() :
		TraitBase{ "Egotistical" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
};

class TraitSkeptical : public TraitBase
{
public:
	TraitSkeptical() :
		TraitBase{ "Skeptical" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override
	{
	}
};

class TraitBossy : public TraitBase
{
public:
	TraitBossy() :
		TraitBase{ "Bossy" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

class TraitBloodthirsty : public TraitBase
{
public:
	TraitBloodthirsty() :
		TraitBase{ "Bloodthirsty" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

class TraitPious : public TraitBase
{
public:
	TraitPious() :
		TraitBase{ "Pious" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

class TraitHaunted : public TraitBase
{
public:
	TraitHaunted() :
		TraitBase{ "Haunted" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

class TraitDiplomatic : public TraitBase
{
public:
	TraitDiplomatic() :
		TraitBase{ "Diplomatic" }
	{}
	void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) override;
};

