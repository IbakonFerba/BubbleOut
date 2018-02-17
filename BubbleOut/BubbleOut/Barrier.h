#pragma once

#ifndef BARRIER_H
#define BARRIER_H

#include "stdafx.h"
#include "Entity.h"
#include "Transform.h"
#include "RectCollider.h"
#include "Rigidbody.h"

class Barrier : public Entity
{
public:
	Barrier() :Entity() {}
	~Barrier() {}

	void init(ObjectManager* ptrObjectManager, const FloatVector2& position, const float& width, const float& height, const Tag& _tag);
private:
	Transform* m_ptr_trans;
	RectCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;
};

#endif