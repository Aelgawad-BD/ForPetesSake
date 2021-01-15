#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "configurations.h"
#include "SplashScreen.h"
#include "Environment.h"


// Handles all things SDL, used in this code base
//	need only have a single instance of it, consider Singelton DesPat

class SDLWRP {

public:
	SDLWRP();
	bool Initialize();
	void ShutDown();

	// The following draws all textures for the scene
	bool LoadSceneMedia();

	// The window we are rendering to
	SDL_Window* gMainWindow;

	// The surface contained by the window
	SDL_Surface* gScreenSurface;

	// The image we will load and show on screen
	SDL_Surface* gLiveSurface;

	// You need that with Textures
	SDL_Renderer* gRenderer;

	// Game active status
	bool gIsRunning;

	// Event handler
	SDL_Event gEvent;

	SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

	Game gGame;
	SplashScreen gStudioLogo;
	SplashScreen gTitleLogo;
};