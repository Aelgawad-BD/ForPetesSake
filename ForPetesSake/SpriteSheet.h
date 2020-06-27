#pragma once
#include "Texture.h"


class SpriteSheet : public Texture
{
private:
	// Walking animation
	SDL_Rect* walkFrames;
	int numberOfWalkFrames;

	// Running animation
	SDL_Rect* runFrames;
	int numberOfRunFrames;

	// Idle animation
	SDL_Rect* idleFrames = NULL;
	int numberOfIdleFrames;

	int frameWidth;
	int frameHeight;

	int currentFrame;
	SpriteSheet_Animation currentAnimation;
	

public:
	// bool isInverted = false;	// indicates if the character is going right to left
	Direction direction;

	// CONSTRUCTORS
	//SpriteSheet(); // but you HAVE to provide frame width and height
	SpriteSheet(int frameWidth, int frameHeight);

	// Destructor
	~SpriteSheet();
	void Free() override;

	// Setters
	void SetFrameDimensions(int fw, int fh);

	// Populate the arrays walkFrames, runFrames, idleFrames with SDL_Rect s
	void LoadWalkingFrames(int startFrame, int endFrame);
	void LoadRunningFrames(int startFrame, int endFrame);
	void LoadIdleFrames(int startFrame, int endFrame);
	// ...

	// Display the next frame in the animation
	void RenderNextWalkFrame(int& poX, int& posY, int stepSpeed, int baseSpeed);
	void RenderNextRunningFrame(int poX, int posY);
	void RenderNextIdleFrame(int poX, int posY);
	// ...
};

