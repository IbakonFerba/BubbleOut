#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "EngineObject.h"
#include "Transform.h"

enum class RenderTag
{
	DEFAULT,
	INFO_SCREEN,
	INGAME
};

class Renderer : public EngineObject
{
public:
	Renderer() : EngineObject()
	{
		pushInheritanceChain<Renderer>();
	}
	virtual ~Renderer() {}

	RenderTag tag = RenderTag::DEFAULT;

	virtual void render(sf::RenderWindow& rWindow) {}

	void setTransform(const Transform* t) { m_ptr_transform = t; }

	virtual sf::FloatRect getBounds() const = 0;

protected:
	const Transform* m_ptr_transform;
};

#endif