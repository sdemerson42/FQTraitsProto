#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

std::string IncidentTheft::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	
	return "";
}

std::string IncidentWounded::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &)
{
	std::string s = m_wounded->getName() + " {has a bit of a cry about/whines about/keeps poking at} " + (m_wounded->getGender() == 'M' ? "his " : "her ")
		+ "injuries and loses morale...\n";
	m_wounded->modAttrib(HeroAttrib::Morale, rand() % 3 - 3);
	auto &hv = party->getActiveRoster();
	for (auto &hp : hv)
	{
		if (hp != m_wounded && (hp->hasTrait("Goody Two Shoes") || hp->getReputation(m_wounded->getName()) > Hero::AttMax * 2/3))
		{
			std::string ss = hp->getName() + " {sings a bawdy song/performs a puppet show} for " +
				(m_wounded->getGender() == 'M' ? "him" : "her") + ", which seems to help!\n";
			s += ss;
			m_wounded->modAttrib(HeroAttrib::Morale, rand() % 4 + 1);
			m_wounded->modReputation(hp->getName(), 2);
			break;
		}
	}
	return s;
}

std::string IncidentFlee::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	return std::string{};
}