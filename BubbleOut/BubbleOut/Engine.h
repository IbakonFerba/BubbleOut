#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "stdafx.h"

/*
 * Main class of the enigne that hosts
 * the main loop with updating, rendering and
 * managing objects
 */
class Engine
{
public:
	Engine() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BubbleOut", sf::Style::Default) {}
	~Engine() {}

	//defines size of the window
	static const int WINDOW_WIDTH = 900;
	static const int WINDOW_HEIGHT = 900;

	//update time step
	const float MS_PER_UPDATE = 16.66666;

	//run the engine
	void run();
private:
	sf::RenderWindow m_window;
	sf::Event m_event;

	//engine functions
	void processInput();
	void update();
	void render();
};


#endif
