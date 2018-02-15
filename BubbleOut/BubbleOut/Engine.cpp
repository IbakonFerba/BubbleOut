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

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	setup();

	//======================================
	//TESTING AREA
	Bubble* b = m_objectManager->getNewObject<Bubble>();
	b->init(m_objectManager, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	Bubble* b2 = m_objectManager->getNewObject<Bubble>();
	b2->init(m_objectManager, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);
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

	//setup state
	m_state = GameState::STARTUP;

	//setup objects
	PlayerPlatform* player = m_objectManager->getNewObject<PlayerPlatform>();
	player->init(m_objectManager, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50));
}

void Engine::reset()
{
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
			m_state = GameState::PLAYING;
		}
	} else if(m_state == GameState::WON)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			reset();
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

		BubbleSystem::updateBubbles(m_objectManager, m_state);
		break;
	case GameState::WON: break;
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
