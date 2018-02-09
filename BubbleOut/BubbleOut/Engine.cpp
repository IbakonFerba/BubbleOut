#include "stdafx.h"
#include "Engine.h"

//----------------------------------------------------------------------
//main loop of the engine
void Engine::run()
{
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

void Engine::update()
{
	
}

void Engine::render()
{
	//clear window
	m_window.clear();

	//draw objects

	//display image
	m_window.display();
}