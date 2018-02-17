#include "stdafx.h"
#include "Engine.h"

#include "ObjectManager.h"
#include "TextureCache.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "PlayerPlatform.h"
#include "PlayerSystem.h"
#include "Bubble.h"
#include "BubbleSystem.h"
#include "Barrier.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	setup();

	//======================================
	//TESTING AREA
	//======================================

	//main loop with fixed update rate and variable render time
	sf::Clock clock;
	double lag = 0.0;
	while (m_window.isOpen())
	{
		lag += clock.getElapsedTime().asMicroseconds() * 0.001;
		clock.restart();

		processInput();

		while (lag >= MS_PER_UPDATE)
		{
			update();
			//m_objectManager->deleteObjects();
			lag -= MS_PER_UPDATE;
		}
		
		render();
	}
}

//----------------------------------------------------------------------
//engine functions
void Engine::setup()
{
	//setting up of needed systems
	TextureCache textureChache;
	BubbleSystem::spawnBubbles(m_objectManager, 4, 120, WINDOW_WIDTH, m_soundSystem);
	addObserver(&m_soundSystem);

	//setup state
	m_state = GameState::STARTUP;

	//setup objects
	PlayerPlatform* player = m_objectManager->getNewObject<PlayerPlatform>();
	player->init(m_objectManager, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50), m_soundSystem);

	//barrier
	const float barrierThickness = 100;
	Barrier* ptrBTop = m_objectManager->getNewObject<Barrier>();
	ptrBTop->init(m_objectManager, FloatVector2(WINDOW_WIDTH / 2, -barrierThickness / 2), WINDOW_WIDTH + barrierThickness, barrierThickness, Tag::BORDER_TOP);

	Barrier* ptrBRight = m_objectManager->getNewObject<Barrier>();
	ptrBRight->init(m_objectManager, FloatVector2(WINDOW_WIDTH + barrierThickness/2, WINDOW_HEIGHT/2), barrierThickness, WINDOW_HEIGHT + barrierThickness, Tag::BORDER_RIGHT);

	Barrier* ptrBBottom = m_objectManager->getNewObject<Barrier>();
	ptrBBottom->init(m_objectManager, FloatVector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT + barrierThickness / 2), WINDOW_WIDTH + barrierThickness, barrierThickness, Tag::BORDER_BOTTOM);

	Barrier* ptrBLeft = m_objectManager->getNewObject<Barrier>();
	ptrBLeft->init(m_objectManager, FloatVector2(-barrierThickness / 2, WINDOW_HEIGHT / 2), barrierThickness, WINDOW_HEIGHT + barrierThickness, Tag::BORDER_LEFT);
}

void Engine::reset()
{
	m_sentWinEvent = false;
	PlayerSystem::resetPlayer(m_objectManager, m_playerStartPos);
	BubbleSystem::resetBubbles(m_objectManager);
}


void Engine::processInput()
{
	//dispatch events
	while (m_window.pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}

	if(m_state == GameState::STARTUP)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			m_observerMessage.type = MessageType::START_GAME;
			notifyObservers();
			m_state = GameState::PLAYING;
		}
	} else if(m_state == GameState::PLAYING)
	{
		bool input = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			PlayerSystem::movePlayer(m_objectManager, MovementDirection::LEFT);
			input = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			PlayerSystem::movePlayer(m_objectManager, MovementDirection::RIGHT);
			input = true;
		}

		if (!input)
		{
			PlayerSystem::movePlayer(m_objectManager, MovementDirection::NONE);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			PlayerSystem::releaseBall(m_objectManager);
		}
	} else if(m_state == GameState::GAME_OVER)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			reset();
			m_observerMessage.type = MessageType::START_GAME;
			notifyObservers();
			m_state = GameState::PLAYING;
		}
	} else if(m_state == GameState::WON)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			reset();
			m_observerMessage.type = MessageType::START_GAME;
			notifyObservers();
			m_state = GameState::PLAYING;
		}
	}
}

//all updates happen in here
void Engine::update()
{
	switch (m_state)
	{
	case GameState::STARTUP: break;
	case GameState::PLAYING:
		PlayerSystem::updatePlayer(m_objectManager, WINDOW_WIDTH, m_state);

		PhysicsSystem::handleCollision(m_objectManager, WINDOW_WIDTH, WINDOW_HEIGHT);
		PhysicsSystem::applyPhysics(m_objectManager);

		BubbleSystem::updateBubbles(m_objectManager, m_state, WINDOW_WIDTH, WINDOW_HEIGHT);
		break;
	case GameState::WON: 
		if(!m_sentWinEvent)
		{
			m_observerMessage.type = MessageType::WIN_GAME;
			notifyObservers();
			m_sentWinEvent = true;
		}
		break;
	case GameState::GAME_OVER: break;
	}
}

//rendering happens in here
void Engine::render()
{
	//clear window
	m_window.clear();

	//draw objects
	switch (m_state)
	{
	case GameState::STARTUP:
		RenderSystem::render(m_objectManager, m_window, RenderTag::INFO_SCREEN);
		break;
	case GameState::PLAYING: 
		RenderSystem::render(m_objectManager, m_window, RenderTag::INGAME);
		break;
	case GameState::WON: 
		RenderSystem::render(m_objectManager, m_window, RenderTag::INFO_SCREEN);
		break;
	case GameState::GAME_OVER: 
		RenderSystem::render(m_objectManager, m_window, RenderTag::INFO_SCREEN);
		break;
	}

	//display image
	m_window.display();
}

//----------------------------------------------------------------------
//observer
void Engine::notifyObservers() const
{
	for (unsigned i = 0; i < m_observers.size(); ++i)
	{
		m_observers.at(i)->update(m_observerMessage);
	}
}
