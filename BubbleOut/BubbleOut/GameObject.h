#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "stdafx.h"
#include "ObjectManager.h"

/*
 * Base class for all objects that can
 * be used in the engine
 */
class GameObject
{
public:
	GameObject() : m_ptr_objManager(nullptr)
	{
		pushInheritanceChain<GameObject>();
	}
	virtual ~GameObject() {}

	//give a reference to the object manager into the object
	void setObjectManager(ObjectManager* ptrObjManager);
	//is the object derived from the given type?
	bool isDerivedFrom(const std::size_t& rTypeHash);

protected:
	//object manager for creating components
	ObjectManager* m_ptr_objManager;
	//stores inheritance information
	std::vector<std::size_t> m_inheritanceChain;

	//use this function at construction of the object to save inheritance
	template <typename T>
	void pushInheritanceChain()
	{
		const std::type_info& typeInfo = typeid(T);
		m_inheritanceChain.push_back(typeInfo.hash_code());
	}
};

#endif