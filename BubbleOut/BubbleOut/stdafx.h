#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <assert.h>

enum class Tag
{
	NONE,
	BORDER_TOP,
	BORDER_RIGHT,
	BORDER_BOTTOM,
	BORDER_LEFT,
	PLAYER,
	BUBBLE,
};

enum class Origin
{
	TOP_LEFT,
	TOP_CENTER,
	TOP_RIGHT,
	CENTER_LEFT,
	CENTER,
	CENTER_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_CENTER,
	BOTTOM_RIGHT,
};

#endif