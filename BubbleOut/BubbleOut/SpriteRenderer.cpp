#include "stdafx.h"
#include "SpriteRenderer.h"
#include "TextureCache.h"

//----------------------------------------------------------------------
//init
void SpriteRenderer::init(const Transform* ptrTrans, const std::string& rTextureFilePath, const Origin& rOrigin)
{
	setTransform(ptrTrans);
	m_ptr_sprite = new sf::Sprite(*TextureCache::getTexture(rTextureFilePath));

	//set the origin of the sprite
	const sf::FloatRect bounds = getBounds();
	switch (rOrigin)
	{
	case Origin::TOP_LEFT: 
		m_ptr_sprite->setOrigin(0, 0);
		break;
	case Origin::TOP_CENTER:
		m_ptr_sprite->setOrigin(bounds.width / 2, 0);
		break;
	case Origin::TOP_RIGHT: 
		m_ptr_sprite->setOrigin(bounds.width, 0);
		break;
	case Origin::CENTER_LEFT:
		m_ptr_sprite->setOrigin(0, bounds.height / 2);
		break;
	case Origin::CENTER: 
		m_ptr_sprite->setOrigin(bounds.width/2, bounds.height / 2);
		break;
	case Origin::CENTER_RIGHT: 
		m_ptr_sprite->setOrigin(bounds.width, bounds.height / 2);
		break;
	case Origin::BOTTOM_LEFT:
		m_ptr_sprite->setOrigin(0, bounds.height);
		break;
	case Origin::BOTTOM_CENTER:
		m_ptr_sprite->setOrigin(bounds.width/2, bounds.height);
		break;
	case Origin::BOTTOM_RIGHT:
		m_ptr_sprite->setOrigin(bounds.width, bounds.height);
		break;
	}
}

//----------------------------------------------------------------------
//render
void SpriteRenderer::render(sf::RenderWindow& rWindow)
{
	m_ptr_sprite->setPosition(m_ptr_transform->position + m_offset);
	m_ptr_sprite->setRotation(m_ptr_transform->rotation);
	m_ptr_sprite->setScale(m_ptr_transform->scale);
	rWindow.draw(*m_ptr_sprite);
}




//----------------------------------------------------------------------
//getter
sf::FloatRect SpriteRenderer::getBounds() const
{
	return m_ptr_sprite->getGlobalBounds();
}

//----------------------------------------------------------------------
//setter
void SpriteRenderer::setTexture(const std::string& rTextureFilePath) const
{
	m_ptr_sprite->setTexture(*TextureCache::getTexture(rTextureFilePath));
}
