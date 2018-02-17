#pragma once

#ifndef CIRCLE_COLLIDER_H
#define CIRCLE_COLLIDER_H

#include "stdafx.h"
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider() : Collider() {}
	~CircleCollider() {}

	void init(const Transform* ptrTransform, const float radius);
	void setRadius(const float radius);

	float getRadius() const;
private:
	float m_radius;
};

#endif