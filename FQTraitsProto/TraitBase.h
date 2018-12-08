#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class EncounterBase;
class Party;
class IncidentBase;
class Hero;
class ILogger;

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
	virtual void doIncidentPhase(Hero *owner, Party *party, std::vector<std::unique_ptr<IncidentBase>> &incident) = 0;
	virtual void initialize(Hero *)
	{
	}
	static void setLogger(ILogger *il);
protected:
	void upLog(const std::string &);
private:
	std::string m_name;
	std::vector<TraitBase *> m_incompatible;
	static ILogger *m_logger;
};
