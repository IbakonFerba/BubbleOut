#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "stdafx.h"
#include "ObjectManager.h"

class GameObject
{
public:
	GameObject() : m_ptr_objManager(nullptr)
	{
		pushInheritanceChain<GameObject>();
	}
	virtual ~GameObject() {}

	void setObjectManager(ObjectManager* ptrObjManager);
	bool isInheritedFrom(const std::size_t& rTypeHash);

protected:
	ObjectManager* m_ptr_objManager;
	std::vector<std::size_t> m_inheritanceChain;

	template <typename T>
	void pushInheritanceChain()
	{
		const std::type_info& typeInfo = typeid(T);
		m_inheritanceChain.push_back(typeInfo.hash_code());
	}
};

#endif