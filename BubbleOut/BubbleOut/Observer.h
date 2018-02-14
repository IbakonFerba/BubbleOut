#pragma once

#ifndef OBSERVER_H
#define OBSERVER_H

#include "stdafx.h"
#include "Transform.h"

enum class MessageType
{
	DEFAULT,
	PLAYER_BALL_HIT_BOTTOM,
};

struct Message
{
	MessageType type = MessageType::DEFAULT;
	Tag tag;
};

class Observer
{
public:
	virtual void update(const Message& message) = 0;
};

#endif