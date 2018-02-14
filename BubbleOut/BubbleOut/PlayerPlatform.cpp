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

	m_ptr_ball = m_ptr_objManager->getNewObject<PlayerBall>();

	//init objects
	m_ptr_trans->position.x = pos.x;
	m_ptr_trans->position.y = pos.y;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(200, 20));
	shape->setFillColor(sf::Color::Cyan);
	m_ptr_rend->init(m_ptr_trans, shape, Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	const sf::FloatRect rendBounds = m_ptr_rend->getBounds();
	m_ptr_col->init(m_ptr_trans, rendBounds.width, rendBounds.height);

	m_ptr_rigidbody->init(this, m_ptr_col, m_ptr_trans, 0, 1);
	m_ptr_rigidbody->kinematic = true;

	m_ptr_ball->init(m_ptr_objManager, 20);
	m_ptr_ball->addObserver(this);

	resetBall();

	//init values
	tag = Tag::PLAYER;
}

//-----------------------------------------------------------
//move
void PlayerPlatform::move() const
{
	m_ptr_trans->position += movementDir;

	if(holdingBall)
	{
		m_ptr_ball->setPosition(FloatVector2(m_ptr_trans->position.x, m_ptr_trans->position.y + m_ballStartOffset));
	}
}

//-----------------------------------------------------------
//ball
void PlayerPlatform::resetBall()
{
	m_ptr_ball->setPosition(FloatVector2(m_ptr_trans->position.x, m_ptr_trans->position.y + m_ballStartOffset));
	m_ptr_ball->getRigidbody()->kinematic = true;
	holdingBall = true;
}

void PlayerPlatform::releaseBall()
{
	holdingBall = false;
	m_ptr_ball->getRigidbody()->kinematic = false;
	m_ptr_ball->getRigidbody()->setVelocity(FloatVector2(0, -m_ptr_ball->speed));
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

//-----------------------------------------------------------
//observer
void PlayerPlatform::update(const Message& message)
{
	if(message.type == MessageType::PLAYER_BALL_HIT_BOTTOM)
	{
		if(m_ptr_ball != nullptr)
		{
			resetBall();
		}
	}
}
