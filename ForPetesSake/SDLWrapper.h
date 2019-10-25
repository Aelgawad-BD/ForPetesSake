#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>

#include "configurations.h"

namespace Global {

	// The window we are rendering to
	SDL_Window* window = NULL;

	// The surface contained by the window
	SDL_Surface* screenSurface = NULL;
}

namespace SDLWRP {
	std::string Initialize();
}