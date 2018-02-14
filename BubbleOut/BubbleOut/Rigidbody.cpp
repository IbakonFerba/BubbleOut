#include "stdafx.h"
#include "Rigidbody.h"

//----------------------------------------------------------------------
//init
void Rigidbody::init(const Entity* ptrEntity, const CircleCollider* ptrCollider, Transform* ptrTransform, const float drag, const float mass)
{
	m_ptr_entity = ptrEntity;
	m_ptr_circleCollider = ptrCollider;
	m_ptr_rectCollider = nullptr;
	m_ptr_transform = ptrTransform;
	m_drag = drag;
	m_mass = mass;

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;

	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;
}

void Rigidbody::init(const Entity* ptrEntity, const RectCollider* ptrCollider, Transform* ptrTransform, const float drag, const float mass)
{
	m_ptr_entity = ptrEntity;
	m_ptr_circleCollider = nullptr;
	m_ptr_rectCollider = ptrCollider;
	m_ptr_transform = ptrTransform;
	m_drag = drag;
	m_mass = mass;

	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;

	m_acceleration.x = 0.0f;
	m_acceleration.y = 0.0f;
}


//----------------------------------------------------------------------
//collision
void Rigidbody::collisionWith(const Rigidbody* other)
{
	m_observerMessage.tag = other->getEntity()->tag;
	notifyObservers();
}

void Rigidbody::collisionWith(const Tag& tag)
{
	m_observerMessage.tag = tag;
	notifyObservers();
}



//----------------------------------------------------------------------
//physics
void Rigidbody::addForce(const FloatVector2& force)
{
	if (kinematic)
	{
		return;
	}
	m_acceleration += force/m_mass;
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

	m_velocity *= (1 / (m_drag*0.01f + 1));
}

//----------------------------------------------------------------------
//getter
const Entity* Rigidbody::getEntity() const
{
	return m_ptr_entity;
}

const CircleCollider* Rigidbody::getCircleCollider() const
{
	return m_ptr_circleCollider;
}

const RectCollider* Rigidbody::getRectCollider() const
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



//----------------------------------------------------------------------
//observers
void Rigidbody::notifyObservers() const
{
	for(unsigned i = 0; i < m_observers.size(); ++i)
	{
		m_observers.at(i)->update(m_observerMessage);
	}
}



