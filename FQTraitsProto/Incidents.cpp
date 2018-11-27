#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

std::string IncidentTheft::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	m_thief->setActive(false);
	return m_observer->getName() + " decides to enact martial law and {strangles/bludgeons/whacks} " + m_thief->getName()
		+ " in " + (m_thief->getGender() == 'M' ? "his " : "her ") + "sleep.\n";

}

std::string IncidentWounded::resolve(Party *party, std::vector<std::unique_ptr<IncidentBase>> &)
{
	std::string s = m_wounded->getName() + " has a bit of a cry about " + (m_wounded->getGender() == 'M' ? "his " : "her ")
		+ "injuries and loses morale...\n";
	m_wounded->modAttrib(HeroAttrib::Morale, -1);
	auto &hv = party->getRoster();
	for (auto &hp : hv)
	{
		if (hp->hasTrait("Goody Two Shoes"))
		{
			std::string ss = hp->getName() + " {sings a bawdy song/performs a puppet show} for " +
				(m_wounded->getGender() == 'M' ? "him" : "her") + ", which seems to help!\n";
			s += ss;
			m_wounded->modAttrib(HeroAttrib::Morale, 1);
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