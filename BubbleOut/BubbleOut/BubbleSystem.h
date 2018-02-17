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
	static void spawnBubbles(ObjectManager* ptrObjManager, const int& rRows, const float& rSpacing, const int& rWindowWidth, SoundSystem& soundSystem);
	static void resetBubbles(ObjectManager* ptrObjManager);

	static void updateBubbles(ObjectManager* ptrObjManager, GameState& rGameState, const int& rWindowWidth, const int& rWindowHeight);

private:
	static void checkBubblePos(Bubble* ptrBubble, const int& rWindowWidth, const int& rWindowHeight);
};

#endif