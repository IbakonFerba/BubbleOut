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
void ShapeRenderer::init(const Transform* ptrTrans, sf::Shape* ptrShape)
{
	m_ptr_shape = ptrShape;
	setTransform(ptrTrans);
}

//----------------------------------------------------------------------
//render
void ShapeRenderer::render(sf::RenderWindow& rWindow) const
{
	m_ptr_shape->setPosition(m_ptr_transform->Position.getSfVector());
	rWindow.draw(*m_ptr_shape);
}



