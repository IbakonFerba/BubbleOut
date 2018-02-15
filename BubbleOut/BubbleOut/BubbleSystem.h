#pragma once

#ifndef BUBBLE_SYSTEM_H
#define BUBBLE_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "Engine.h"

class BubbleSystem
{
public:
	static void spawnBubbles(ObjectManager* ptrObjManager);
	static void resetBubbles(ObjectManager* ptrObjManager);

	static void updateBubbles(ObjectManager* ptrObjManager, GameState& gameState);
};

#endif