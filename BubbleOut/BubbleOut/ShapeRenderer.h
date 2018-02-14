#pragma once

#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include "stdafx.h"
#include "Renderer.h"

class ShapeRenderer : public Renderer
{
public:
	ShapeRenderer() : Renderer()
	{
		pushInheritanceChain<ShapeRenderer>();
	}
	virtual ~ShapeRenderer();

	void init(const Transform* ptrTrans, sf::Shape* ptrShape, const Origin& origin);
	void render(sf::RenderWindow& rWindow) override;

	sf::FloatRect getBounds() const override;
protected:
	sf::Shape* m_ptr_shape;
};

#endif
