#include "SDLWrapper.h";
#include "configurations.h";

using namespace std;


int main(int argc, char* args[])
{
	SDLWRP GodInstance;
	// Game Loop After lesson 10
	//  Whilst application is running
	while (GodInstance.gIsRunning)
	{
		//Handle events on queue
		while (SDL_PollEvent(&GodInstance.gEvent) != 0)
		{
			//User requests quit
			if (GodInstance.gEvent.type == SDL_QUIT)
			{
				GodInstance.gIsRunning = false;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(GodInstance.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(GodInstance.gRenderer);

		//Render background texture to screen
		GodInstance.gBackgroundTexture.Render(0, 0, NULL);
		
		GodInstance.gCharacterTexture.RenderNextWalkFrame(30, 390);
		// GodInstance.gCharacterTexture.RenderAnimation(240, 190);



		//Update screen
		SDL_RenderPresent(GodInstance.gRenderer);
	}

	// no need to Wait, game is running long as no quit event triggered

	GodInstance.ShutDown();

	return ExitCode::SUCCESS;
}