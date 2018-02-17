#pragma once

#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "Engine.h"

enum class MovementDirection
{
	NONE,
	LEFT,
	RIGHT
};

/*
 * This system handles everything concerning the player
 */
class PlayerSystem
{
public:
	static void movePlayer(ObjectManager* ptrObjManager, const MovementDirection& rDir);
	static void updatePlayer(ObjectManager* ptrObjManager, const float& rWindowWidth, GameState& rState);

	static void releaseBall(ObjectManager* ptrObjManager);

	static void resetPlayer(ObjectManager* ptrObjManager, const sf::Vector2f& rPlayerPos);
};

#endif