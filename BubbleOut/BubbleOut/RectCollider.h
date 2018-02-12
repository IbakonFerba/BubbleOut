#pragma once

#ifndef RECT_COLLIDER_H
#define RECT_COLLIDER_H

#include "stdafx.h"
#include "Collider.h"

class RectCollider : public Collider
{
public:
	RectCollider() : Collider()
	{
		pushInheritanceChain<RectCollider>();
	}
	~RectCollider() {}

	void init(const Transform* ptrTransform, const float width, const float height);
	void setDimensions(const float width, const float height);

	sf::Vector2f getDimensions() const;
private:
	sf::Vector2f m_dimensions;
};

#endif