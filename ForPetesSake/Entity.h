#pragma once
#include "LTexture.h"

// Anything that has an image file on the screen is an Entity
//  be it moving characters or inanimate props

class Entity
{
	int XPosition;
	int YPosition;
	LTexture texture;
	bool animate;
};

