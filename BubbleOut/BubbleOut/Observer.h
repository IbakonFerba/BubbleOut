#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"
#include "Transform.h"

struct Message
{
	int intVal;
	float floatVal;
	bool boolVal;
	std::string stringVal;
	Tag tag;
	Transform* transform;
};

class Observer
{
public:
	virtual void update(const Message& message) = 0;
};

#endif