#pragma once

#include "Globals.h"
#include "ILogger.h"

class Party;
class IncidentBase;

#include <vector>
#include <memory>
#include <string>

class EncounterBase
{
public:
	virtual ~EncounterBase()
	{}
	EncounterBase(HeroAttrib attrib, unsigned int level, ILogger *logger) :
		m_attribType{ attrib }, m_level{ level }, m_logger{ logger }
	{}
	HeroAttrib getAttrib() const
	{
		return m_attribType;
	}
	unsigned int getLevel() const
	{
		return m_level;
	}
	void upLog(const std::string &s)
	{
		m_logger->log(s);
	}
	virtual std::vector<std::unique_ptr<IncidentBase>> resolve(Party *party) = 0;
private:
	HeroAttrib m_attribType;
	unsigned int m_level;
	ILogger *m_logger;
};
