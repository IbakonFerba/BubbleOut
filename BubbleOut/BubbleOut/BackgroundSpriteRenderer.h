#pragma once

#ifndef BACKGROUND_SPRITE_RENDERER_H
#define BACKGROUND_SPRITE_RENDERER_H

#include "stdafx.h"
#include "SpriteRenderer.h"

class BackgroundSpriteRenderer : public SpriteRenderer
{
public:
	BackgroundSpriteRenderer() : SpriteRenderer()
	{
		pushInheritanceChain<BackgroundSpriteRenderer>();
	}
	~BackgroundSpriteRenderer() {}
};

#endif