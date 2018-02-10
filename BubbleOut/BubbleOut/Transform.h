#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "stdafx.h"
#include "GameObject.h"
#include "FloatVector2.h"

class Transform : public GameObject
{
public:
	Transform() : GameObject()
	{
		pushInheritanceChain<Transform>();
	}
	~Transform() {}

	FloatVector2 Position;
};

#endif

