#include "stdafx.h"
#include "Engine.h"

#include "ObjectManager.h"
#include "Renderer.h"
#include "TestObject.h"
#include "TextureCache.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	//setting up of needed systems
	TextureCache textureChache;

	//======================================
	//TESTING AREA
	TestObject* obj2 = m_objectManager->getNewObject<TestObject>();
	obj2->init(m_objectManager, FloatVector2(100, 100), FloatVector2(-7, 0), 1, true);

	TestObject* obj = m_objectManager->getNewObject<TestObject>();
	obj->init(m_objectManager, FloatVector2(600, 159), FloatVector2(7, 0), 1, false);
	obj->m_ptr_rigidbody->kinematic = true;
	obj->tag = Tag::TEST;
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
}

//all updates happen in here
void Engine::update()
{
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
