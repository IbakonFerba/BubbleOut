#pragma once

#ifndef RECT_COLLIDER_H
#define RECT_COLLIDER_H

#include "stdafx.h"
#include "Collider.h"

class RectCollider : public Collider
{
public:
	RectCollider() : Collider() {}
	~RectCollider() {}

	void init(const Transform* ptrTransform, const float width, const float height);
	void setDimensions(const float width, const float height);

	FloatVector2 getDimensions() const;
private:
	FloatVector2 m_dimensions;
};

#endif