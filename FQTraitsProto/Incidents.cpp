#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

void IncidentTheft::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	
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