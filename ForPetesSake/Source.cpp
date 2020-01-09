#include "SDLWrapper.h";

using namespace std;

// The window we are rendering to
SDL_Window* Global::gMainWindow = NULL;

// The surface contained by the window
SDL_Surface* Global::gScreenSurface = NULL;

// a.k.a gCurrentSurface
SDL_Surface* Global::gLiveSurface = NULL;

bool Global::gIsRunning = true;

SDL_Event Global::gEvent;

SDL_Surface* Global::gKeyPressSurfaces[];


int main(int argc, char* args[])
{
	if (!SDLWRP::Initialize())
	{
		return ExitCode::FAILED;
	}

	if (!SDLWRP::LoadMedia())
	{
		return ExitCode::FAILED;
	}

	// GAME LOOP
	while (Global::gIsRunning)
	{
		while (SDL_PollEvent(&Global::gEvent) != 0)			// Long as there is something in the event queue
		{
			if (Global::gEvent.type == SDL_QUIT)			// Was the event a quit event?
			{
				Global::gIsRunning = false;
			}
			// User presses a key
			else if (Global::gEvent.type == SDL_KEYDOWN)
			{
				// load surface based on the key pressed
				switch (Global::gEvent.key.keysym.sym)
				{
				case SDLK_UP:
					Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
					break;

				case SDLK_DOWN:
					Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
					break;

				case SDLK_LEFT:
					Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
					break;

				case SDLK_RIGHT:
					Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
					break;

				default:
					Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
					break;
				}
			}

			else if (Global::gEvent.type == SDL_KEYUP)
			{
				Global::gLiveSurface = Global::gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			}
		}


		// // Fill the surface white
		// SDL_FillRect(Global::gScreenSurface, NULL, SDL_MapRGB(Global::gScreenSurface->format, 0x00, 0x00, 0x00));

		SDL_BlitSurface(Global::gLiveSurface, NULL, Global::gScreenSurface, NULL);

		// Update thhe surface
		SDL_UpdateWindowSurface(Global::gMainWindow);
	}

	// no need to Wait, game is running long as no quit event triggered
	// SDL_Delay(TIME_DELAY);
	SDLWRP::ShutDown();
	return ExitCode::SUCCESS;
}