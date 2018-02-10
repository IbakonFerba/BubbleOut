#pragma once

#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include "stdafx.h"
#include "Renderer.h"

class CircleRenderer : public Renderer
{
public:
	CircleRenderer() : Renderer()
	{
		pushInheritanceChain<CircleRenderer>();
	}
	~CircleRenderer();

	void init(const Transform* ptrTrans, sf::CircleShape* ptrShape);
	void render(sf::RenderWindow& rWindow) const override;
private:
	sf::CircleShape* m_ptr_shape;
};

#endif
