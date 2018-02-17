#include "stdafx.h"
#include "RenderSystem.h"
#include "Renderer.h"
#include "SpriteRenderer.h"
#include "UISpriteRenderer.h"
#include "BackgroundSpriteRenderer.h"

void RenderSystem::render(ObjectManager* objectManager, sf::RenderWindow& rWindow, const RenderTag& rTagToRender)
{
	const ObjectCollection<BackgroundSpriteRenderer> bgSpr = objectManager->getObjectsOfType<BackgroundSpriteRenderer>();

	for (unsigned i = 0; i < bgSpr.object_list_starts.size(); ++i)
	{
		for (BackgroundSpriteRenderer* ptrRend = bgSpr.object_list_starts.at(i); ptrRend <= bgSpr.object_list_ends.at(i); ++ptrRend)
		{
			if (ptrRend->enabled && (ptrRend->tag == rTagToRender || ptrRend->tag == RenderTag::DEFAULT))
			{
				ptrRend->render(rWindow);
			}
		}
	}



	const ObjectCollection<SpriteRenderer> spr = objectManager->getObjectsOfType<SpriteRenderer>();

	for (unsigned i = 0; i < spr.object_list_starts.size(); ++i)
	{
		for (SpriteRenderer* ptrRend = spr.object_list_starts.at(i); ptrRend <= spr.object_list_ends.at(i); ++ptrRend)
		{
			if (ptrRend->enabled && (ptrRend->tag == rTagToRender || ptrRend->tag == RenderTag::DEFAULT))
			{
				ptrRend->render(rWindow);
			}
		}
	}





	const ObjectCollection<UISpriteRenderer> uiSpr = objectManager->getObjectsOfType<UISpriteRenderer>();

	for (unsigned i = 0; i < uiSpr.object_list_starts.size(); ++i)
	{
		for (UISpriteRenderer* ptrRend = uiSpr.object_list_starts.at(i); ptrRend <= uiSpr.object_list_ends.at(i); ++ptrRend)
		{
			if (ptrRend->enabled && (ptrRend->tag == rTagToRender || ptrRend->tag == RenderTag::DEFAULT))
			{
				ptrRend->render(rWindow);
			}
		}
	}
}
