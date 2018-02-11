#include "stdafx.h"
#include "Engine.h"

#include "ObjectManager.h"
#include "Renderer.h"
#include "TestObject.h"
#include "TextureCache.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
	//setting up of needed systems
	TextureCache textureChache;

	//======================================
	//TESTING AREA
	TestObject* obj = m_objectManager->getNewObject<TestObject>();
	obj->init(m_objectManager);
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
	
}

//rendering happens in here
void Engine::render()
{
	//clear window
	m_window.clear();

	//draw objects
	ObjectCollection<Renderer> renderers = m_objectManager->getObjectsOfType<Renderer>();

	for(unsigned i = 0; i < renderers.object_list_starts.size(); ++i)
	{
		for(Renderer* r = renderers.object_list_starts.at(i); r <= renderers.object_list_ends.at(i); ++r)
		{
			r->render(m_window);
		}
	}

	//display image
	m_window.display();
}
