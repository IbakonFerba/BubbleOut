#pragma once

#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "stdafx.h"
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider() : Collider(), m_radius(0){}
	~CircleCollider() {}

	//initialize the collider
	void init(const Transform* ptrTransform, const float& rRadius);
	void setRadius(const float& rRadius);

	float getRadius() const;
private:
	float m_radius;
};

#endif