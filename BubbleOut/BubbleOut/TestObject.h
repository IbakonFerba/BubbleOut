#pragma once

#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "stdafx.h"
#include "GameObject.h"
#include "CircleRenderer.h"

class TestObject : public GameObject
{
public:
	TestObject() : GameObject()
	{
		pushInheritanceChain<TestObject>();
	}
	~TestObject();

	void init(ObjectManager* ptrObjectManager);
private:
	Transform* m_ptr_trans;
	CircleRenderer* m_ptr_rend;
};

#endif