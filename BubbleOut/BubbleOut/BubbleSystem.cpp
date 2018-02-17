#include "stdafx.h"
#include "BubbleSystem.h"
#include "Bubble.h"

void BubbleSystem::spawnBubbles(ObjectManager* ptrObjManager, const int& rRows, const float& rSpacing, const int& rWindowWidth, SoundSystem& soundSystem)
{
	const int cols = (rWindowWidth / rSpacing)-1; //calc number of colums
	const float freeSpace = rWindowWidth - (cols-1) * rSpacing; //calculate how much space is left in the x Axis (needed for centering the field)

	for(int y = 0; y < rRows; ++y)
	{
		for(int x = 0; x < cols; ++x)
		{
			Bubble* ptrBubble = ptrObjManager->getNewObject<Bubble>();
			ptrBubble->addObserver(&soundSystem);
			ptrBubble->init(ptrObjManager, (x* rSpacing) + freeSpace/2, (y*rSpacing) + rSpacing);
		}
	}
}

void BubbleSystem::resetBubbles(ObjectManager* ptrObjManager)
{
	const ObjectCollection<Bubble> bubbles = ptrObjManager->getObjectsOfType<Bubble>();

	for (unsigned i = 0; i < bubbles.object_list_starts.size(); ++i)
	{
		for (Bubble* ptrBubble = bubbles.object_list_starts.at(i); ptrBubble <= bubbles.object_list_ends.at(i); ++ptrBubble)
		{
			ptrBubble->reset();
		}
	}
}

void BubbleSystem::updateBubbles(ObjectManager* ptrObjManager, GameState& rGameState, const int& rWindowWidth, const int& rWindowHeight)
{
	const ObjectCollection<Bubble> bubbles = ptrObjManager->getObjectsOfType<Bubble>();

	bool allBubblesDisabled = true;
	for (unsigned i = 0; i < bubbles.object_list_starts.size(); ++i)
	{
		for (Bubble* ptrBubble = bubbles.object_list_starts.at(i); ptrBubble <= bubbles.object_list_ends.at(i); ++ptrBubble)
		{
			//check if the bubble is smaller than the min allowed scale (which means the player destroyed it)
			if(ptrBubble->getScale().x < ptrBubble->MIN_SCALE && ptrBubble->enabled)
			{
				ptrBubble->disable();
			}

			//disable bubbles that managed to fly out of the window
			checkBubblePos(ptrBubble, rWindowWidth, rWindowHeight);
			

			if(ptrBubble->enabled)
			{
				allBubblesDisabled = false;
			}
		}
	}

	//if there is no active bubble, the player won
	if(allBubblesDisabled)
	{
		rGameState = GameState::WON;
	}
}

void BubbleSystem::checkBubblePos(Bubble* ptrBubble, const int& rWindowWidth, const int& rWindowHeight)
{
	const FloatVector2 pos = ptrBubble->getPosition();

	//check if bubble is outside the window
	if(pos.x < 0 || pos.x > rWindowWidth || pos.y < 0 || pos.y > rWindowHeight)
	{
		ptrBubble->enabled = false;
	}
}
