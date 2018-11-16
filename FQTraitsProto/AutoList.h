#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class AutoList
{
public:
	AutoList()
	{
		m_ref.push_back(static_cast<T *>(this));
	}
	virtual ~AutoList()
	{
		auto targ = static_cast<T *>(this);
		auto p = std::find(begin(m_ref), end(m_ref), targ);
		if (p != end(m_ref))
			m_ref.erase(p);
	}
	static int size()
	{
		return m_ref.size();
	}
	static T *get(int index)
	{
		return m_ref[index];
	}
private:
	static std::vector<T *> m_ref;
};

template<typename T>
std::vector<T *> AutoList<T>::m_ref;
