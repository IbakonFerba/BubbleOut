#pragma once

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "Rigidbody.h"

class PhysicsSystem
{
public:
	static void handleCollision(ObjectManager* ptrObjectManager, const float windowWidth, const float windowHeight);
	static void applyPhysics(ObjectManager* ptrObjectManager);

private:
	static void checkCircleCircle(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c1, const CircleCollider* c2);
	static void checkRectRect(Rigidbody* rb1, Rigidbody* rb2, const RectCollider* r1, const RectCollider* r2);
	static void checkCircleRect(Rigidbody* rbC, Rigidbody* rbR, const CircleCollider* c, const RectCollider* r);

	static void addToCollidingRbs(Rigidbody* rb, Rigidbody* collidingRb);
	static void removeFromCollidingRbs(Rigidbody* rb, Rigidbody* collidingRb);
};

#endif