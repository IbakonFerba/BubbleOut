#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "stdafx.h"
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer() : Renderer()
	{
		pushInheritanceChain<SpriteRenderer>();
	}
	virtual ~SpriteRenderer()
	{
		delete m_ptr_sprite;
	}

	void init(const Transform* ptrTrans, const std::string& rTextureFilePath, const Origin& origin);
	void render(sf::RenderWindow& rWindow) override;

	sf::FloatRect getBounds() const override;
private:
	sf::Sprite* m_ptr_sprite;
};

#endif