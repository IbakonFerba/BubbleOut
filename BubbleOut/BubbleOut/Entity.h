#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "ObjectManager.h"

class Entity
{
public:
	Entity()
	{
		tag = Tag::NONE;
	}
	virtual ~Entity() {}

	Tag tag;

	virtual void init(ObjectManager* ptrObjectManager) {}
};

#endif