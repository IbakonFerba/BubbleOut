#include "stdafx.h"
#include "Engine.h"

#include "ObjectManager.h"
#include "TestObject.h"
#include "TextureCache.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "PlayerPlatform.h"
#include "PlayerSystem.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	setup();

	//======================================
	//TESTING AREA
	/*for(int i = 0; i < 100; ++i)
	{
		TestObject* obj2 = m_objectManager->getNewObject<TestObject>();
		obj2->init(m_objectManager, FloatVector2(i, i), FloatVector2(0, 10), 1, true);
	}

	TestObject* obj = m_objectManager->getNewObject<TestObject>();
	obj->init(m_objectManager, FloatVector2(600, 159), FloatVector2(7, 0), 1, false);
	obj->m_ptr_rigidbody->kinematic = true;*/
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
			m_objectManager->deleteObjects();
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
	m_state = GameState::PLAYING;

	//setup objects
	PlayerPlatform* player = m_objectManager->getNewObject<PlayerPlatform>();
	player->init(m_objectManager, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50));
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

	if(m_state == GameState::PLAYING)
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

		if(!input)
		{
			PlayerSystem::movePlayer(m_objectManager, MovementDirection::NONE);
		}
	}
}

//all updates happen in here
void Engine::update() const
{
	PlayerSystem::executePlayerMovement(m_objectManager, WINDOW_WIDTH);

	PhysicsSystem::handleCollision(m_objectManager, WINDOW_WIDTH, WINDOW_HEIGHT);
	PhysicsSystem::applyPhysics(m_objectManager);
}

//rendering happens in here
void Engine::render()
{
	//clear window
	m_window.clear();

	//draw objects
	RenderSystem::render(m_objectManager, m_window);

	//display image
	m_window.display();
}
