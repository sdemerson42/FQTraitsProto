#pragma once

#include "TraitBase.h"

#include "Encounters.h"
#include "Incident.h"
#include "Party.h"
#include "HeroBase.h"

class TraitKlepto : public TraitBase
{
public:
	TraitKlepto() :
		TraitBase{ "Kleptomaniac" }
	{}
	void doEncounterPhase(EncounterBase *, Party *) override
	{
	}
	void doLootPhase(EncounterBase *, Party *) override
	{
	}
	void doIncidentPhase(IncidentBase *, Party *) override
	{
	}
};

class TraitHotheaded : public TraitBase
{
public:
	TraitHotheaded() :
		TraitBase{ "Hotheaded" }
	{}
	void doEncounterPhase(EncounterBase *, Party *) override
	{
	}
	void doLootPhase(EncounterBase *, Party *) override
	{
	}
	void doIncidentPhase(IncidentBase *, Party *) override
	{
	}
};

class TraitCowardly : public TraitBase
{
public:
	TraitCowardly() :
		TraitBase{ "Cowardly" }
	{}
	void doEncounterPhase(EncounterBase *, Party *) override
	{
	}
	void doLootPhase(EncounterBase *, Party *) override
	{
	}
	void doIncidentPhase(IncidentBase *, Party *) override
	{
	}
};

class TraitGoody : public TraitBase
{
public:
	TraitGoody() :
		TraitBase{ "Goody Two Shoes" }
	{}
	void doEncounterPhase(EncounterBase *, Party *) override
	{
	}
	void doLootPhase(EncounterBase *, Party *) override
	{
	}
	void doIncidentPhase(IncidentBase *, Party *) override
	{
	}
};


