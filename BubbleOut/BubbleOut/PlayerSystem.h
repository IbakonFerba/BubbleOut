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

class PlayerSystem
{
public:
	static void movePlayer(ObjectManager* ptrObjManager, const MovementDirection& dir);
	static void updatePlayer(ObjectManager* ptrObjManager, const float windowWidth, GameState& state);

	static void releaseBall(ObjectManager* ptrObjManager);

	static void resetPlayer(ObjectManager* ptrObjManager, const sf::Vector2f& playerPos);
};

#endif