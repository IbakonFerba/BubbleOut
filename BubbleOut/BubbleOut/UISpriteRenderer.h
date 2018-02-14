#pragma once

#ifndef UI_SPRITE_RENDERER_H
#define UI_SPRITE_RENDERER_H

#include "stdafx.h"
#include "SpriteRenderer.h"

class UISpriteRenderer : public SpriteRenderer
{
public:
	UISpriteRenderer() : SpriteRenderer()
	{
		pushInheritanceChain<UISpriteRenderer>();
	}
	~UISpriteRenderer() {}
};

#endif