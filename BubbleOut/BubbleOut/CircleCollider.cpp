#include "stdafx.h"
#include "CircleCollider.h"

//----------------------------------------------------------------------
//init
void CircleCollider::init(const Transform* ptrTransform, const float& rRadius)
{
	setTransform(ptrTransform);

	m_radius = rRadius;
}

//----------------------------------------------------------------------
//setter
void CircleCollider::setRadius(const float& rRadius)
{
	m_radius = rRadius;
}

//----------------------------------------------------------------------
//getter
float CircleCollider::getRadius() const
{
	return m_radius * ((m_ptr_transform->scale.x >= m_ptr_transform->scale.y) ? m_ptr_transform->scale.x : m_ptr_transform->scale.y);
}