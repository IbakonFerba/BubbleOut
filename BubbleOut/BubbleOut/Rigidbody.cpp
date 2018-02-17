#include "stdafx.h"
#include "Rigidbody.h"

//----------------------------------------------------------------------
//init
void Rigidbody::init(const Entity* ptrEntity, CircleCollider* ptrCollider, Transform* ptrTransform, const float& rDrag, const float& rMass)
{
	m_ptr_entity = ptrEntity;
	m_ptr_circleCollider = ptrCollider;
	m_ptr_rectCollider = nullptr;
	m_ptr_transform = ptrTransform;
	drag = rDrag;
	mass = rMass;

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;

	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;
}

void Rigidbody::init(const Entity* ptrEntity, RectCollider* ptrCollider, Transform* ptrTransform, const float& rDrag, const float& rMass)
{
	m_ptr_entity = ptrEntity;
	m_ptr_circleCollider = nullptr;
	m_ptr_rectCollider = ptrCollider;
	m_ptr_transform = ptrTransform;
	drag = rDrag;
	mass = rMass;

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;

	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;
}


//----------------------------------------------------------------------
//collision
void Rigidbody::collisionWith(const Rigidbody* other)
{
	m_observerMessage.type = MessageType::COLLISION_ENTER;
	m_observerMessage.tag = other->getEntity()->tag;
	m_observerMessage.ptr_circle_collider = other->getCircleCollider();
	m_observerMessage.ptr_rect_collider = other->getRectCollider();

	notifyObservers();
	m_observerMessage.type = MessageType::DEFAULT;
}

void Rigidbody::collisionExitWith(const Rigidbody* other)
{
	m_observerMessage.type = MessageType::COLLISION_EXIT;
	m_observerMessage.tag = other->getEntity()->tag;
	m_observerMessage.ptr_circle_collider = other->getCircleCollider();
	m_observerMessage.ptr_rect_collider = other->getRectCollider();

	notifyObservers();
	m_observerMessage.type = MessageType::DEFAULT;
}



//----------------------------------------------------------------------
//physics
void Rigidbody::addForce(const FloatVector2& force)
{
	if (kinematic)
	{
		return;
	}
	m_acceleration += force/mass;
}

void Rigidbody::applyPhysics()
{
	if(kinematic)
	{
		return;
	}
	m_velocity += m_acceleration;
	m_acceleration.x = 0.0;
	m_acceleration.y = 0.0;

	m_ptr_transform->position += m_velocity;

	m_velocity *= (1 / (drag*0.01f + 1));
}

//----------------------------------------------------------------------
//getter
const Entity* Rigidbody::getEntity() const
{
	return m_ptr_entity;
}

CircleCollider* Rigidbody::getCircleCollider() const
{
	return m_ptr_circleCollider;
}

RectCollider* Rigidbody::getRectCollider() const
{
	return m_ptr_rectCollider;
}

FloatVector2 Rigidbody::getVelocity() const
{
	return m_velocity;
}

//----------------------------------------------------------------------
//setter
void Rigidbody::setVelocity(const FloatVector2& newVel)
{
	m_velocity = newVel;
}