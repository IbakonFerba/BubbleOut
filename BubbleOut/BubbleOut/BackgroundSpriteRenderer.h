#pragma once

#ifndef BACKGROUND_SPRITE_RENDERER_H
#define BACKGROUND_SPRITE_RENDERER_H

#include "stdafx.h"
#include "SpriteRenderer.h"

/*
 * Sprite Renderer that is allways rendered 
 * before the normal Sprite Renderer
 */
class BackgroundSpriteRenderer : public SpriteRenderer
{
public:
	BackgroundSpriteRenderer() : SpriteRenderer() {}
	~BackgroundSpriteRenderer() {}
};

#endif