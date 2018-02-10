#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "GameObject.h"
#include "Transform.h"

class Renderer : public GameObject
{
public:
	Renderer() : GameObject()
	{
		pushInheritanceChain<Renderer>();
	}
	~Renderer() {}

	virtual void render(sf::RenderWindow& rWindow) const {}

	void setTransform(const Transform* t) { m_ptr_transform = t; }

protected:
	const Transform* m_ptr_transform;
};

#endif