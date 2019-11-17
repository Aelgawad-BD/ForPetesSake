#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>

#include "configurations.h"

namespace Global {
	// The window we are rendering to
	extern SDL_Window* window;

	// The surface contained by the window
	extern SDL_Surface* screenSurface;
}


namespace SDLWRP {
	std::string Initialize();
}