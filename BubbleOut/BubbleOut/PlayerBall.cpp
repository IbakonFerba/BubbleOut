#include "stdafx.h"
#include "PlayerBall.h"

//-------------------------------------------------------------
//init
void PlayerBall::init(ObjectManager* ptrObjectManager)
{
	//get objects
	m_ptr_transform = ptrObjectManager->getNewObject<Transform>();
	m_ptr_col = ptrObjectManager->getNewObject<CircleCollider>();
	m_ptr_rigidbody = ptrObjectManager->getNewObject<Rigidbody>();
	m_ptr_rend = ptrObjectManager->getNewObject<SpriteRenderer>();

	//init values
	tag = Tag::PLAYER;

	//setup objetcs
	m_ptr_rend->init(m_ptr_transform, "Assets/graphics/Ball.png", Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	const sf::FloatRect rendBounds = m_ptr_rend->getBounds();
	m_ptr_col->init(m_ptr_transform, rendBounds.width/2);

	m_ptr_rigidbody->init(this,m_ptr_col, m_ptr_transform, 0, 1);

	//set observer
	m_ptr_rigidbody->addObserver(this);
}



//-------------------------------------------------------------
//setter
void PlayerBall::setPosition(const FloatVector2& pos) const
{
	m_ptr_transform->position = pos;
}

//-------------------------------------------------------------
//getter
Rigidbody* PlayerBall::getRigidbody() const
{
	return m_ptr_rigidbody;
}



//-------------------------------------------------------------
//observer
void PlayerBall::update(const Message& rMessage)
{
	if(rMessage.type == MessageType::COLLISION_ENTER)
	{
		if (rMessage.tag == Tag::BORDER_BOTTOM)
		{
			m_observerMessage.type = MessageType::PLAYER_BALL_HIT_BOTTOM;
			notifyObservers();
		}
	} else if(rMessage.type == MessageType::COLLISION_EXIT)
	{
		m_observerMessage.type = MessageType::PLAYER_BALL_IMPACT;
		notifyObservers();
	}
}