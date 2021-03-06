#pragma once

#include "EncounterBase.h"
#include "Party.h"
#include "Incidents.h"
#include "ILogger.h"

#include <set>

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

		//int bonus{ 0 };

		//

		//if (party->getPartyAttrib(HeroAttrib::Level) + bonus > getLevel())
		//{
		//	upLog("The party {beats them senseless/gives them a stern talking-to/does terrible, terrible things to them}!\n");

		//	// Hotheaded check

		//	for (auto hp : party->getActiveRoster())
		//	{
		//		if (hp->hasTrait("Hotheaded"))
		//		{
		//			upLog(hp->getName() + " charges heedlessly into battle, ");
		//			int x = rand() % 10;
		//			if (x < hp->getAttrib(HeroAttrib::Physical))
		//			{
		//				upLog("cutting a glorious, bloody path through the enemy!\n");
		//				bonus += 1;
		//			}
		//			else
		//			{
		//				upLog("tripping over some {broken furniture/skulls/crockery} and receiving an injury...\n");
		//				bonus -= 1;
		//				r.push_back(std::make_unique<IncidentWounded>(hp));
		//			}
		//		}
		//	}

		//	unsigned int loot = getLevel() * rand() % 20 + 10;
		//	upLog("After {searching/desecrating/inspecting} the {corpses/bodies/bloody mess remaining} the party finds " + std::to_string(loot) + " loot!\n");

		//	// Klepto Check

		//	for (auto hp : party->getRoster())
		//	{
		//		if (hp->hasTrait("Kleptomaniac"))
		//		{
		//			int roll = rand() % 3;
		//			if (roll == 0)
		//			{
		//				upLog(hp->getName() + " {pilfers/steals/swipes/nabs/pockets} some loot on the sly!\n");
		//				loot -= loot / 5;

		//				// Caught?

		//				for (auto hp2 : party->getRoster())
		//				{
		//					if (hp2 != hp && hp2->hasTrait("Goody Two Shoes"))
		//					{
		//						upLog(hp2->getName() + " catches " + hp->getName() + " in the act and is pretty unhappy...\n");
		//						r.push_back(std::make_unique<IncidentTheft>(hp, hp2));
		//						break;
		//					}
		//				}

		//			}
		//		}
		//	}

		//	upLog("The party gains " + std::to_string(loot) + " loot.\n");
		//	party->addLoot(loot);


		//}
		//else
		//	upLog("\nThe party is vanquished...\n");

		std::set<Hero *> wounded;
		int bonus{ 0 };

		// Pre battle trait actions

		for (auto hp : party->getActiveRoster())
		{
			if (hp->hasTrait("Hotheaded") || hp->hasTrait("Bloodthirsty"))
			{
				// 50% chance of charging in...
				if (rand() % 2 == 0)
				{
					upLog(hp->getName() + " {charges heedlessly into the fray!/bellows and leaps into combat!/screams like a lunatic and rushes toward the enemy!}\n");
					// Injured vs. Bonus
					if (rand() % Hero::AttMax + 1 + hp->getAttrib(HeroAttrib::Luck) >= Hero::AttMax)
					{
						upLog(hp->gp("1c") + " {terrifies the enemy!/commits a glorious massacre!/litters the floor with corpses!/bathes in the enemy's blood!}\n");
						bonus += 10;
					}
					else
					{
						upLog(hp->gp("1c") + " {trips over some skulls/crashes into some furniture/gets caught in a tapestry and falls to the floor}...\n");
						bonus -= 10;
						wounded.insert(hp);
					}
				}
			}
			if (hp->hasTrait("Cowardly"))
			{
				upLog(hp->getName() + " is {terrified/visibly trembling/looking for an exit} ");
				// Roll vs. morale to stay in combat
				if (rand() % Hero::AttMax + 1 <= hp->getAttrib(HeroAttrib::Morale))
				{
					upLog("but {keeps it together/decides to fight anyway/manages to run toward the enemy rather than away}.\n");
				}
				else
				{
					upLog("and {hides behind some crockery/runs gallantly away/decides to sit this one out}.\n");
					bonus -= hp->getBestCoreAttribValue();
					// Add incident...
					r.push_back(std::make_unique<IncidentFlee>(hp));
				}
			}
			if (hp->hasTrait("Haunted"))
			{
				// Roll for ghostly bonus!
				if (rand() % Hero::AttMax + 1 <= hp->getAttrib(HeroAttrib::Luck))
				{
					upLog("{A ghostly presence/A grim spectre/A terrifying banshee} accompanies " + hp->getName() + " into battle, {terrifying/freaking out/unnerving} the enemy!\n");
					bonus += 8;
				}
			}
		}

		// Battle roll

		bool win = false;

		int battleStat{ (int)party->getBestAttribTotal() + (int)party->getMorale() };
		battleStat += bonus;
		battleStat += (int)party->getPartyAttrib(HeroAttrib::Gear);
		battleStat += ((int)party->getPartyAttrib(HeroAttrib::Level) - (int)getLevel()) * 6;
		battleStat /= 10;

		int battleRoll = rand() % 10 + 1;

		if (battleRoll <= battleStat)
		{
			win = true;
			upLog("The party {demolishes/crushes/pulverizes/humiliates/does horrible things to/permanently traumatizes} the enemy!\n");
		}
		else if (battleRoll - battleStat <= 3)
		{
			upLog("The party {flees in terror/flees ignominiously/barely escapes/beats feet/sneaks off as quietly as possible}...\n");
			for (auto hp : party->getActiveRoster())
			{
				int mLoss = rand() % 3 - 3;
				hp->modAttrib(HeroAttrib::Morale, mLoss);
				upLog(hp->getName() + " loses " + std::to_string(abs(mLoss)) + " morale.\n");
			}
		}
		else
		{
			upLog("Oh no! The party {is overwhelmed!/is beaten senseless!/gets its collective butt kicked!}\n");
			for (auto hp : party->getActiveRoster())
			{
				if (wounded.find(hp) == end(wounded))
				{
					if (rand() % 2 == 0)
					{
						// Add serious wounded incident...
						r.push_back(std::make_unique<IncidentWounded>(hp, true));
						upLog(hp->getName() + " {gets a nasty blow to the head!/is lightly mangled!/takes a particularly ugly beating!/is horrifically maimed!}\n");
					}
				}
			}
			upLog("The party is {demoralized/humiliated/saddened} by its {pitiful/ignominious/utter} defeat.\n");
			for (auto hp : party->getActiveRoster())
			{
				int mLoss = rand() % 3 - 5;
				hp->modAttrib(HeroAttrib::Morale, mLoss);
			}
		}

		// Add wounded incidents...

		for (auto hp : wounded)
		{
			r.push_back(std::make_unique<IncidentWounded>(hp));
		}

		// Exit early if party lost...

		if (!win)
			return r;

		// Loot!

		unsigned int loot = getLevel() * rand() % 20 + 10;
		upLog("After {searching/desecrating/inspecting} the {corpses/bodies/bloody mess remaining} the party finds " + std::to_string(loot) + " loot!\n");

		// Klepto Check

		for (auto hp : party->getRoster())
		{
			if (hp->hasTrait("Kleptomaniac"))
			{
				int roll = rand() % 2;
				if (roll == 0)
				{
					upLog(hp->getName() + " {pilfers/steals/swipes/nabs/pockets} some loot on the sly!\n");
					loot -= loot / 5;

					// Caught?

					for (auto hp2 : party->getRoster())
					{
						if (hp2 != hp && !hp2->hasTrait("Kleptomaniac"))
						{
							// Roll against thief's Rogue skill
							if (rand() % Hero::AttMax + 1 > hp->getAttrib(HeroAttrib::Rogue))
							{
								upLog(hp2->getName() + " catches " + hp->getName() + " in the act and is pretty unhappy...\n");
								r.push_back(std::make_unique<IncidentTheft>(hp, hp2));
								break;
							}
						}
					}
				}
			}
		}

		upLog("The party gains " + std::to_string(loot) + " loot.\n");
		party->addLoot(loot);

		return r;
	}
private:
	std::string m_namePlural;
};

class GenericTrapEncounter : public EncounterBase
{
public:
	GenericTrapEncounter(HeroAttrib attrib, unsigned int level, ILogger *logger) :
		EncounterBase{ attrib, level, logger }
	{}
	std::vector<std::unique_ptr<IncidentBase>> resolve(Party *party) override
	{

		std::vector<std::unique_ptr<IncidentBase>> r;

		// Determine trap type for flavor...

		int type = rand() % 2;

		// Chance to detect trap...

		auto rh = party->getHeroWithBestAttrib(HeroAttrib::Rogue);

		if (rand() % Hero::AttMax + 1 < rh->getAttrib(HeroAttrib::Rogue))
		{
			// Trap detected

			upLog("While {strolling down/walking along/plodding through} a {filthy cooridoor/narrow passage/dark tunnel}, " +
				rh->getName() + " detects a {dastardly/dangerous/devious} trap!\n");

			// Vengeance?

			auto p = party->getActiveHeroWithTrait("Vengeful");
			if (p != nullptr)
			{
				for (auto vp : party->getActiveRoster())
				{
					if (vp != p && p->getReputation(vp->getName()) == 0)
					{
						// Yes!
						upLog(p->getName() + " decides to enact {horrible/gruesome/terrifying} vengeance upon "
							+ vp->getName() + " by pushing " + vp->gp("2") + " into the trap's {pointy spikes/sinister blades/deadly protrusions}!\n");
						p->setReputation(vp->getName(), Hero::AttMax / 2);

						if (rand() % 2 == 0)
						{
							upLog(vp->getName() + " is {lightly wounded/somewhat mangled/mildly bruised} by the trap.\n");
							r.push_back(std::make_unique<IncidentWounded>(vp));
							return r;
						}
						else
						{
							upLog(vp->getName() + " is {badly hurt/seriously maimed/horribly wounded} by the trap.\n");
							r.push_back(std::make_unique<IncidentWounded>(vp, true));
							return r;
						}
					}
				}
			}

			upLog("The party evades the trap with ease and continues the journey.\n");
			return r;
		}
		else
		{
			// Detection failed

			upLog("While {strolling down/walking along/plodding through} a {filthy cooridoor/narrow passage/dark tunnel}, the party triggers a {dastardly/dangerous/devious} trap!\n");

			// Types?

			if (type == 0)
			{
				// Pit trap
				// Who falls in?

				auto p = party->getActiveHeroWithTrait("Bossy");
				if (p != nullptr)
				{
					upLog(p->getName() + ", who is leading the way as usual, {bumbles/plunges/somersaults} directly into a hidden pit!\n");
				}
				else
				{
					p = party->getActiveRoster()[rand() % party->getActiveRoster().size()];
					upLog(p->getName() + " {bumbles/plunges/somersaults} directly into a hidden pit!\n");

				}
				if (rand() % 2 == 0)
				{
					upLog(p->getName() + " is {lightly wounded/somewhat mangled/mildly bruised} by the fall.\n");
					r.push_back(std::make_unique<IncidentWounded>(p));
				}
				else
				{
					upLog(p->getName() + " is {badly hurt/seriously maimed/horribly wounded} by the trap.\n");
					r.push_back(std::make_unique<IncidentWounded>(p, true));
				}
				upLog("The party manages to get " + p->getName() + " out of the pit and continues on its way.\n");
				return r;
			}
			else if (type == 1)
			{
				// Poison Dart
				// Who gets hit?

				auto p = party->getActiveRoster()[rand() % party->getActiveRoster().size()];
				upLog(p->getName() + " is hit with a poisoned dart!\n");

				if (rand() % 2 == 0)
				{
					upLog("Fortunately, {the injury is minor/it's just a scratch}.\n");
					r.push_back(std::make_unique<IncidentWounded>(p));
				}
				else
				{
					upLog("Alas, the dart was poisoned! " + p->getName() + " {is looking a bit green/doesn't feel very well/is in for a rough evening}.\n");
					r.push_back(std::make_unique<IncidentPoison>(p));
				}
				upLog("The party continues on its way.\n");
				return r;
			}
			else if (type == 2)
			{

			}
		}


	}
};
