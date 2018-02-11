#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stdafx.h"
#include "GameObject.h"
#include "FloatVector2.h"

class Transform : public GameObject
{
public:
	Transform() : GameObject(), position(0,0), scale(1, 1), rotation(0)
	{
		pushInheritanceChain<Transform>();
	}
	~Transform() {}

	FloatVector2 position;
	FloatVector2 scale;
	float rotation;
};

#endif

