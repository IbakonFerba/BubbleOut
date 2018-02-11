#pragma once

#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include "stdafx.h"

class TextureCache
{
public:
	TextureCache();
	~TextureCache();

	static sf::Texture* getTexture(const std::string& rFilename);

private:
	std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	static TextureCache* m_s_instance_; //singleton
};

#endif