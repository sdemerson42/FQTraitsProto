#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

void IncidentTheft::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	// Vengeful

	if (m_observer->hasTrait("Vengeful"))
	{
		m_observer->setReputation(m_thief->getName(), 0);
		upLog(m_observer->getName() + " now hates " + m_thief->getName() + " and {promises revenge/swears unholy vengeance/plans retribution}...\n");
		return;
	}

	int anger = 0;

	// Reputation

	if (m_observer->getReputation(m_thief->getName()) < Hero::AttMax / 3)
	{
		anger += 5;
	}

	if (m_observer->getReputation(m_thief->getName()) > Hero::AttMax * 2 / 3)
	{
		anger -= 5;
	}

	// Alignment

	if (m_observer->getAttrib(HeroAttrib::Alignment) > Hero::AttMax * 2 / 3)
	{
		anger += 3;
	}

	if (m_observer->getAttrib(HeroAttrib::Alignment) > Hero::AttMax * 4 / 5)
	{
		anger += 3;
	}

	// Traits

	if (m_observer->hasTrait("Hotheaded")) anger += 6;
	if (m_observer->hasTrait("Goody Two Shoes")) anger += 4;
	if (m_observer->hasTrait("Bloodthirsty")) anger += 4;
	if (m_observer->hasTrait("Cowardly")) anger -= 4;
	if (m_observer->hasTrait("Bossy")) anger += 3;


	// Evaluate

	std::string oName{ m_observer->getName() };
	std::string tName{ m_thief->getName() };

	if (anger < 6)
	{
		// Ill will...
		upLog(oName + " is {upset/angry/piqued/annoyed} about a theft and has a lowered opinion of " + tName + ".\n");
		m_observer->modReputation(tName, rand() % 3 - 4);
	}
	else if (anger < 11)
	{
		// Drama!
		upLog(oName + " confronts " + tName + " about a theft and {tempers flare/hurtful things are said/drama ensues}.\n");

		// Chance for diplomat to defuse...

		for (auto hp : party->getActiveRoster())
		{
			if (hp->hasTrait("Diplomatic") && hp != m_observer && hp != m_thief)
			{
				upLog(hp->getName() + " attempts to {intervene/calm everyone down/defuse the situation} ");
				if (rand() % 2 == 0)
				{
					upLog("and is successful.\n");
					return;
				}
				else
				{
					upLog(", but is {unsuccessful/pushed aside/invited to butt out}...\n");
				}
			}
		}

		m_observer->modReputation(tName, rand() % 3 - 5);
		m_thief->modReputation(oName, rand() % 3 - 5);
		
		upLog("Nobody feels particularly good about this and morale decreases slightly all around.\n");
		for (auto hp : party->getActiveRoster())
		{
			hp->modAttrib(HeroAttrib::Morale, -1);
		}
	}
	else
	{
		// Violence!
		upLog(oName + " is {furious/enraged/apoplectic} about a theft and attacks " + tName + "!\n");

		// Chance for diplomat to defuse...

		for (auto hp : party->getActiveRoster())
		{
			if (hp->hasTrait("Diplomatic") && hp != m_observer && hp != m_thief)
			{
				upLog(hp->getName() + " attempts to {intervene/calm everyone down/defuse the situation} ");
				if (rand() % 4 == 0)
				{
					upLog("and is successful.\n");
					return;
				}
				else
				{
					upLog(", but is {unsuccessful/pushed aside/invited to butt out}...\n");
				}
			}
		}

		int oScore = rand() % Hero::AttMax + 1 + m_observer->getBestCoreAttribValue();
		int tScore = rand() % Hero::AttMax + 1 + m_thief->getBestCoreAttribValue();
		int diff = abs(oScore - tScore);
		Hero *att = m_observer;
		Hero *def = m_thief;
		if (tScore > oScore)
		{
			att = m_thief;
			def = m_observer;
		}

		incident.push_back(std::make_unique<IncidentPartyInfighting>(att, def));
	}
}

void IncidentWounded::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &)
{
	upLog(m_wounded->getName() + " {has a bit of a cry about/whines about/keeps poking at} " + (m_wounded->getGender() == 'M' ? "his " : "her ")
		+ "injuries and loses morale...\n");
	m_wounded->modAttrib(HeroAttrib::Morale, rand() % 3 - 3);
	auto &hv = party->getActiveRoster();
	for (auto &hp : hv)
	{
		if (hp != m_wounded && (hp->hasTrait("Goody Two Shoes") || hp->getReputation(m_wounded->getName()) > Hero::AttMax * 2/3))
		{
			upLog(hp->getName() + " {sings a bawdy song/performs a puppet show/does magic tricks} for " + m_wounded->gp("2") + "...\n");
			
			// 50% chance of improvement...

			if (rand() % 2 == 0)
			{
				upLog(m_wounded->getName() + " {feels better/perks right up/is miraculously healed}!\n");
				m_wounded->modAttrib(HeroAttrib::Morale, rand() % 4 + 1);
				m_wounded->modReputation(hp->getName(), 2);
			}
			else
			{
				upLog(m_wounded->getName() + " {isn't interested/doesn't respond/is in too much pain to notice}.\n");
			}
			break;
		}
	}
	
}

void IncidentFlee::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	for (auto hp : party->getActiveRoster())
	{
		if (hp != m_hero && !hp->hasTrait("Cowardly"))
		{
			if (hp->hasTrait("Hotheaded"))
			{
				upLog(hp->getName() + " is {disgusted by/appalled at/nauseated by} " + m_hero->getName() + "'s cowardice and thinks less of " + m_hero->gp("2") + ".\n");
				hp->modReputation(m_hero->getName(), -2);
			}
			if (hp->hasTrait("Bossy"))
			{
				upLog(hp->getName() + " is {angry about/furious about/unhappy with} " + m_hero->getName() + "'s failure to follow orders and thinks less of " + m_hero->gp("2") + ".\n");
				hp->modReputation(m_hero->getName(), -2);
				
				// Possible confrontation...

				if (hp->getReputation(m_hero->getName()) < Hero::AttMax * 4 / 5)
				{
					// Random disciplinary action ensues...

					int roll = rand() % 2;
					// Dressing down...
					upLog(hp->getName() + " {starts screaming at/begins to bawl out} " + m_hero->getName() + "!\n");
					if (roll == 0)
					{
						// ...and violence
						upLog("The situation escalates into violence!\n");
						incident.push_back(std::make_unique<IncidentPartyInfighting>(hp, m_hero));
					}
				}
			}
		}
	}
}

void IncidentPartyInfighting::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident)
{
	auto att = m_att;
	auto def = m_def;
	int oScore = rand() % Hero::AttMax + 1 + m_att->getBestCoreAttribValue();
	int tScore = rand() % Hero::AttMax + 1 + m_def->getBestCoreAttribValue();
	int diff = abs(oScore - tScore);

	std::string attName = att->getName();
	std::string defName = def->getName();

	if (diff > 4 * Hero::AttMax * 2 / 5)
	{
		// Uh oh...
		upLog(defName + " has been {bludgeoned to death/mortally injured/more or less killed} by " + attName + "...\n");
		def->setActive(false);
	}
	else if (diff > 2 * Hero::AttMax * 2 / 3)
	{
		// A vicious wound
		upLog(attName + " {seriously/gravely/horribly} {wounds/maims/wallops/injures} " + defName + "!\n");
		def->modReputation(attName, rand() % 3 - 5);
		incident.push_back(std::make_unique<IncidentWounded>(def, true));
	}
	else
	{
		// A light wound
		upLog(attName + " gives " + defName + " a {minor thrashing/thump on the head/boot to the groin}!\nThe party {laughs it off/eventually calms down}, but the combatants are {not feeling chummy/not speaking to one another/not on great terms at the moment}.\n");
		def->modReputation(attName, rand() % 3 - 3);
		incident.push_back(std::make_unique<IncidentWounded>(def, false));
	}
}