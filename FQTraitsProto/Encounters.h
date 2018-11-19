#pragma once

#include "EncounterBase.h"
#include "Party.h"
#include "Incident.h"
#include "ILogger.h"

class GenericCombatEncounter : public EncounterBase
{
public:
	GenericCombatEncounter(HeroAttrib attrib, unsigned int level, ILogger *logger, const std::string &namePlural) :
		EncounterBase{ attrib, level, logger }, m_namePlural{ namePlural }
	{}
	std::vector<std::unique_ptr<IncidentBase>> resolve(Party *party) override
	{
		std::vector<std::unique_ptr<IncidentBase>> r;

		// Sample Encounter logic. To be modified.

		upLog("\nOh no! Some " + m_namePlural + " have attacked!\n");

		if (party->getPartyAttrib(HeroAttrib::Level) > getLevel())
			upLog("\nThe party is victorious!\n");
		else
			upLog("\nThe party in vanquished...\n");

		return r;
	}
private:
	std::string m_namePlural;
};
