#include "Incident.h"
#include "ConsoleLogger.h"
#include "DualLogger.h"

ILogger *IncidentBase::m_logger;

void IncidentBase::setLogger(ILogger *lp)
{
	m_logger = lp;
}

void IncidentBase::upLog(const std::string &s)
{
	m_logger->log(s);
}