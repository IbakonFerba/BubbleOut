#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"
struct Message
{
	int intVal;
	float floatVal;
	bool boolVal;
	std::string stringVal;
};

class Observer
{
public:
	virtual void update(const Message& message) = 0;
};

#endif