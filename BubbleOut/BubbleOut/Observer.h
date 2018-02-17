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
	COLLISION_EXIT,
	PLAYER_BALL_IMPACT,
	BUBBLE_IMPACT,
	GAME_OVER,
	START_GAME,
	WIN_GAME,
	BUBBLE_DESTROYED,
};

struct Message
{
	MessageType type = MessageType::DEFAULT;
	Tag tag;
	CircleCollider* ptr_circle_collider;
	RectCollider* ptr_rect_collider;
};

class Observer
{
public:
	Observer() {}
	virtual ~Observer() {}
	virtual void update(const Message& rMessage) = 0;
};

#endif