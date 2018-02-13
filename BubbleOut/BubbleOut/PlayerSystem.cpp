#include "stdafx.h"
#include "PlayerSystem.h"
#include "PlayerPlatform.h"

void PlayerSystem::movePlayer(ObjectManager* ptrObjManager, const MovementDirection& dir)
{
	ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* player = players.object_list_starts.at(i); player <= players.object_list_ends.at(i); ++player)
		{
			switch (dir)
			{
			case MovementDirection::NONE:
				player->movementDir = FloatVector2(0, 0);
				break;
			case MovementDirection::LEFT:
				player->movementDir = FloatVector2(-player->speed, 0);
				break;
			case MovementDirection::RIGHT:
				player->movementDir = FloatVector2(player->speed, 0);
				break;
			}
		}
	}
}

void PlayerSystem::executePlayerMovement(ObjectManager* ptrObjManager, const float windowWidth)
{
	ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* player = players.object_list_starts.at(i); player <= players.object_list_ends.at(i); ++player)
		{
			const FloatVector2 center = player->getCenter();
			sf::Vector2f dim = player->getBounds();

			if (center.x - dim.x / 2 < 0 && player->movementDir.x < 0)
			{
				return;
			}
			else if (center.x + dim.x / 2 > windowWidth && player->movementDir.x > 0)
			{
				return;
			}

			player->move();
		}
	}
}

