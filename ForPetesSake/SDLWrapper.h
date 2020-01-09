#pragma once
#include <stdio.h>
#include <SDL.h>
#include <string>

#include "configurations.h"

// 'ld Be nice to put them as a member attributes in a Class SDLWRP
namespace Global {
	// The window we are rendering to
	extern SDL_Window* gMainWindow;

	// The surface contained by the window
	extern SDL_Surface* gScreenSurface;

	// The image we will load and show on screen
	extern  SDL_Surface* gLiveSurface;

	/*
		Fun Important Fact: SDL_Surface uses Software Rendering which means it is rendered by the CPU
	*/

	// Game active status
	extern bool gIsRunning;

	// Event handler
	extern SDL_Event gEvent;

	extern SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
}


// Be nice to convert to a Class later
namespace SDLWRP {
	bool Initialize();
	bool LoadMedia();
	void ShutDown();
	SDL_Surface* LoadSurface(std::string path);
	void LoadKeyPressSurfacesArray();
}