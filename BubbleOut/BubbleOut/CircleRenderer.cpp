#include "stdafx.h"
#include "CircleRenderer.h"

//----------------------------------------------------------------------
//destructor
CircleRenderer::~CircleRenderer()
{
	delete m_ptr_shape;
}

//----------------------------------------------------------------------
//init
void CircleRenderer::init(const Transform* ptrTrans, sf::CircleShape* ptrShape)
{
	m_ptr_shape = ptrShape;
	setTransform(ptrTrans);
}

//----------------------------------------------------------------------
//render
void CircleRenderer::render(sf::RenderWindow& rWindow) const
{
	m_ptr_shape->setPosition(m_ptr_transform->Position.getSfVector());
	rWindow.draw(*m_ptr_shape);
}


