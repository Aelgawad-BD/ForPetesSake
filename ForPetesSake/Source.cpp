#include "SDLWrapper.h";
#include "configurations.h";

using namespace std;

int main(int argc, char* args[])
{
	SDLWRP sdlGodInstance;

	// Clear screen
	SDL_SetRenderDrawColor(sdlGodInstance.gRenderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(sdlGodInstance.gRenderer);

	// Game Loop
	//  Whilst application is running
	while (sdlGodInstance.gIsRunning)
	{
		// Handle events on queue
		while (SDL_PollEvent(&sdlGodInstance.gEvent) != 0)
		{
			//User requests quit
			if (sdlGodInstance.gEvent.type == SDL_QUIT)
			{
				sdlGodInstance.gIsRunning = false;
			}
		}

		// Clear screen
		SDL_SetRenderDrawColor(sdlGodInstance.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(sdlGodInstance.gRenderer);

		sdlGodInstance.gGame.Draw();

		if (sdlGodInstance.gGame.mainCharacter.GetCurrentAnimation() == SpriteSheet_Animation::ATTACK)
		{
			sdlGodInstance.gGame.mainCharacter.Attack();
		}
		else {

			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
			
			if (currentKeyStates[SDL_SCANCODE_LEFT])
			{
				sdlGodInstance.gGame.mainCharacter.SetDirection(Direction::LEFT);
				sdlGodInstance.gGame.mainCharacter.Run();
			}
			else if (currentKeyStates[SDL_SCANCODE_RIGHT])
			{
				sdlGodInstance.gGame.mainCharacter.SetDirection(Direction::RIGHT);
				sdlGodInstance.gGame.mainCharacter.Run();
			}
			else if (currentKeyStates[SDL_SCANCODE_SPACE])
			{
				sdlGodInstance.gGame.mainCharacter.Attack();
			}
			else
			{
				sdlGodInstance.gGame.mainCharacter.Stand();
			}
		}
		// Update screen
		SDL_RenderPresent(sdlGodInstance.gRenderer);
		// currentFrame = 0; // on next line
		
	}

	sdlGodInstance.ShutDown();

	return ExitCode::SUCCESS;
}