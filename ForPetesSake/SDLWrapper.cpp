#include "SDLWrapper.h"

using namespace std;


bool SDLWRP::Initialize()
{
	// Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("ERROR >> SDL couldn't initialize\n SDL says: %s", SDL_GetError());
		return false;
	}

	// Create Window
	Global::gMainWindow = SDL_CreateWindow("UnDecided", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (Global::gMainWindow == NULL)
	{
		printf("ERROR >> Window could not be created! \n SDL says: %s", SDL_GetError());
		return false;
	}

	 Global::gScreenSurface = SDL_GetWindowSurface(Global::gMainWindow);

	// Pre-Populate quick surfaces
	LoadKeyPressSurfacesArray();


	return true;
}

bool SDLWRP::LoadMedia()
{
	const char* imageResourceLocation = "Resources/Bitmap/splash_screen.bmp"; // = img_SplashScreen_dir
	Global::gLiveSurface = SDL_LoadBMP(imageResourceLocation);
	if (Global::gLiveSurface == NULL)
	{
		printf("ERROR >> Unable to Load Image %s\nSDL says: %s", imageResourceLocation, SDL_GetError());
		return false;
	}
	return true;
}

void SDLWRP::ShutDown()
{
	// This applies to the whole system
	//   so it should be called on system close

	// Deallocate the image Surface
	SDL_FreeSurface(Global::gLiveSurface);
	Global::gLiveSurface = NULL;

	// Same for the Window
	SDL_DestroyWindow(Global::gMainWindow);
	Global::gMainWindow = NULL;

	// Quit SDL Subsystems
	SDL_Quit();

	printf("Application closed successfully");
}

SDL_Surface* SDLWRP::LoadSurface(std::string path)
{
	// - Load image at specified path

	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf(">> ERROR: Unable to load image %s", SDL_GetError());
	}
	return loadedSurface;
}

/// The function pre populates the array with 
void SDLWRP::LoadKeyPressSurfacesArray()
{
	bool success = true;

	// Load default surface
	Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface(img_SplashScreen_dir);
	if (Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image.\n");
		success = false;
	}

	// Load up surface
	Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface(img_Up_dir);
	if (Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image.\n");
		success = false;
	}

	// Load down surface
	Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface(img_Down_dir);
	if (Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image.\n");
		success = false;
	}

	// Load left surface
	Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface(img_Left_dir);
	if (Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image.\n");
		success = false;
	}

	// Load right surface
	Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface(img_Right_dir);
	if (Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image.\n");
		success = false;
	}
}
