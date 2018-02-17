#pragma once

#ifndef UI_SPRITE_RENDERER_H
#define UI_SPRITE_RENDERER_H

#include "stdafx.h"
#include "SpriteRenderer.h"

/*
 * A sprite Renderer that is allways rendered
 * after all normal sprite renderers
 */
class UISpriteRenderer : public SpriteRenderer
{
public:
	UISpriteRenderer() : SpriteRenderer() {}
	~UISpriteRenderer() {}
};

#endif