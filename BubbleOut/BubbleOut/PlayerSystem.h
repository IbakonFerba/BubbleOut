#pragma once

#ifndef PLAYER_SYSTEM_H
#define PLAYER_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"

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
	static void executePlayerMovement(ObjectManager* ptrObjManager, const float windowWidth);
};

#endif