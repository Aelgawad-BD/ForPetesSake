#include "SDLWrapper.h";

using namespace std;

// The window we are rendering to
SDL_Window* Global::window = NULL;

// The surface contained by the window
SDL_Surface* Global::screenSurface = NULL;

int main(int argc, char* args[])
{
	if (SDLWRP::Initialize() == "")
	{
		// Fill the surface white
		SDL_FillRect(Global::screenSurface, NULL, SDL_MapRGB(Global::screenSurface->format, 0xFF, 0xFF, 0xFF));

		// Update thhe surface
		SDL_UpdateWindowSurface(Global::window);

		// Wait 
		SDL_Delay(TIME_DELAY);
	}
	return 0;
}