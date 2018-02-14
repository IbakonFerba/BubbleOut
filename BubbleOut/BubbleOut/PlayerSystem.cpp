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

void PlayerSystem::releaseBall(ObjectManager* ptrObjManager)
{
	ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* player = players.object_list_starts.at(i); player <= players.object_list_ends.at(i); ++player)
		{
			if(player->holdingBall)
			{
				player->releaseBall();
			}
		}
	}
}

void PlayerSystem::updatePlayer(ObjectManager* ptrObjManager, const float windowWidth, GameState& state)
{
	ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* player = players.object_list_starts.at(i); player <= players.object_list_ends.at(i); ++player)
		{
			if(player->lives < 1)
			{
				state = GameState::GAME_OVER;
			}

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


	ObjectCollection<PlayerBall> balls = ptrObjManager->getObjectsOfType<PlayerBall>();

	for (unsigned i = 0; i < balls.object_list_starts.size(); ++i)
	{
		for (PlayerBall* ball = balls.object_list_starts.at(i); ball <= balls.object_list_ends.at(i); ++ball)
		{
			Rigidbody* rb = ball->getRigidbody();
			FloatVector2 vel = rb->getVelocity();
			const float desiredSpeed = ball->speed;
			if(vel.magnitude() < desiredSpeed)
			{
				vel.normalize();
				const FloatVector2 acc = vel;
				rb->addForce(acc);
			} else if(vel.magnitude() > desiredSpeed)
			{
				vel.normalize();
				vel *= desiredSpeed;
				rb->setVelocity(vel);
			}
		}
	}
}

void PlayerSystem::resetPlayer(ObjectManager* ptrObjManager, const sf::Vector2f& playerPos)
{
	ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* player = players.object_list_starts.at(i); player <= players.object_list_ends.at(i); ++player)
		{
			player->reset(playerPos);
		}
	}
}