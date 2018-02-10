#pragma once

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "stdafx.h"
#include "ObjectManager.h"

class GameObject
{
public:
	GameObject() : m_objManager(nullptr)
	{
		pushInheritanceChain<GameObject>();
	}
	virtual ~GameObject() {}

	void setObjectManager(ObjectManager* objManager);
	bool isInheritedFrom(const std::size_t& typeHash);

protected:
	ObjectManager* m_objManager;
	std::vector<std::size_t> m_inheritanceChain;

	template <typename T>
	void pushInheritanceChain()
	{
		const std::type_info& typeInfo = typeid(T);
		m_inheritanceChain.push_back(typeInfo.hash_code());
	}
};

class A : public GameObject
{
public:
	A() : GameObject()
	{
		pushInheritanceChain<A>();
	}
	virtual ~A() {}

	int i = 10;
};

class B : public A
{
public:
	B() : A()
	{
		pushInheritanceChain<B>();
		i = 20;
	}
	virtual ~B() {}

	float f = 3.12;
};

class C : public GameObject
{
public:
	C() : GameObject()
	{
		pushInheritanceChain<C>();
	}
	virtual ~C() {}

	std::string s = "help";
};

#endif