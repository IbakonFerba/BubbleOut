#pragma once

#ifndef PLAYER_PLATFORM_H
#define PLAYER_PLATFORM_H

#include "stdafx.h"
#include "Entity.h"
#include "RectCollider.h"
#include "Rigidbody.h"
#include "PlayerBall.h"
#include "SoundSystem.h"
#include "UISpriteRenderer.h"

/*
 * The Platform controlled by the Player
 */
class PlayerPlatform : public Entity, public Observer, public Subject
{
public:
	PlayerPlatform() : Entity(), m_ptr_trans(nullptr), m_ptr_rend(nullptr), m_ptr_rend2(nullptr), m_ptr_col(nullptr),
	                   m_ptr_col2(nullptr), m_ptr_rigidbody(nullptr), m_ptr_rigidbody2(nullptr), m_ptr_ball(nullptr) {}
	~PlayerPlatform() {}

	static const int MAX_LIVES = 4;
	const float SPEED = 10.0;

	int lives = MAX_LIVES;
	bool holdingBall = true;

	FloatVector2 movementDir;

	//initialize the platform
	void init(ObjectManager* ptrObjectManager, const sf::Vector2f& rPos, SoundSystem& rSoundSystem);
	void reset(const sf::Vector2f& rPos);

	void move() const;
	void releaseBall();

	//Send the game over event
	void sendGameOver();


	sf::Vector2f getBounds() const;
	FloatVector2 getCenter() const;

	//update observer
	void update(const Message& rMessage) override;
private:
	Transform* m_ptr_trans;
	SpriteRenderer* m_ptr_rend;
	SpriteRenderer* m_ptr_rend2;
	RectCollider* m_ptr_col;
	RectCollider* m_ptr_col2;
	Rigidbody* m_ptr_rigidbody;
	Rigidbody* m_ptr_rigidbody2;

	PlayerBall* m_ptr_ball;

	UISpriteRenderer* m_liveDisplays[MAX_LIVES];

	//ofset of the ball when it is held
	const float BALL_START_OFFSET = -35;

	void resetBall();
};

#endif