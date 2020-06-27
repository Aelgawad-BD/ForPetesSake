#pragma once

#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "configurations.h"

#include "Entity.h"
#include "Character.h"



// Be nice to convert to a Class later
class SDLWRP {

public:
	SDLWRP();
	bool Initialize();
	bool LoadMediaSurface();
	bool LoadMediaTexture();
	void ShutDown();
	SDL_Surface* LoadSurface(std::string path);
	SDL_Texture* LoadTexture(std::string path);
	void LoadKeyPressSurfacesArray();
	void LoadKeyPressTexturesArray();

	// lesson 10
	// the following draws all textures for the scene
	bool LoadSceneMedia();
	void ShutSceneDown();

	// The window we are rendering to
	SDL_Window* gMainWindow;

	// The surface contained by the window
	SDL_Surface* gScreenSurface;

	// The image we will load and show on screen
	SDL_Surface* gLiveSurface;

	/*
		Important Fun Fact: SDL_Surface uses Software Rendering which means it is rendered by the CPU
	*/

	/*
		Now will be using SDL_Texture instead of SDL_Surface which uses hardware rendering
		(which runs on GPU - Hardware acceleration)
	*/

	// This will replace the screenSurface
	SDL_Texture* gScreenTexture;

	// You need that with Textures
	SDL_Renderer* gRenderer;

	// Game active status
	bool gIsRunning;

	// Event handler
	SDL_Event gEvent;

	SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

	SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

	Texture gBackgroundTexture;
	Texture gCharacterTexture;

	// load entities not textures
	//  entities has textures amongst other things
	Entity gBackground;
	Character gMainCharacter;
};