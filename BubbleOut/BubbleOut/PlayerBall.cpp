#include "stdafx.h"
#include "PlayerBall.h"

//-------------------------------------------------------------
//init
void PlayerBall::init(ObjectManager* ptrObjectManager, const float radius)
{
	setObjectManager(ptrObjectManager);

	//get objects
	m_ptr_transform = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_col = m_ptr_objManager->getNewObject<CircleCollider>();
	m_ptr_rigidbody = m_ptr_objManager->getNewObject<Rigidbody>();
	m_ptr_rend = m_ptr_objManager->getNewObject<ShapeRenderer>();

	//setup objetcs
	sf::CircleShape* ptrShape = new sf::CircleShape(radius);
	ptrShape->setFillColor(sf::Color::Cyan);
	m_ptr_rend->init(m_ptr_transform, ptrShape, Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	m_ptr_col->init(m_ptr_transform, radius);

	m_ptr_rigidbody->init(this,m_ptr_col, m_ptr_transform, 0, 1);

	//set observer
	m_ptr_rigidbody->addObserver(this);
}



//-------------------------------------------------------------
//setter
void PlayerBall::setPosition(const FloatVector2& pos)
{
	m_ptr_transform->position = pos;
}

//-------------------------------------------------------------
//getter
Rigidbody* PlayerBall::getRigidbody()
{
	return m_ptr_rigidbody;
}



//-------------------------------------------------------------
//observer
void PlayerBall::update(const Message& message)
{
	if(message.tag == Tag::BORDER_BOTTOM)
	{
		notifyObservers();
	}
}


void PlayerBall::notifyObservers() const
{
	Message m;
	m.type = MessageType::PLAYER_BALL_HIT_BOTTOM;

	for (unsigned i = 0; i < m_observers.size(); ++i)
	{
		m_observers.at(i)->update(m);
	}
}

