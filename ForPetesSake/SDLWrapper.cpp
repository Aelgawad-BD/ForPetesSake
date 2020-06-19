#include "SDLWrapper.h"

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
	this->gMainWindow = SDL_CreateWindow("The Law", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	//// Pre-Populate quick surfaces
	//// LoadKeyPressSurfacesArray();
	//LoadKeyPressTexturesArray();

	this->gBackgroundTexture.SetRenderer(this->gRenderer);
	this->gCharacterTexture.SetRenderer(this->gRenderer);
	this->gCharacterTexture.SetIsSpriteSheet(true);

	this->gCharacterTexture.IsSpriteSheet();

	this->gIsRunning = LoadSceneMedia();

	// All is well ends ok	
	return gIsRunning;
}

bool SDLWRP::LoadMediaSurface()
{
	//-// This function is a simple test you should populate the array and use that instead
	//const char* imageResourceLocation = "Resources/Bitmap/splash_screen.bmp"; // = img_SplashScreen_dir
	//this->gLiveSurface = SDL_LoadBMP(imageResourceLocation);
	//if (this->gLiveSurface == NULL)
	//{
	//	printf("ERROR >> Unable to Load Image %s\nSDL says: %s", imageResourceLocation, SDL_GetError());
	//	return false;
	//}
	return true;
}

bool SDLWRP::LoadMediaTexture()
{
	const char* imageResourceLocation = "Resources/Bitmap/splash_screen.bmp"; // = img_SplashScreen_dir
	this->gLiveSurface = SDL_LoadBMP(imageResourceLocation);
	if (this->gLiveSurface == NULL)
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

	SDL_DestroyTexture(this->gScreenTexture);
	this->gScreenTexture = NULL;

	//// Deallocate the image Surface // was used before texture
	//SDL_FreeSurface(this->gLiveSurface);
	//this->gLiveSurface = NULL;

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

SDL_Surface* SDLWRP::LoadSurface(std::string path)
{
	// - Load image at specified path
	// OPTIMIZED: you first  need to load the bitmap the regular way (which is functionally enough),
	//			 but then you need to optimize that same surface by calling SDL_ConvertSurface()

	// before it was // SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_Surface* optimizedSurface = NULL;
	if (loadedSurface == NULL)
	{
		printf(">> ERROR: Unable to load image %s", SDL_GetError());
	}	// Optimize here...
	else
	{
		//  Convert to screen format (This stretches out the img to fit the screen)
		optimizedSurface = SDL_ConvertSurface(loadedSurface, this->gScreenSurface->format, 0);
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

SDL_Texture* SDLWRP::LoadTexture(std::string path)
{
	SDL_Texture* newTexture = NULL;
	// IMG_Load gets an image of any format not just .bmp (any supported format that is)
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL)
	{
		printf(">> ERROR: Unable to load image %s", IMG_GetError());
		return NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(this->gRenderer, loadedSurface);
	if (newTexture == NULL)
		printf(">> ERROR: Unable to create texture from %s! SDL Error: %s\n", SDL_GetError());

	SDL_FreeSurface(loadedSurface);

	return newTexture;
}

// The function pre populates the array with 
void SDLWRP::LoadKeyPressSurfacesArray()
{
	bool success = true;

	// Load default surface
	this->gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = LoadSurface(img_SplashScreen_bmp);
	if (this->gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image.\n");
		success = false;
	}

	// Load up surface
	this->gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = LoadSurface(img_Up_bmp);
	if (this->gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image.\n");
		success = false;
	}

	// Load down surface
	this->gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = LoadSurface(img_Down_bmp);
	if (this->gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image.\n");
		success = false;
	}

	// Load left surface
	this->gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = LoadSurface(img_Left_bmp);
	if (this->gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image.\n");
		success = false;
	}

	// Load right surface
	this->gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = LoadSurface(img_Right_bmp);
	if (this->gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image.\n");
		success = false;
	}
}

// Does the same thing but with textures instead of surfaces
void SDLWRP::LoadKeyPressTexturesArray()
{
	bool success = true;

	// Load default surface
	this->gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] = LoadTexture(img_SplashScreen_bmp);
	if (this->gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] == NULL)
	{
		printf("Failed to load default image.\n");
		success = false;
	}

	// Load up surface
	this->gKeyPressTextures[KEY_PRESS_SURFACE_UP] = LoadTexture(img_Up_bmp);
	if (this->gKeyPressTextures[KEY_PRESS_SURFACE_UP] == NULL)
	{
		printf("Failed to load up image.\n");
		success = false;
	}

	// Load down surface
	this->gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = LoadTexture(img_Down_bmp);
	if (this->gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL)
	{
		printf("Failed to load down image.\n");
		success = false;
	}

	// Load left surface
	this->gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = LoadTexture(img_Left_bmp);
	if (this->gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL)
	{
		printf("Failed to load left image.\n");
		success = false;
	}

	// Load right surface
	this->gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] = LoadTexture(img_Right_bmp);
	if (this->gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] == NULL)
	{
		printf("Failed to load right image.\n");
		success = false;
	}
}

// is like LoadKeyPressTexturesArray but instead of having 5 imgs in an array it loads 2 imgs hard coded
bool SDLWRP::LoadSceneMedia()
{
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if (!this->gCharacterTexture.LoadFromFile(spriteSheet_mainCharcter_walkCycle_png))
	{
		printf("Failed to load Foo' texture image!\n");
		success = false;
	}

	//Load background texture
	if (!this->gBackgroundTexture.LoadFromFile(img_background_png))
	{
		printf("Failed to load background texture image!\n");
		success = false;
	}

	return success;
}

void SDLWRP::ShutSceneDown()
{
	// This applies to the whole system
	//   so it should be called on system close

	this->gCharacterTexture.Free();
	this->gBackgroundTexture.Free();

	//// Deallocate the image Surface // was used before texture
	//SDL_FreeSurface(this->gLiveSurface);
	//this->gLiveSurface = NULL;

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
