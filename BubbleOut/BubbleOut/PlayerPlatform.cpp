#include "stdafx.h"
#include "PlayerPlatform.h"
#include "ShapeRenderer.h"

//-----------------------------------------------------------
//init
void PlayerPlatform::init(ObjectManager* ptrObjectManager, const sf::Vector2f& pos)
{
	setObjectManager(ptrObjectManager);
	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<ShapeRenderer>();
	m_ptr_col = m_ptr_objManager->getNewObject<RectCollider>();
	m_ptr_rigidbody = m_ptr_objManager->getNewObject<Rigidbody>();

	//init objects
	m_ptr_trans->position.x = pos.x;
	m_ptr_trans->position.y = pos.y;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(200, 20));
	shape->setFillColor(sf::Color::Cyan);
	m_ptr_rend->init(m_ptr_trans, shape, Origin::CENTER);

	sf::FloatRect rendBounds = m_ptr_rend->getBounds();
	m_ptr_col->init(m_ptr_trans, rendBounds.width, rendBounds.height);

	m_ptr_rigidbody->init(this, m_ptr_col, m_ptr_trans, 0, 1);
	m_ptr_rigidbody->kinematic = true;

	//init values
	tag = Tag::PLAYER;
}

//-----------------------------------------------------------
//move
void PlayerPlatform::move() const
{
	m_ptr_trans->position += movementDir;
}

//-----------------------------------------------------------
//getter
sf::Vector2f PlayerPlatform::getBounds() const
{
	return m_ptr_col->getDimensions();
}

FloatVector2 PlayerPlatform::getCenter() const
{
	return m_ptr_trans->position;
}

