#pragma once
#include "Texture.h"

/*
	SpriteSheet handles all animations even if they are (and they are) spread out over more than one sprite sheet
	all you need is a single object for each Entity
*/

class SpriteSheet : public Texture
{
private:
	// Idle animation
	SDL_Rect* idleFrames;
	int numberOfIdleFrames;

	// Walking animation array
	SDL_Rect* walkFrames;
	int numberOfWalkFrames;

	// Running animation array
	SDL_Rect* runFrames;
	int numberOfRunFrames;

	// Attack animation array
	SDL_Rect* attackFrames;
	int numberOfAttackFrames;

	int currentFrame;
	SpriteSheet_Animation currentAnimation = IDLE;

	int idleAnimationDelay = 100;
	int walkAnimationDelay = 60;
	int attackAnimationDelay = 90;
	int runAnimationDelay = 60;		// Trial n Error (... and that's a magic number)

	// holds all the resource files (spritesheets in order)
	std::string spriteSheetFile;

	// All animation frames should have the same dimmensions
	int frameWidth;
	int frameHeight;

public:

	// indicates if the character is going right to left
	Direction direction;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	// CONSTRUCTOR
	SpriteSheet();

	// DESTRUCTOR
	~SpriteSheet();

	// GETTERS
	SpriteSheet_Animation getCurrentAnimation();
	int GetIdleFramesCount();
	int GetWalkFramesCount();
	int GetRunFramesCount();
	// ...

	// Setters
	void SetFrameDimensions(int fw, int fh);
	void SetCurrentFrame(int frameNumber);

	// Populate the arrays walkFrames, runFrames, idleFrames with SDL_Rect s
	void LoadIdleFrames(int frameCount);
	void LoadWalkFrames(int frameCount);
	void LoadRunFrames(int frameCount);
	void LoadAttackFrames(int frameCount);
	// ...

	// Display the next frame in the animation
	void RenderNextIdleFrame(int& poX, int& posY);
	void RenderNextWalkFrame(int& poX, int& posY, int stepSpeed, int baseSpeed);
	void RenderNextRunFrame(int& poX, int& posY, int stepspeed);
	void RenderNextAttackFrame(int& poX, int& posY);
	void RenderAttackFrames(int& poX, int& posY);
	// ...
};

