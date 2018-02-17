#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "stdafx.h"
#include "Renderer.h"

class SpriteRenderer : public Renderer
{
public:
	SpriteRenderer() : Renderer(), m_ptr_sprite(nullptr) {}
	virtual ~SpriteRenderer()
	{
		delete m_ptr_sprite;
	}

	void init(const Transform* ptrTrans, const std::string& rTextureFilePath, const Origin& rOrigin);
	void render(sf::RenderWindow& rWindow) override;

	sf::FloatRect getBounds() const override;

	void setTexture(const std::string& rTextureFilePath) const;
private:
	sf::Sprite* m_ptr_sprite;
};

#endif