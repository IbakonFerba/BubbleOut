#pragma once

#ifndef STDAFX_H
#define STDAFX_H

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <assert.h>

enum class Tag
{
	NONE = 0,
	TEST = 1
};

enum class Origin
{
	TOP_LEFT = 0,
	TOP_CENTER = 1,
	TOP_RIGHT = 2,
	CENTER_LEFT = 3,
	CENTER = 4,
	CENTER_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_CENTER = 7,
	BOTTOM_RIGHT = 8,
};

#endif