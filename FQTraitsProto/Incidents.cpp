#include "Incidents.h"
#include "Party.h"
#include "HeroBase.h"

std::string IncidentTheft::resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &)
{
	m_thief->setActive(false);
	return m_observer->getName() + " decides to enact martial law and {strangles/bludgeons/whacks} " + m_thief->getName()
		+ " in " + (m_thief->getGender() == 'M' ? "his " : "her ") + "sleep.\n";

}
