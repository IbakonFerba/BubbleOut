#include "stdafx.h"
#include "BubbleSystem.h"
#include "Bubble.h"

void BubbleSystem::spawnBubbles(ObjectManager* ptrObjManager)
{
	
}

void BubbleSystem::resetBubbles(ObjectManager* ptrObjManager)
{
	ObjectCollection<Bubble> bubbles = ptrObjManager->getObjectsOfType<Bubble>();

	for (unsigned i = 0; i < bubbles.object_list_starts.size(); ++i)
	{
		for (Bubble* bubble = bubbles.object_list_starts.at(i); bubble <= bubbles.object_list_ends.at(i); ++bubble)
		{
			bubble->reset();
		}
	}
}

void BubbleSystem::updateBubbles(ObjectManager* ptrObjManager, GameState& gameState)
{
	ObjectCollection<Bubble> bubbles = ptrObjManager->getObjectsOfType<Bubble>();

	bool allBubblesDisabled = true;
	for (unsigned i = 0; i < bubbles.object_list_starts.size(); ++i)
	{
		for (Bubble* bubble = bubbles.object_list_starts.at(i); bubble <= bubbles.object_list_ends.at(i); ++bubble)
		{
			if(bubble->getScale().x < bubble->MIN_SCALE)
			{
				bubble->disable();
			}

			if(bubble->enabled)
			{
				allBubblesDisabled = false;
			}
		}
	}

	if(allBubblesDisabled)
	{
		gameState = GameState::WON;
	}
}