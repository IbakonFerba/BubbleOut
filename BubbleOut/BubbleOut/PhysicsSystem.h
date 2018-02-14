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
	static FloatVector2 checkCircleCircle(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c1, const CircleCollider* c2);
	static FloatVector2 checkRectRect(Rigidbody* rb1, Rigidbody* rb2, const RectCollider* r1, const RectCollider* r2);
	static FloatVector2 checkCircleRect(Rigidbody* rb1, Rigidbody* rb2, const CircleCollider* c, const RectCollider* r);

	static FloatVector2 checkEdges(Rigidbody* rb, const CircleCollider* c, const float windowWidth, const float windowHeight);
	static FloatVector2 checkEdges(Rigidbody* rb, const RectCollider* r, const float windowWidth, const float windowHeight);
};

#endif