#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "stdafx.h"

class GameObject
{
public:
	GameObject() {};
	~GameObject() {};

	virtual void init() = 0;
};

#endif
