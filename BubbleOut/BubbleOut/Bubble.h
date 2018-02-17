#pragma once

#ifndef BUBBLE_H
#define BUBBLE_H

#include "stdafx.h"
#include "Entity.h"
#include "Observer.h"
#include "Transform.h"
#include "ShapeRenderer.h"
#include "CircleCollider.h"
#include "Rigidbody.h"

class Bubble : public Entity, public Observer, public Subject
{
public:
	Bubble() : Entity()
	{
		pushInheritanceChain<Bubble>();
	}
	~Bubble() {}

	const float MIN_SCALE = 0.5f;
	const float MAX_SCALE = 1.5;
	const float SCALE_STEP = 0.1f;
	const float DRAG_STEP = 0.5;
	const float MASS_STEP = 0.1;
	bool enabled = true;

	void init(ObjectManager* ptrObjectManager, const float posX, const float posY);
	void reset();

	void disable();

	void notifyObservers() const override;
	void update(const Message& message) override;

	FloatVector2 getScale() const;
	FloatVector2 getPosition() const;
private:
	Transform* m_ptr_trans;
	ShapeRenderer* m_ptr_rend;
	CircleCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;

	FloatVector2 m_startPos;
	float m_startDrag;
	float m_startMass;

	Message m_observerMessage;
};

#endif