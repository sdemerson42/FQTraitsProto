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

class TraitVengeful : public TraitBase
{
public:
	TraitVengeful() :
		TraitBase{ "Vengeful" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitFaceblind : public TraitBase
{
public:
	TraitFaceblind() :
		TraitBase{ "Face Blind" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitSkeptical : public TraitBase
{
public:
	TraitSkeptical() :
		TraitBase{ "Skeptical" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitBossy : public TraitBase
{
public:
	TraitBossy() :
		TraitBase{ "Bossy" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitBloodthirsty : public TraitBase
{
public:
	TraitBloodthirsty() :
		TraitBase{ "Bloodthirsty" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitPious : public TraitBase
{
public:
	TraitPious() :
		TraitBase{ "Pious" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitHaunted : public TraitBase
{
public:
	TraitHaunted() :
		TraitBase{ "Haunted" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

class TraitDiplomatic : public TraitBase
{
public:
	TraitDiplomatic() :
		TraitBase{ "Diplomatic" }
	{}
	void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &iv) override
	{
	}
};

