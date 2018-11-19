#include "ILogger.h"
#include <vector>

std::string ILogger::parse(const std::string &s)
{
	std::string t;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == '{')
		{
			std::string temp;
			std::vector<std::string> randVec;
			while (true)
			{
				++i;
				if (s[i] == '}' || s[i] == '/')
				{
					randVec.push_back(temp);
					if (s[i] == '}')
						break;
					temp = "";
				}
				else
				{
					temp += s[i];
				}
			}
			int x = rand() % randVec.size();
			t += randVec[x];
		}
		else
		{
			t += s[i];
		}
	}
	return t;
}