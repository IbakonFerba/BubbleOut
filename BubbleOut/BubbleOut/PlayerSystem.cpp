#include "stdafx.h"
#include "PlayerSystem.h"
#include "PlayerPlatform.h"

void PlayerSystem::movePlayer(ObjectManager* ptrObjManager, const MovementDirection& rDir)
{
	const ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* ptrPlayer = players.object_list_starts.at(i); ptrPlayer <= players.object_list_ends.at(i); ++ptrPlayer)
		{
			switch (rDir)
			{
			case MovementDirection::NONE:
				ptrPlayer->movementDir = FloatVector2(0, 0);
				break;
			case MovementDirection::LEFT:
				ptrPlayer->movementDir = FloatVector2(-ptrPlayer->SPEED, 0);
				break;
			case MovementDirection::RIGHT:
				ptrPlayer->movementDir = FloatVector2(ptrPlayer->SPEED, 0);
				break;
			}
		}
	}
}

void PlayerSystem::releaseBall(ObjectManager* ptrObjManager)
{
	const ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* ptrPlayer = players.object_list_starts.at(i); ptrPlayer <= players.object_list_ends.at(i); ++ptrPlayer)
		{
			if(ptrPlayer->holdingBall)
			{
				ptrPlayer->releaseBall();
			}
		}
	}
}

void PlayerSystem::updatePlayer(ObjectManager* ptrObjManager, const float& rWindowWidth, GameState& rState)
{
	const ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* ptrPlayer = players.object_list_starts.at(i); ptrPlayer <= players.object_list_ends.at(i); ++ptrPlayer)
		{
			//if there are no lifes left, change to game over state
			if(ptrPlayer->lives < 1)
			{
				ptrPlayer->sendGameOver();
				rState = GameState::GAME_OVER;
			}

			//make sure player stays inside window
			const FloatVector2 center = ptrPlayer->getCenter();
			const sf::Vector2f dim = ptrPlayer->getBounds();

			if (center.x - dim.x / 2 < 0 && ptrPlayer->movementDir.x < 0)
			{
				return;
			}
			else if (center.x + dim.x / 2 > rWindowWidth && ptrPlayer->movementDir.x > 0)
			{
				return;
			}

			ptrPlayer->move();
		}
	}


	const ObjectCollection<PlayerBall> balls = ptrObjManager->getObjectsOfType<PlayerBall>();

	for (unsigned i = 0; i < balls.object_list_starts.size(); ++i)
	{
		for (PlayerBall* ptrBall = balls.object_list_starts.at(i); ptrBall <= balls.object_list_ends.at(i); ++ptrBall)
		{
			//make sure player ball holds constant speed
			Rigidbody* rb = ptrBall->getRigidbody();
			FloatVector2 vel = rb->getVelocity();
			const float desiredSpeed = ptrBall->speed;
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

void PlayerSystem::resetPlayer(ObjectManager* ptrObjManager, const sf::Vector2f& rPlayerPos)
{
	const ObjectCollection<PlayerPlatform> players = ptrObjManager->getObjectsOfType<PlayerPlatform>();

	for (unsigned i = 0; i < players.object_list_starts.size(); ++i)
	{
		for (PlayerPlatform* ptrPlayer = players.object_list_starts.at(i); ptrPlayer <= players.object_list_ends.at(i); ++ptrPlayer)
		{
			ptrPlayer->reset(rPlayerPos);
		}
	}
}