#pragma once

#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H

#include "stdafx.h"
#include "EngineObject.h"
#include "ShapeRenderer.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Rigidbody.h"
#include "CircleCollider.h"

class TestObject : public Entity, public Observer
{
public:
	TestObject() : Entity()
	{
		pushInheritanceChain<TestObject>();
	}
	~TestObject();

	Rigidbody* m_ptr_rigidbody;

	void init(ObjectManager* ptrObjectManager, const FloatVector2& pos, const FloatVector2& initialForce, float mass, bool cirlceCollider);
	void update(const Message& message);
private:
	Transform* m_ptr_trans;
	ShapeRenderer* m_ptr_rend;
	RectCollider* m_ptr_collider;
	CircleCollider* m_ptr_circleCollider;
};

#endif