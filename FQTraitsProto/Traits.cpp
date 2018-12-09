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

void TraitBossy::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// Chance to give orders

	int roll = rand() % 4;

	if (roll == 0)
	{
		upLog(owner->getName() + " {begins to bark orders at everyone/demands that the party perform drills before dinner/micromanages the firebuilding process}.\n");

		for (auto hp : party->getActiveRoster())
		{
			// 50 % chance + reputation check...
			if (hp->getReputation(owner->getName()) + rand() % 5 + 1 > Hero::AttMax / 2 && rand() % 2 == 0)
			{
				// Morale improved
				upLog(hp->getName() + " {feel inspired/appreciates the effort/likes orderliness/tolerates this behavior} and " + hp->gp("p") + " morale improves.\n");
				hp->modAttrib(HeroAttrib::Morale, 2);
			}
			else if ((int)hp->getReputation(owner->getName()) - (rand() % 5 + 1) <= Hero::AttMax / 5)
			{
				// Annoyed
				upLog(hp->getName() + " {is irritated/is not in the mood/doesn't take orders well} and loses morale.\n");
				hp->modAttrib(HeroAttrib::Morale, -1);
			}
		}
	}
}

void TraitBloodthirsty::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// Chance to do ill-advised night hunting...
	int roll = rand() % 4;
	if (roll == 0)
	{
		std::string oName{ owner->getName() };
		upLog(oName + " {stalks off to do some hunting/sneaks off to find something to kill/is restless and slips away from camp}...\n");

		roll = rand() % 3;

		if (roll == 0)
		{
			// Success
			upLog(owner->gp("1c") + " returns to camp {smiling and covered with entrails/bloody and happy/with a brand new severed head}. " + owner->gp("pc") + " morale improves!\n");
			owner->modAttrib(HeroAttrib::Morale, 2);
		}
		else if (roll == 1)
		{
			// No effect
			upLog(owner->gp("1c") + " {soon returns without incident/has no luck/comes back empty-handed}.\n");
		}
		else
		{
			// Uh-oh...
			upLog(owner->gp("1c") + " returns {pursued by dungeon wolves/, chased by giant ants/with a horde of imps in hot pursuit}!\n");
			if (rand() % 2 == 0)
			{
				// Reputaton damage
				upLog("The party {fends off the monsters/shoos the creatures away with a broom/yells at them until they leave}, but they're not happy with " + oName + "!\n");

				for (auto hp : party->getActiveRoster())
				{
					if (hp != owner)
					{
						hp->modReputation(oName, -1);
					}
				}
			}
			else
			{
				// Injury
				int vi{ 0 };
				while (true)
				{
					vi = rand() % party->getActiveRoster().size();
					if (party->getActiveRoster()[vi] != owner)
						break;
				}
				auto ih = party->getActiveRoster()[vi];
				upLog("Unfortunately, " + ih->getName() + " {was injured/got pulverized/was gnawed on/was emotionally crippled} during the fighting.\n");
				incident.push_back(std::make_unique<IncidentWounded>(ih));
			}
		}
	}
}

void TraitPious::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// Chance to deliver a sermon

	int roll = rand() % 4;

	if (roll == 0)
	{
		upLog(owner->getName() + " {delights the party with a dull parable/delivers a sermon on proper dental care/preaches against fornication with pixies/gives the party a condescending pep talk}.\n");

		for (auto hp : party->getActiveRoster())
		{
			// 50 % chance + Divinity check OR automatic if Goody Two Shoes
			if ((hp->getAttrib(HeroAttrib::Divine) + rand() % 10 + 1 > Hero::AttMax / 2 && rand() % 2 == 0) || hp->hasTrait("Goody Two Shoes"))
			{
				// Morale improved
				upLog(hp->getName() + " {feel inspired/appreciates the effort/is feeling devout this evening/tolerates this behavior} and " + hp->gp("p") + " morale improves.\n");
				hp->modAttrib(HeroAttrib::Morale, 2);
			}
			else if (rand() % 2 == 0)
			{
				// Annoyed
				upLog(hp->getName() + " {is irritated/becomes sullen/curses the gods} and loses morale.\n");
				hp->modAttrib(HeroAttrib::Morale, -1);
			}
		}
	}
}

void TraitHaunted::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// Chance of a ghostly visitation...
	int roll = rand() % 4;
	if (roll == 0)
	{
		upLog("A {ghostly presence/long dead warrior/creepy sort of wraith-like thing} comes to haunt " + owner->getName() + " and the rest of the party!\n");
		auto hp = party->getActiveRoster()[rand() % party->getActiveRoster().size()];

		// Chance for priest-like characters to exorcise

		for (auto ep : party->getActiveRoster())
		{
			if (rand() % Hero::AttMax + 1 < ep->getAttrib(HeroAttrib::Divine))
			{
				upLog(ep->getName() + " {banishes/exorcises/chastises/glares at} the apparition and it promptly vanishes!\n");
				ep->modAttrib(HeroAttrib::Morale, 1);
				return;
			}
		}

		// 50% chance of good / ill effect

		if (rand() % 2 == 0)
		{
			upLog("The apparition {compliments/gives sage life advice to/fortells good fortune for} " + hp->getName() + " before vanishing!\n");
			hp->modAttrib(HeroAttrib::Morale, rand() % 3 + 1);
		}
		else
		{
			upLog("The apparition {insults/scares the hell out of/fortells grisly doom for} " + hp->getName() + " before vanishing!\n");
			hp->modAttrib(HeroAttrib::Morale, rand() % 3 - 3);
		}
	}
}

void TraitDiplomatic::doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// 50% chance of trying to improve party relations

	for (auto hp : party->getActiveRoster())
	{
		for (auto cp : party->getActiveRoster())
		{
			if (hp != cp)
			{
				if (hp->getReputation(cp->getName()) <= Hero::AttMax / 4)
				{
					if (rand() % 2 == 0)
					{
						// Attempt will be made for this relationship.

						upLog(owner->getName() + " chats with " + hp->getName() + " about " + hp->gp("p") + " {intense/terrible/overwhelming} {distaste/loathing/hatred} for\n" + cp->getName() + "...\n");

						if (hp->hasTrait("Vengeful"))
						{
							// Automatic failure
							upLog(hp->getName() + " tells " + owner->gp("2") + " to {shove off/get stuffed/butt out}.\n");
							return;
						}

						// 75% chance of success

						if (rand() % 4 == 0)
						{
							upLog(hp->getName() + " tells " + owner->gp("2") + " to {shove off/get stuffed/butt out}.\n");
							return;
						}
						else
						{
							upLog(hp->getName() + " {is persuaded/gives in/pretends to care but somehow winds up actually caring}.\n");
							upLog("Relations between " + hp->getName() + " and " + cp->getName() + " improve!");
							hp->modReputation(cp->getName(), rand() % 4 + 1);
							cp->modReputation(hp->getName(), rand() % 4 + 1);
							return;
						}

						return;
					}
				}
			}
		}
	}
}