#pragma once

#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "CircleCollider.h"
#include "RectCollider.h"
#include "Rigidbody.h"

/*
 * This system handles all collision
 * and physics of Rigidbodies
 */
class PhysicsSystem
{
public:
	//detects collisions and adds the resolving forces to the Rigidbodies but does not execute the Physics on the rigidbodies
	static void handleCollision(ObjectManager* ptrObjectManager, const float& rWindowWidth, const float& rWindowHeight);
	//executes Physics on the Rigidbodies
	static void applyPhysics(ObjectManager* ptrObjectManager);

private:
	static void checkCircleCircle(Rigidbody* ptrRb1, Rigidbody* ptrRb2, const CircleCollider* ptrC1, const CircleCollider* ptrC2);
	static void checkRectRect(Rigidbody* ptrRb1, Rigidbody* ptrRb2, const RectCollider* ptrR1, const RectCollider* ptrR2);
	static void checkCircleRect(Rigidbody* ptrRbC, Rigidbody* ptrRbR, const CircleCollider* ptrC, const RectCollider* ptrR);

	static void addToCollidingRbs(Rigidbody* ptrRb, Rigidbody* ptrCollidingRb);
	static void removeFromCollidingRbs(Rigidbody* ptrRb, Rigidbody* ptrCollidingRb);
};

#endif