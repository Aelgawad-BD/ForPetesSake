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

	/*
		Important Fun Fact: SDL_Surface uses Software Rendering which means it is rendered by the CPU

		Now will be using SDL_Texture instead of SDL_Surface which uses hardware rendering
		(which runs on GPU - Hardware acceleration)
	*/

	// You need that with Textures
	SDL_Renderer* gRenderer;

	// Game active status
	bool gIsRunning;

	// Event handler
	SDL_Event gEvent;

	//SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

	//-// Texture gBackgroundTexture;
	//-// Texture gCharacterTexture;

	// load entities not textures
	//  entities has textures amongst other things

	// Idea: Instead of having a background entity
	//       there should be an Environment class that has a background and a whole bunch of tiles
	//		I wonder if all the characters should be included in the Environment class as well (environment has a characters)

	Game gGame;
	SplashScreen gStudioLogo;
	SplashScreen gTitleLogo;
};