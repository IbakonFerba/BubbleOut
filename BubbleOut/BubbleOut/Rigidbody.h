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
	Rigidbody() : drag(0), mass(1), kinematic(false), m_ptr_entity(nullptr), m_ptr_circleCollider(nullptr),
	              m_ptr_rectCollider(nullptr), m_ptr_transform(nullptr),
	              m_velocity(0.0, 0.0), m_acceleration(0.0, 0.0) {}
	~Rigidbody() {}

	float drag;
	float mass;
	bool kinematic;
	bool enabled = true;

	std::vector<Rigidbody*> collidingRigidbodys;

	//initialize the Rigidbody with a Circle Collider
	void init(const Entity* ptrEntity, CircleCollider* ptrCollider, Transform* ptrTransform, const float& rDrag, const float& rMass);
	//initialize the Rigidbody with a Rect Collider
	void init(const Entity* ptrEntity, RectCollider* ptrCollider, Transform* ptrTransform, const float& rDrag, const float& rMass);

	//call when colliding with a Rigdbody
	void collisionWith(const Rigidbody* ptrOther);
	//Call when stopping to collide with Rigidbody
	void collisionExitWith(const Rigidbody* ptrOther);
	//Add a force to be applied when the next physics update happens
	void addForce(const FloatVector2& rForce);

	//update velocity
	void applyPhysics();

	const Entity* getEntity() const;
	CircleCollider* getCircleCollider() const;
	RectCollider* getRectCollider() const;
	FloatVector2 getVelocity() const;

	void setVelocity(const FloatVector2& rNewVel);
private:
	const Entity* m_ptr_entity;
	CircleCollider* m_ptr_circleCollider;
	RectCollider* m_ptr_rectCollider;
	Transform* m_ptr_transform;
	FloatVector2 m_velocity;
	FloatVector2 m_acceleration;
};

#endif