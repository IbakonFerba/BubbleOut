#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "GameObject.h"

class Entity : public GameObject
{
public:
	Entity() : GameObject()
	{
		pushInheritanceChain<Entity>();
	}
	virtual ~Entity() {}

	Tag tag;

	virtual void init(ObjectManager* ptrObjectManager)
	{
		setObjectManager(ptrObjectManager);
	}
};

#endif