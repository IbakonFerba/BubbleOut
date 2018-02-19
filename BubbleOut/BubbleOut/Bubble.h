#pragma once

#ifndef BUBBLE_H
#define BUBBLE_H

#include "stdafx.h"
#include "Entity.h"
#include "Observer.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"

/*
 * A Bubble that has physics
 * and shrinks when it is hit by the player.
 * If it hits another bubble it grows if it is bigger than
 * the other bubble and shrinks if it is smaller
 */
class Bubble : public Entity, public Observer, public Subject
{
public:
	Bubble() : Entity(), m_ptr_trans(nullptr), m_ptr_rend(nullptr), m_ptr_col(nullptr), m_ptr_rigidbody(nullptr), m_startDrag(0), m_startMass(1) {}
	~Bubble() {}

	const float MIN_SCALE = 0.3f;
	const float MAX_SCALE = 1.2;
	const float SCALE_STEP = 0.1f;
	const float DRAG_STEP = 0.5;
	const float MASS_STEP = 0.1;

	bool enabled = true;

	//initialize the bubble
	void init(ObjectManager* ptrObjectManager, const float& rPosX, const float& rPosY);

	//set the bubble back to its start position and start scale and resets all values
	void reset();
	//disables the bubble
	void disable();

	//update observer
	void update(const Message& rMessage) override;

	FloatVector2 getScale() const;
	FloatVector2 getPosition() const;
private:
	Transform* m_ptr_trans;
	SpriteRenderer* m_ptr_rend;
	CircleCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;

	FloatVector2 m_startPos;
	float m_startDrag;
	float m_startMass;
};

#endif