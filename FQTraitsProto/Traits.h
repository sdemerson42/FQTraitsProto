#pragma once

#include "TraitBase.h"

#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

class TraitKlepto : public TraitBase
{
public:
	TraitKlepto() :
		TraitBase{ "Kleptomaniac" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitHotheaded : public TraitBase
{
public:
	TraitHotheaded() :
		TraitBase{ "Hotheaded" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitCowardly : public TraitBase
{
public:
	TraitCowardly() :
		TraitBase{ "Cowardly" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitGoody : public TraitBase
{
public:
	TraitGoody() :
		TraitBase{ "Goody Two Shoes" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};


