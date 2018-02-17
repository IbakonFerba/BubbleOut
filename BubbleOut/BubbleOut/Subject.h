#pragma once

#ifndef SUBJECT_H
#define SUBJECT_H

#include "stdafx.h"
#include "Observer.h"

class Subject
{
public:
	virtual ~Subject() {}
	void addObserver(Observer* o);
	void removeObserver(Observer* o);
protected:
	std::vector<Observer*> m_observers;
	Message m_observerMessage;

	virtual void notifyObservers() const;
};

#endif