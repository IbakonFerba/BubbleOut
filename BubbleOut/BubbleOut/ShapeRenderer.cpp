#include "stdafx.h"
#include "ShapeRenderer.h"

//----------------------------------------------------------------------
//destructor
ShapeRenderer::~ShapeRenderer()
{
	delete m_ptr_shape;
}

//----------------------------------------------------------------------
//init
void ShapeRenderer::init(const Transform* ptrTrans, sf::Shape* ptrShape, const Origin& origin)
{
	m_ptr_shape = ptrShape;
	setTransform(ptrTrans);

	const sf::FloatRect bounds = getBounds();
	switch (origin)
	{
	case Origin::TOP_LEFT:
		m_ptr_shape->setOrigin(0, 0);
		break;
	case Origin::TOP_CENTER:
		m_ptr_shape->setOrigin(bounds.width / 2, 0);
		break;
	case Origin::TOP_RIGHT:
		m_ptr_shape->setOrigin(bounds.width, 0);
		break;
	case Origin::CENTER_LEFT:
		m_ptr_shape->setOrigin(0, bounds.height / 2);
		break;
	case Origin::CENTER:
		m_ptr_shape->setOrigin(bounds.width / 2, bounds.height / 2);
		break;
	case Origin::CENTER_RIGHT:
		m_ptr_shape->setOrigin(bounds.width, bounds.height / 2);
		break;
	case Origin::BOTTOM_LEFT:
		m_ptr_shape->setOrigin(0, bounds.height);
		break;
	case Origin::BOTTOM_CENTER:
		m_ptr_shape->setOrigin(bounds.width / 2, bounds.height);
		break;
	case Origin::BOTTOM_RIGHT:
		m_ptr_shape->setOrigin(bounds.width, bounds.height);
		break;
	}
}

//----------------------------------------------------------------------
//render
void ShapeRenderer::render(sf::RenderWindow& rWindow)
{
	m_ptr_shape->setPosition(m_ptr_transform->position);
	m_ptr_shape->setRotation(m_ptr_transform->rotation);
	m_ptr_shape->setScale(m_ptr_transform->scale);
	rWindow.draw(*m_ptr_shape);
}

//----------------------------------------------------------------------
//getter
sf::FloatRect ShapeRenderer::getBounds() const
{
	return m_ptr_shape->getGlobalBounds();
}

