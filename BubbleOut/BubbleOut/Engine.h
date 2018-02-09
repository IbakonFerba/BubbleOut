#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "stdafx.h"

class Engine
{
public:
	Engine() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BubbleOut", sf::Style::Default) {}
	~Engine() {}

	static const int WINDOW_WIDTH = 900;
	static const int WINDOW_HEIGHT = 900;

	const float MS_PER_UPDATE = 16.66666;

	void run();

private:
	sf::RenderWindow m_window;
	sf::Event m_event;

	void processInput();
	void update();
	void render();
};


#endif
