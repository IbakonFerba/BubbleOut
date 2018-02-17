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

class PlayerPlatform : public Entity, public Observer, public Subject
{
public:
	PlayerPlatform() : Entity() {}
	~PlayerPlatform() {}

	static const int MAX_LIVES = 4;
	int lives = MAX_LIVES;

	const float speed = 10.0;
	FloatVector2 movementDir;
	bool holdingBall = true;

	void init(ObjectManager* ptrObjectManager, const sf::Vector2f& pos, SoundSystem& soundSystem);
	void reset(const sf::Vector2f& pos);

	void move() const;
	void releaseBall();

	void sendGameOver();


	sf::Vector2f getBounds() const;
	FloatVector2 getCenter() const;

	void update(const Message& message) override;
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

	float m_ballStartOffset = -35;

	void resetBall();
};

#endif