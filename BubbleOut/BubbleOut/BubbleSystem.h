#pragma once

#ifndef BUBBLE_SYSTEM_H
#define BUBBLE_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "Engine.h"
#include "SoundSystem.h"
#include "Bubble.h"

class BubbleSystem
{
public:
	static void spawnBubbles(ObjectManager* ptrObjManager, const int rows, const float spacing, const int windowWidth, SoundSystem& soundSystem);
	static void resetBubbles(ObjectManager* ptrObjManager);

	static void updateBubbles(ObjectManager* ptrObjManager, GameState& gameState, const int& windowWidth, const int& windowHeight);

private:
	static void checkBubblePos(Bubble* bubble, const int& windowWidth, const int& windowHeight);
};

#endif