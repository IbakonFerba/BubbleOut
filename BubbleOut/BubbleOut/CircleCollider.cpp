#include "stdafx.h"
#include "CircleCollider.h"

//----------------------------------------------------------------------
//init
void CircleCollider::init(const Transform* ptrTransform, const float radius)
{
	setTransform(ptrTransform);

	m_radius = radius;
}

//----------------------------------------------------------------------
//setter
void CircleCollider::setRadius(const float radius)
{
	m_radius = radius;
}

//----------------------------------------------------------------------
//getter
float CircleCollider::getRadius() const
{
	return m_radius;
}