#include "stdafx.h"
#include "Subject.h"

void Subject::addObserver(Observer* ptrObserver)
{
	m_observers.push_back(ptrObserver);
}

void Subject::removeObserver(Observer* ptrObserver)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), ptrObserver), m_observers.end());
}


void Subject::notifyObservers() const
{
	for (unsigned i = 0; i < m_observers.size(); ++i)
	{
		m_observers.at(i)->update(m_observerMessage);
	}
}

