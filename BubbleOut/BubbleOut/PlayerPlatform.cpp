#include "stdafx.h"
#include "PlayerPlatform.h"
#include "SoundSystem.h"

//-----------------------------------------------------------
//init

void PlayerPlatform::init(ObjectManager* ptrObjectManager, const sf::Vector2f& rPos, SoundSystem& rSoundSystem)
{
	//get all components
	m_ptr_trans = ptrObjectManager->getNewObject<Transform>();
	m_ptr_rend = ptrObjectManager->getNewObject<SpriteRenderer>();
	m_ptr_rend2 = ptrObjectManager->getNewObject<SpriteRenderer>();
	m_ptr_col = ptrObjectManager->getNewObject<RectCollider>();
	m_ptr_col2 = ptrObjectManager->getNewObject<RectCollider>();
	m_ptr_rigidbody = ptrObjectManager->getNewObject<Rigidbody>();
	m_ptr_rigidbody2 = ptrObjectManager->getNewObject<Rigidbody>();

	m_ptr_ball = ptrObjectManager->getNewObject<PlayerBall>();

	//initializer life display
	for(int i = 0; i < MAX_LIVES; ++i)
	{
		const float lifeRad = 5;
		m_liveDisplays[i] = ptrObjectManager->getNewObject<UISpriteRenderer>();
		m_liveDisplays[i]->init(m_ptr_trans, "Assets/graphics/Life.png", Origin::CENTER);
		m_liveDisplays[i]->setOffset(FloatVector2(-lifeRad*(MAX_LIVES-1) + i * lifeRad*2, 0));
		m_liveDisplays[i]->tag = RenderTag::INGAME;
	}

	//init objects
	m_ptr_trans->position.x = rPos.x;
	m_ptr_trans->position.y = rPos.y;

	m_ptr_rend->init(m_ptr_trans, "Assets/graphics/Platform1.png", Origin::CENTER);
	m_ptr_rend->tag = RenderTag::INGAME;

	const FloatVector2 shape2Offset(0, -12.5);
	m_ptr_rend2->init(m_ptr_trans, "Assets/graphics/Platform2.png", Origin::CENTER);
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

	m_ptr_ball->init(ptrObjectManager);
	m_ptr_ball->addObserver(this);
	m_ptr_ball->addObserver(&rSoundSystem);

	resetBall();

	//init values
	tag = Tag::PLAYER;

	//add observer
	addObserver(&rSoundSystem);
}

void PlayerPlatform::reset(const sf::Vector2f& rPos)
{
	m_ptr_trans->position = rPos;
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
		m_ptr_ball->setPosition(FloatVector2(m_ptr_trans->position.x, m_ptr_trans->position.y + BALL_START_OFFSET));
	}
}

//-----------------------------------------------------------
//ball

void PlayerPlatform::resetBall()
{
	m_ptr_ball->setPosition(FloatVector2(m_ptr_trans->position.x, m_ptr_trans->position.y + BALL_START_OFFSET));
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
	return m_ptr_col->getDimensions().getSfVector();
}

FloatVector2 PlayerPlatform::getCenter() const
{
	return m_ptr_trans->position;
}

//-----------------------------------------------------------
//observer

void PlayerPlatform::sendGameOver()
{
	m_observerMessage.type = MessageType::GAME_OVER;
	notifyObservers();
}


void PlayerPlatform::update(const Message& rMessage)
{
	if(rMessage.type == MessageType::PLAYER_BALL_HIT_BOTTOM)
	{
		lives--;
		if(lives > 0)
		{
			resetBall();
		}
	}
}
