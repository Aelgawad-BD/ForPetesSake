#include "Environment.h"

Game::Game() :mainCharacter("Jeager Meister", 100, 30, 30)
{
	Camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
}

bool Game::OpenScene()
{
	// Set Positions
	background.SetPosition(0, 0);
	mainCharacter.SetPosition(30, 509);

	// Set Scales
	mainCharacter.SetScale(1.5f);

	this->mainCharacter.LoadAllFrames(spriteSheet_jeagermeister_png);

	// Load background texture
	if (!this->background.LoadTextureFromFile(img_level_png))
	{
		printf("Failed to load background texture image!\n");
		return false;
	}
	return true;
}

void Game::CloseScene()
{
	this->background.Free();
	this->mainCharacter.Free();
}

void Game::Draw()
{
	// This Works BUT:
	// It would be a nightmare adding another single character to the scene, let alone more than one
	//  the way I see it, there should be LOGICAL and ACTUAL positions.
	// LOGICAL positions are ones related to the background texture
	// ACTUAL positions are ones relating to the SDL Window


	if (mainCharacter.GetCurrentAnimation() == SpriteSheet_Animation::RUN) {
		// If character is at mid-screen
		if (mainCharacter.GetXPos() < (SCREEN_WIDTH / 2) + MARGIN
			&&
			mainCharacter.GetXPos() > (SCREEN_WIDTH / 2) - MARGIN)
		{
			// is there more background to the right??
			if (Camera.x + Camera.w <= background.GetWidth() && mainCharacter.GetDirection() == Direction::RIGHT)
			{
				// Char in mid-screen and Camera HAS NOT yet scrolled all the way to the right end
				mainCharacter.SetPosition(SCREEN_WIDTH / 2, mainCharacter.GetYPos());
				Camera.x += mainCharacter.GetRunSpeed();

			}
			else if (Camera.x > 0 && mainCharacter.GetDirection() == Direction::LEFT)
			{
				mainCharacter.SetPosition(SCREEN_WIDTH / 2, mainCharacter.GetYPos());
				Camera.x += mainCharacter.GetRunSpeed();
			}

		}
	}


	background.Draw(&Camera);
}


Game::~Game()
{

}