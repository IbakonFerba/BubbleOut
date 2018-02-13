#pragma once

#ifndef PLAYER_PLATFORM_H
#define PLAYER_PLATFORM_H

#include "stdafx.h"
#include "Entity.h"
#include "RectCollider.h"
#include "Rigidbody.h"
#include "ShapeRenderer.h"

class PlayerPlatform : public Entity
{
public:
	PlayerPlatform() : Entity()
	{
		pushInheritanceChain<PlayerPlatform>();
	}
	~PlayerPlatform() {}

	float speed = 10.0;
	FloatVector2 movementDir;

	void init(ObjectManager* ptrObjectManager, const sf::Vector2f& pos);

	void move() const;

	sf::Vector2f getBounds() const;
	FloatVector2 getCenter() const;
private:
	Transform* m_ptr_trans;
	ShapeRenderer* m_ptr_rend;
	RectCollider* m_ptr_col;
	Rigidbody* m_ptr_rigidbody;
};

#endif