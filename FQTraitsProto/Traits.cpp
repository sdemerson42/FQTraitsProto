#include "Traits.h"
#include "HeroBase.h"

void TraitKlepto::initialize(Hero *h) 
{
	h->modAttrib(HeroAttrib::Rogue, rand() % 3 + 3);
}

void TraitVengeful::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &iv)
{
	// Revenge!

	for (auto hp : party->getActiveRoster())
	{
		if (hp != owner && owner->getReputation(hp->getName()) == 0)
		{
			upLog(owner->getName() + " decides {to take bloody vengeance on/that it's payback time for} " + hp->getName() + "!\n");
			owner->setReputation(hp->getName(), Hero::AttMax / 2);
			iv.push_back(std::make_unique<IncidentPartyInfighting>(owner, hp));
		}
	}
}