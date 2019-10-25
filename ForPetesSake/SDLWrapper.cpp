#include "SDLWrapper.h"

using namespace std;

string SDLWRP::Initialize()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return  "SDL couldn't initialize";
	}
	else
	{
		// Create Window
		Global::window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Global::window == NULL)
		{
			return "Window could not be created! SDL_ERROR: " + string(SDL_GetError());
		}
		else
		{
			Global::screenSurface = SDL_GetWindowSurface(Global::window);
		}
	}
	return "";
}