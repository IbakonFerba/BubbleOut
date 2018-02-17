#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "stdafx.h"
#include "ObjectManager.h"

/*
 * Base for all collections of Components
 * (Basically like the Game Object in Unity)
 */
class Entity
{
public:
	Entity() : tag(Tag::NONE) {}
	virtual ~Entity() {}

	Tag tag;

	//initialize the entity
	virtual void init(ObjectManager* ptrObjectManager) {}
};

#endif