#include "SDLWrapper.h"
#include "Environment.h"

using namespace std;

SDLWRP::SDLWRP()
{
	Initialize();
}

bool SDLWRP::Initialize()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR >> SDL couldn't initialize\n SDL says: %s", SDL_GetError());
		return false;
	}

	// Create Window
	this->gMainWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (this->gMainWindow == NULL)
	{
		printf("ERROR >> Window could not be created! \n SDL says: %s", SDL_GetError());
		return false;
	}

	// Intialize Renderer (if you are using one)
	this->gRenderer = SDL_CreateRenderer(this->gMainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->gRenderer == NULL)
	{
		printf("ERROR >> Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	// Renderer was successfully created. Now initialize to color
	SDL_SetRenderDrawColor(this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG;
	if ((IMG_Init(imgFlags) & imgFlags) == false)
	{
		printf("ERROR >> SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	this->gScreenSurface = SDL_GetWindowSurface(this->gMainWindow);

	this->gGame.background.SetRenderer(this->gRenderer);
	this->gGame.mainCharacter.SetRenderer(this->gRenderer);
	this->gTitleLogo.SetRenderer(this->gRenderer);
	this->gStudioLogo.SetRenderer(this->gRenderer);

	gGame.OpenScene();

	this->gIsRunning = LoadSceneMedia();

	// All is well ends ok	
	return gIsRunning;
}

bool SDLWRP::LoadSceneMedia()
{
	//Loading success flag
	bool success = true;

	gTitleLogo.SetBlendMode(SDL_BLENDMODE_BLEND);

	//Load Intro texture
	if (!this->gTitleLogo.LoadTextureFromFile(img_title_png))
	{
		printf("Failed to load Intro texture image!\n");
		success = false;
	}

	//Load Intro texture
	if (!this->gStudioLogo.LoadTextureFromFile(img_studio_png))
	{
		printf("Failed to load Intro texture image!\n");
		success = false;
	}

	return success;
}

void SDLWRP::ShutDown()
{
	// This applies to the whole system
	//   so it should be called on system close

	this->gTitleLogo.Free();
	this->gStudioLogo.Free();

	//// Deallocate the image Surface // was used before texture
	// SDL_FreeSurface(this->gLiveSurface);
	// this->gLiveSurface = NULL;

	SDL_DestroyRenderer(this->gRenderer);
	this->gRenderer = NULL;

	// Same for the Window
	SDL_DestroyWindow(this->gMainWindow);
	this->gMainWindow = NULL;

	// Quit SDL Subsystems
	IMG_Quit();
	SDL_Quit();

	printf("Application closed successfully");
}
