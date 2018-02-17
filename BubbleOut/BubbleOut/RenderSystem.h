#pragma once

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "Renderer.h"

class RenderSystem
{
public:
	//render all renderes with the given Tag
	static void render(ObjectManager* objectManager, sf::RenderWindow& rWindow, const RenderTag& rTagToRender);
};

#endif