#pragma once

#ifndef PLAYER_BALL_H
#define PLAYER_BALL_H

#include "stdafx.h"
#include "Entity.h"
#include "Transform.h"
#include "CircleCollider.h"
#include "Rigidbody.h"
#include "SpriteRenderer.h"

class PlayerBall : public Entity, public Observer, public Subject
{
public:
	PlayerBall() : Entity(), m_ptr_transform(nullptr), m_ptr_col(nullptr), m_ptr_rigidbody(nullptr), m_ptr_rend(nullptr) {}

	~PlayerBall() {}

	float speed = 10.0f;

	void init(ObjectManager* ptrObjectManager) override;


	void setPosition(const FloatVector2& pos) const;
	

	Rigidbody* getRigidbody() const;

	void update(const Message& rMessage) override;
private:
	Transform* m_ptr_transform;
	CircleCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;
	SpriteRenderer* m_ptr_rend;
};

#endif