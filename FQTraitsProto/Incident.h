#pragma once

#include <vector>
#include <memory>
#include <string>

class Party;

class IncidentBase
{
public:
	virtual ~IncidentBase()
	{}
	virtual std::string resolve(Party *, std::vector<std::unique_ptr<IncidentBase>> &) = 0;
};