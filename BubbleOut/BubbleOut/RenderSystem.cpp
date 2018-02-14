#include "stdafx.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"

void RenderSystem::render(ObjectManager* objectManager, sf::RenderWindow& rWindow, const RenderTag& tagToRender)
{
	ObjectCollection<ShapeRenderer> sr = objectManager->getObjectsOfType<ShapeRenderer>();

	for (unsigned i = 0; i < sr.object_list_starts.size(); ++i)
	{
		for (ShapeRenderer* r = sr.object_list_starts.at(i); r <= sr.object_list_ends.at(i); ++r)
		{
			if (r->tag == tagToRender || r->tag == RenderTag::DEFAULT)
			{
				r->render(rWindow);
			}
		}
	}

	ObjectCollection<SpriteRenderer> spr = objectManager->getObjectsOfType<SpriteRenderer>();

	for (unsigned i = 0; i < spr.object_list_starts.size(); ++i)
	{
		for (SpriteRenderer* r = spr.object_list_starts.at(i); r <= spr.object_list_ends.at(i); ++r)
		{
			if (r->tag == tagToRender || r->tag == RenderTag::DEFAULT)
			{
				r->render(rWindow);
			}
		}
	}
}
