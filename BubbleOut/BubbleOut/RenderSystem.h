#pragma once

#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "stdafx.h"
#include "ObjectManager.h"
#include "Renderer.h"

class RenderSystem
{
public:
	static void render(ObjectManager* objectManager, sf::RenderWindow& rWindow, const RenderTag& tagToRender);
};

#endif