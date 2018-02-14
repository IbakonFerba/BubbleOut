#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "stdafx.h"
#include "ObjectManager.h"

enum class GameState
{
	PLAYING,
	WON,
	GAME_OVER,
};

/*
 * Main class of the Chronos enigne that hosts
 * the main loop with updating, rendering and
 * managing objects
 */
class Engine
{
public:
	Engine() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BubbleOut", sf::Style::Default)
	{
		m_objectManager = new ObjectManager();
	}
	~Engine()
	{
		delete m_objectManager;
	}

	//defines size of the window
	static const int WINDOW_WIDTH = 900;
	static const int WINDOW_HEIGHT = 900;

	//update time step
	const float MS_PER_UPDATE = 16.66666;

	//run the engine
	void run();
private:
	ObjectManager* m_objectManager;
	sf::RenderWindow m_window;
	sf::Event m_event;

	GameState m_state;

	//engine functions
	void setup();
	void processInput();
	void update() const;
	void render();
};


#endif
