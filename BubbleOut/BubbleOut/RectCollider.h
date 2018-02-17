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

	//initialize the Rect Collider
	void init(const Transform* ptrTransform, const float& rWidth, const float& rHeight);
	void setDimensions(const float& rWidth, const float& rHeight);

	FloatVector2 getDimensions() const;
private:
	FloatVector2 m_dimensions;
};

#endif