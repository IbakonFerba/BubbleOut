#include "stdafx.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "ShapeRenderer.h"
#include "SpriteRenderer.h"
#include "UIShapeRenderer.h"
#include "UISpriteRenderer.h"
#include "BackgroundSpriteRenderer.h"

void RenderSystem::render(ObjectManager* objectManager, sf::RenderWindow& rWindow, const RenderTag& tagToRender)
{
	ObjectCollection<BackgroundSpriteRenderer> bgSpr = objectManager->getObjectsOfType<BackgroundSpriteRenderer>();

	for (unsigned i = 0; i < bgSpr.object_list_starts.size(); ++i)
	{
		for (BackgroundSpriteRenderer* r = bgSpr.object_list_starts.at(i); r <= bgSpr.object_list_ends.at(i); ++r)
		{
			if (r->enabled && (r->tag == tagToRender || r->tag == RenderTag::DEFAULT))
			{
				r->render(rWindow);
			}
		}
	}

	ObjectCollection<ShapeRenderer> sr = objectManager->getObjectsOfType<ShapeRenderer>();

	for (unsigned i = 0; i < sr.object_list_starts.size(); ++i)
	{
		for (ShapeRenderer* r = sr.object_list_starts.at(i); r <= sr.object_list_ends.at(i); ++r)
		{
			if (r->enabled && (r->tag == tagToRender || r->tag == RenderTag::DEFAULT))
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
			if (r->enabled && (r->tag == tagToRender || r->tag == RenderTag::DEFAULT))
			{
				r->render(rWindow);
			}
		}
	}





	ObjectCollection<UIShapeRenderer> uiSr = objectManager->getObjectsOfType<UIShapeRenderer>();

	for (unsigned i = 0; i < uiSr.object_list_starts.size(); ++i)
	{
		for (UIShapeRenderer* r = uiSr.object_list_starts.at(i); r <= uiSr.object_list_ends.at(i); ++r)
		{
			if (r->enabled && (r->tag == tagToRender || r->tag == RenderTag::DEFAULT))
			{
				r->render(rWindow);
			}
		}
	}

	ObjectCollection<UISpriteRenderer> uiSpr = objectManager->getObjectsOfType<UISpriteRenderer>();

	for (unsigned i = 0; i < uiSpr.object_list_starts.size(); ++i)
	{
		for (UISpriteRenderer* r = uiSpr.object_list_starts.at(i); r <= uiSpr.object_list_ends.at(i); ++r)
		{
			if (r->enabled && (r->tag == tagToRender || r->tag == RenderTag::DEFAULT))
			{
				r->render(rWindow);
			}
		}
	}
}
