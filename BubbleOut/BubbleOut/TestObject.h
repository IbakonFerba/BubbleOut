#pragma once

#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "stdafx.h"
#include "GameObject.h"
#include "ShapeRenderer.h"
#include "Entity.h"
#include "SpriteRenderer.h"

class TestObject : public Entity
{
public:
	TestObject() : Entity()
	{
		pushInheritanceChain<TestObject>();
	}
	~TestObject();

	void init(ObjectManager* ptrObjectManager) override;
private:
	Transform* m_ptr_trans;
	SpriteRenderer* m_ptr_rend;
};

#endif