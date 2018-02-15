#include "stdafx.h"
#include "PlayerPlatform.h"
#include "ShapeRenderer.h"
#include "SoundSystem.h"

//-----------------------------------------------------------
//init
void PlayerPlatform::init(ObjectManager* ptrObjectManager, const sf::Vector2f& pos, SoundSystem& soundSystem)
{
	setObjectManager(ptrObjectManager);
	m_ptr_trans = m_ptr_objManager->getNewObject<Transform>();
	m_ptr_rend = m_ptr_objManager->getNewObject<ShapeRenderer>();
	m_ptr_rend2 = m_ptr_objManager->getNewObject<ShapeRenderer>();
	m_ptr_col = m_ptr_objManager->getNewObject<RectCollider>();
	m_ptr_col2 = m_ptr_objManager->getNewObject<RectCollider>();
	m_ptr_rigidbody = m_ptr_objManager->getNewObject<Rigidbody>();
	m_ptr_rigidbody2 = m_ptr_objManager->getNewObject<Rigidbody>();

	m_ptr_ball = m_ptr_objManager->getNewObject<PlayerBall>();

	for(int i = 0; i < MAX_LIVES; ++i)
	{
		m_liveDisplays[i] = m_ptr_objManager->getNewObject<UIShapeRenderer>();
		sf::CircleShape* liveBall = new sf::CircleShape(5);
		liveBall->setFillColor(sf::Color::Red);
		m_liveDisplays[i]->init(m_ptr_trans, liveBall, Origin::CENTER);
		m_liveDisplays[i]->setOffset(FloatVector2(-10 + i * 10, 0));
		m_liveDisplays[i]->tag = RenderTag::INGAME;
	}

	//init objects
	m_ptr_trans->position.x = pos.x;
	m_ptr_trans->position.y = pos.y;

	sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(200, 20));
	shape->setFillColor(sf::Color::Cyan);
	m_ptr_rend->init(m_ptr_trans, shape, Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	const FloatVector2 shape2Offset(0, -12.5);
	sf::RectangleShape* shape2 = new sf::RectangleShape(sf::Vector2f(100, 5));
	shape2->setFillColor(sf::Color::Cyan);
	m_ptr_rend2->init(m_ptr_trans, shape2, Origin::CENTER);
	m_ptr_rend2->setOffset(shape2Offset);
	m_ptr_rend2->tag = RenderTag::INGAME;

	const sf::FloatRect rendBounds = m_ptr_rend->getBounds();
	m_ptr_col->init(m_ptr_trans, rendBounds.width, rendBounds.height);

	const sf::FloatRect rendBounds2 = m_ptr_rend2->getBounds();
	m_ptr_col2->init(m_ptr_trans, rendBounds2.width, rendBounds2.height);
	m_ptr_col2->setOffset(shape2Offset);

	m_ptr_rigidbody->init(this, m_ptr_col, m_ptr_trans, 0, 1);
	m_ptr_rigidbody->kinematic = true;

	m_ptr_rigidbody2->init(this, m_ptr_col2, m_ptr_trans, 0, 1);
	m_ptr_rigidbody2->kinematic = true;

	m_ptr_ball->init(m_ptr_objManager, 20);
	m_ptr_ball->addObserver(this);
	m_ptr_ball->addObserver(&soundSystem);

	resetBall();

	//init values
	tag = Tag::PLAYER;
}

void PlayerPlatform::reset(const sf::Vector2f& pos)
{
	m_ptr_trans->position = pos;
	lives = MAX_LIVES;

	for (int i = 0; i < MAX_LIVES; ++i)
	{
		m_liveDisplays[i]->enabled = true;
	}
	resetBall();
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
	m_liveDisplays[lives - 1]->enabled = false;
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
		lives--;
		if(lives > 0)
		{
			resetBall();
		}
	}
}
