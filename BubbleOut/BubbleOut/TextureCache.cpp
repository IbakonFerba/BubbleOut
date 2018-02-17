#include "stdafx.h"
#include "TextureCache.h"

TextureCache* TextureCache::m_s_instance_ = nullptr;

//------------------------------------------------------------------------------------------
//Constructor
TextureCache::TextureCache()
{
	assert(m_s_instance_ == nullptr); //makes sure this is true, otherwise it won't continue
	m_s_instance_ = this;
}

//------------------------------------------------------------------------------------------
//get textures
sf::Texture* TextureCache::getTexture(const std::string& rFilename)
{
	auto& rTextureCache = m_s_instance_->m_textures;
	auto const cacheElement = rTextureCache.find(rFilename);

	//find out wether we found a match
	if (cacheElement != rTextureCache.end())
	{
		return cacheElement->second;
	}
	else
	{
		//create a texture to hold a graphic on the GPU
		sf::Texture* ptrTexture = new sf::Texture(); //allocate texture on heap, not on stack (heap is controlled by programmer (there is no garbage collection, we have to manage that ourselfs)(dynamic allocation), stack cannot be controlled (automatic allocation))
													 //load a graphic into the texture
		ptrTexture->loadFromFile(rFilename); //that (->) loads the value of the pointer, could also write (*texture)
		ptrTexture->setSmooth(false);

		rTextureCache[rFilename] = ptrTexture;

		return ptrTexture;
	}
}
