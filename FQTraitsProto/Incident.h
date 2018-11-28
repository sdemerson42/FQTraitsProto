#pragma once

#include <vector>
#include <memory>
#include <string>

class Party;
class ILogger;

class IncidentBase
{
public:
	virtual ~IncidentBase()
	{}
	virtual void resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) = 0;
	static void setLogger(ILogger *);
	void upLog(const std::string &);
private:
	static ILogger *m_logger;
};