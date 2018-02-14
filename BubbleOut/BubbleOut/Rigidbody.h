#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "stdafx.h"
#include "EngineObject.h"
#include "Subject.h"
#include "Collider.h"
#include "Entity.h"
#include "CircleCollider.h"
#include "RectCollider.h"

class Rigidbody : public EngineObject, public Subject
{
public:
	Rigidbody() : EngineObject(), m_velocity(0.0, 0.0), m_acceleration(0.0, 0.0), m_mass(1), m_drag(0), kinematic(false)
	{
		pushInheritanceChain<Rigidbody>();
	}
	~Rigidbody() {}

	bool kinematic;
	bool enabled = true;

	void init(const Entity* ptrEntity, const CircleCollider* ptrCollider, Transform* ptrTransform, const float drag, const float mass);
	void init(const Entity* ptrEntity, const RectCollider* ptrCollider, Transform* ptrTransform, const float drag, const float mass);

	void collisionWith(const Rigidbody* other);
	void collisionWith(const Tag& tag);
	void addForce(const FloatVector2& force);

	void applyPhysics();

	const Entity* getEntity() const;
	const CircleCollider* getCircleCollider() const;
	const RectCollider* getRectCollider() const;
	FloatVector2 getVelocity() const;

	void setVelocity(const FloatVector2& newVel);
protected:
	void notifyObservers() const override;

private:
	const Entity* m_ptr_entity;
	const CircleCollider* m_ptr_circleCollider;
	const RectCollider* m_ptr_rectCollider;
	Transform* m_ptr_transform;
	FloatVector2 m_velocity;
	FloatVector2 m_acceleration;
	float m_drag;
	float m_mass;

	Message m_observerMessage;
};

#endif