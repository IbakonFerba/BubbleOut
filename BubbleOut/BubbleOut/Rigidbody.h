#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "stdafx.h"
#include "Subject.h"
#include "Collider.h"
#include "Entity.h"
#include "CircleCollider.h"
#include "RectCollider.h"

class Rigidbody : public Subject
{
public:
	Rigidbody() : m_velocity(0.0, 0.0), m_acceleration(0.0, 0.0), mass(1), drag(0), kinematic(false) {}
	~Rigidbody() {}

	float drag;
	float mass;
	bool kinematic;
	bool enabled = true;
	std::vector<Rigidbody*> collidingRigidbodys;

	void init(const Entity* ptrEntity, CircleCollider* ptrCollider, Transform* ptrTransform, const float _drag, const float _mass);
	void init(const Entity* ptrEntity, RectCollider* ptrCollider, Transform* ptrTransform, const float _drag, const float _mass);

	void collisionWith(const Rigidbody* other);
	void collisionWith(const Tag& tag);
	void collisionExitWith(const Rigidbody* other);
	void addForce(const FloatVector2& force);

	void applyPhysics();

	const Entity* getEntity() const;
	CircleCollider* getCircleCollider() const;
	RectCollider* getRectCollider() const;
	FloatVector2 getVelocity() const;

	void setVelocity(const FloatVector2& newVel);

private:
	const Entity* m_ptr_entity;
	CircleCollider* m_ptr_circleCollider;
	RectCollider* m_ptr_rectCollider;
	Transform* m_ptr_transform;
	FloatVector2 m_velocity;
	FloatVector2 m_acceleration;
};

#endif