#pragma once

#ifndef SUBJECT_H
#define SUBJECT_H

#include "stdafx.h"
#include "Observer.h"

class Subject
{
public:
	void addObserver(Observer* o);
	void removeObserver(Observer* o);
protected:
	std::vector<Observer*> m_observers;

	virtual void notifyObservers() const = 0;
};

#endif