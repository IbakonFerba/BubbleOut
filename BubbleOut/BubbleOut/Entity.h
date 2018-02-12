#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "EngineObject.h"

class Entity : public EngineObject
{
public:
	Entity() : EngineObject()
	{
		tag = Tag::NONE;
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