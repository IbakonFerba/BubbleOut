#include "stdafx.h"
#include "Subject.h"

void Subject::addObserver(Observer* o)
{
	m_observers.push_back(o);
}

void Subject::removeObserver(Observer* o)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), o), m_observers.end());
}

