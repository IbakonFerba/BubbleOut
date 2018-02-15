#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"
#include "CircleCollider.h"
#include "RectCollider.h"

enum class MessageType
{
	DEFAULT,
	PLAYER_BALL_HIT_BOTTOM,
	COLLISION_ENTER,
	COLLISION_EXIT
};

struct Message
{
	MessageType type = MessageType::DEFAULT;
	Tag tag;
	CircleCollider* circle_collider;
	RectCollider* rect_collider;
};

class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void update(const Message& message) = 0;
};

#endif