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
		std::string attName = att->getName();
		std::string defName = def->getName();

		if (diff > 4 * Hero::AttMax * 2 / 5)
		{
			// Uh oh...
			upLog(defName + " has been {bludgeoned to death/mortally injured/more or less killed} by " + attName + "...\n");
			def->setActive(false);
			incident.push_back(std::make_unique<IncidentPartyInfighting>(att, def, true));
			// Morale effects wait until Infighting is resolved.
		}
		else if (diff > 2 * Hero::AttMax * 2 / 3)
		{
			// A vicious wound
			upLog(attName + " {seriously/gravely/horribly} {wounds/maims/wallops/injures} " + defName + "!\n");
			incident.push_back(std::make_unique<IncidentWounded>(def, true));
			incident.push_back(std::make_unique<IncidentPartyInfighting>(att, def, true));
			// Morale effects wait until Infighting is resolved.
		}
		else
		{
			// A light wound
			upLog(attName + " gives " + defName + " a {minor thrashing/thump on the head/boot to the groin!\nThe party laughs it off, but the combatants are {not feeling chummy/not speaking to one another/not on great terms at the moment}.\n");
			m_observer->modReputation(tName, rand() % 3 - 5);
			m_thief->modReputation(oName, rand() % 3 - 5);
			incident.push_back(std::make_unique<IncidentWounded>(def, false));
		}


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

void IncidentFlee::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	
}

void IncidentPartyInfighting::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{

}