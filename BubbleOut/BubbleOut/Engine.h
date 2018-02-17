#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "SoundSystem.h"
#include "Subject.h"

enum class GameState
{
	STARTUP,
	PLAYING,
	WON,
	GAME_OVER,
};

/*
 * Main class of the Chronos enigne that hosts
 * the main loop with updating, rendering and
 * managing objects
 */
class Engine : public Subject
{
public:
	Engine() : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BubbleOut", sf::Style::Default), m_playerStartPos(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50)
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

	//observer
	void notifyObservers() const override;
private:
	ObjectManager* m_objectManager;
	sf::RenderWindow m_window;
	sf::Event m_event;
	SoundSystem m_soundSystem;

	const sf::Vector2f m_playerStartPos;

	GameState m_state;

	Message m_observerMessage;

	bool m_sentWinEvent = false;

	//engine functions
	void setup();
	void processInput();
	void update();
	void render();

	//game
	void reset();
};


#endif
