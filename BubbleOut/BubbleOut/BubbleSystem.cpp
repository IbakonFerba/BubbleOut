
#include "stdafx.h"
#include "BubbleSystem.h"
#include "Bubble.h"

void BubbleSystem::spawnBubbles(ObjectManager* ptrObjManager, const int rows, const float spacing, const int windowWidth, SoundSystem& soundSystem)
{
	int cols = (windowWidth / spacing)-1;
	float freeSpace = windowWidth - (cols-1) * spacing;
	for(int y = 0; y < rows; ++y)
	{
		for(int x = 0; x < cols; ++x)
		{
			Bubble* bubble = ptrObjManager->getNewObject<Bubble>();
			bubble->addObserver(&soundSystem);
			bubble->init(ptrObjManager, (x* spacing) + freeSpace/2, (y*spacing) + spacing);
		}
	}
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

void BubbleSystem::updateBubbles(ObjectManager* ptrObjManager, GameState& gameState, const int& windowWidth, const int& windowHeight)
{
	ObjectCollection<Bubble> bubbles = ptrObjManager->getObjectsOfType<Bubble>();

	bool allBubblesDisabled = true;
	for (unsigned i = 0; i < bubbles.object_list_starts.size(); ++i)
	{
		for (Bubble* bubble = bubbles.object_list_starts.at(i); bubble <= bubbles.object_list_ends.at(i); ++bubble)
		{
			if(bubble->getScale().x < bubble->MIN_SCALE && bubble->enabled)
			{
				bubble->disable();
			}

			checkBubblePos(bubble, windowWidth, windowHeight);
			

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

void BubbleSystem::checkBubblePos(Bubble* bubble, const int& windowWidth, const int& windowHeight)
{
	const FloatVector2 pos = bubble->getPosition();

	if(pos.x < 0 || pos.x > windowWidth || pos.y < 0 || pos.y > windowHeight)
	{
		bubble->enabled = false;
	}
}
