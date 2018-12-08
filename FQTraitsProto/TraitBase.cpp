#include "TraitBase.h"
#include "ConsoleLogger.h"
#include "DualLogger.h"

ILogger *TraitBase::m_logger;

void TraitBase::setLogger(ILogger *il)
{
	m_logger = il;
}

void TraitBase::upLog(const std::string &s)
{
	m_logger->log(s);
}