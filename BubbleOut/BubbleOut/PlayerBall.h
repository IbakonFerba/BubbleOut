#pragma once

#ifndef PLAYER_BALL_H
#define PLAYER_BALL_H

#include "stdafx.h"
#include "Entity.h"
#include "Transform.h"
#include "ShapeRenderer.h"
#include "CircleCollider.h"
#include "Rigidbody.h"

class PlayerBall : public Entity, public Observer, public Subject
{
public:
	PlayerBall() :Entity()
	{
		pushInheritanceChain<PlayerBall>();
	}
	~PlayerBall() {}

	float speed = 10.0f;

	void init(ObjectManager* ptrObjectManager, const float radius);

	void setPosition(const FloatVector2& pos);
	

	Rigidbody* getRigidbody();

	void update(const Message& message) override;
	void notifyObservers() const override;
private:
	Transform* m_ptr_transform;
	CircleCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;
	ShapeRenderer* m_ptr_rend;
};

#endif