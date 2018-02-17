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
	Barrier() :Entity(), m_ptr_trans(nullptr), m_ptr_col(nullptr), m_ptr_rigidbody(nullptr) {}
	~Barrier() {}

	void init(ObjectManager* ptrObjectManager, const FloatVector2& rPosition, const float& rWidth, const float& rHeight, const Tag& rTag);
private:
	Transform* m_ptr_trans;
	RectCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;
};

#endif