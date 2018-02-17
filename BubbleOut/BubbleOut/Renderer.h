#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "stdafx.h"
#include "Transform.h"

enum class RenderTag
{
	DEFAULT,
	INFO_SCREEN,
	INGAME
};

class Renderer
{
public:
	Renderer() : m_ptr_transform(nullptr), m_offset(0.0f, 0.0f) {}
	virtual ~Renderer() {}

	RenderTag tag = RenderTag::DEFAULT;
	bool enabled = true;

	virtual void render(sf::RenderWindow& rWindow) {}

	void setTransform(const Transform* ptrTrans) { m_ptr_transform = ptrTrans; }
	void setOffset(const FloatVector2& rOffset) { m_offset = rOffset; }

	virtual sf::FloatRect getBounds() const = 0;

protected:
	const Transform* m_ptr_transform;
	FloatVector2 m_offset;
};

#endif