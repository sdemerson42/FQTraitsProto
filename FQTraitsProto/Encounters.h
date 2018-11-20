#pragma once

#include "EncounterBase.h"
#include "Party.h"
#include "Incidents.h"
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

		upLog("\nOh no! Some " + m_namePlural + " have {attacked/pounced/appeared}!\n");

		int bonus{ 0 };

		

		if (party->getPartyAttrib(HeroAttrib::Level) + bonus > getLevel())
		{
			upLog("The party {beats them senseless/gives them a stern talking-to/does terrible, terrible things to them}!\n");

			// Hotheaded check

			for (auto hp : party->getRoster())
			{
				if (hp->hasTrait("Hotheaded"))
				{
					upLog(hp->getName() + " charges heedlessly into battle, ");
					int x = rand() % 10;
					if (x < hp->getAttrib(HeroAttrib::Physical))
					{
						upLog("cutting a glorious, bloody path through the enemy!\n");
						bonus += 1;
					}
					else
					{
						upLog("tripping over some {broken furniture/skulls/crockery} and receiving an injury...\n");
						bonus -= 1;
						r.push_back(std::make_unique<IncidentWounded>(hp));
					}
				}
			}

			unsigned int loot = getLevel() * rand() % 20 + 10;
			upLog("After {searching/desecrating/inspecting} the {corpses/bodies/bloody mess remaining} the party finds " + std::to_string(loot) + " loot!\n");

			// Klepto Check

			for (auto hp : party->getRoster())
			{
				if (hp->hasTrait("Kleptomaniac"))
				{
					int roll = rand() % 3;
					if (roll == 0)
					{
						upLog(hp->getName() + " {pilfers/steals/swipes/nabs/pockets} some loot on the sly!\n");
						loot -= loot / 5;

						// Caught?

						for (auto hp2 : party->getRoster())
						{
							if (hp2 != hp && hp2->hasTrait("Goody Two Shoes"))
							{
								upLog(hp2->getName() + " catches " + hp->getName() + " in the act and is pretty unhappy...\n");
								r.push_back(std::make_unique<IncidentTheft>(hp, hp2));
								break;
							}
						}

					}
				}
			}

			upLog("The party gains " + std::to_string(loot) + " loot.\n");
			party->addLoot(loot);


		}
		else
			upLog("\nThe party is vanquished...\n");

		return r;
	}
private:
	std::string m_namePlural;
};
