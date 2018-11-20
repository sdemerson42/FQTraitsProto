#pragma once

#include <vector>
#include <string>
#include <algorithm>

class EncounterBase;
class Party;
class IncidentBase;

class TraitBase
{
public:
	TraitBase(const std::string &name) :
		m_name{ name }
	{}
	virtual ~TraitBase()
	{}
	const std::string &name() const
	{
		return m_name;
	}
	void addIncompatible(TraitBase *tp)
	{
		m_incompatible.push_back(tp);
	}
	bool checkCompatible(TraitBase *tp)
	{
		auto p = std::find(begin(m_incompatible), end(m_incompatible), tp);
		if (p == end(m_incompatible))
			return true;
		return false;
	}
	virtual void doIncidentPhase(Party *, std::vector<std::unique_ptr<IncidentBase>> &) = 0;
private:
	std::string m_name;
	std::vector<TraitBase *> m_incompatible;
};
