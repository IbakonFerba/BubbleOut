#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stdafx.h"
#include "EngineObject.h"
#include "FloatVector2.h"

class Transform : public EngineObject
{
public:
	Transform() : EngineObject(), position(0,0), scale(1, 1), rotation(0)
	{
		pushInheritanceChain<Transform>();
	}
	~Transform() {}

	FloatVector2 position;
	FloatVector2 scale;
	float rotation;
};

#endif

