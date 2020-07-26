#include "SpriteSheet.h"


//SpriteSheet::SpriteSheet()
//{
//	LoadWalkingFrames(0, 7);
//	// loadRunningFrames(0, 7);
//	// loadIdleFrames(0, 7);
//}

SpriteSheet::SpriteSheet(int frameWidth, int frameHeight)
{
	this->frameWidth = frameWidth;
	this->frameHeight = frameHeight;
	LoadWalkingFrames(0, 7);
}

SpriteSheet::~SpriteSheet()
{
	// To-Test: Will the following call the function SpriteSheet::Free() below?
	Texture::~Texture();

	if (this->walkFrames != NULL)
	{
		delete walkFrames;
	}

	if (this->idleFrames != NULL)
	{
		delete idleFrames;
	}

	if (this->runFrames != NULL)
	{
		delete runFrames;
	}
}

void SpriteSheet::Free()
{
	Texture::Free();
}

void SpriteSheet::SetFrameDimensions(int fw, int fh)
{
	if (fw > 0 && fh > 0)
	{
		this->frameWidth = fw;
		this->frameHeight = fh;
	}
}


// Chops up the sprite sheet into SDL_Rects and loads them in memory so they're there when needed at render time
// The purpose of the function is to supply the RenderClip with SDL_Rects
//  sliced from a sprite sheet. Frames are 0 based index
void SpriteSheet::LoadWalkingFrames(int startFrame, int endFrame)
{
	// NOTE: The following implementation is NOT generic and has magic numbers
	//       specific for the current sprite sheet, developer discretion is advised

	if (startFrame > endFrame)
	{
		printf("Animation Start frame %n is higher than End Frame %n", startFrame, endFrame);
		return;
	}

	// Get number of frames
	this->numberOfWalkFrames = endFrame - startFrame + 1;

	this->walkFrames = new SDL_Rect[numberOfWalkFrames];

	// const int FRAME_WIDTH = 80;
	// const int FRAME_HEIGH = 110;
	const int FRAME_WIDTH = 63;
	const int FRAME_HEIGH = 100;

	for (int i = startFrame; i <= endFrame; i++)
	{
		this->walkFrames[i].x = i * (this->frameWidth);
		this->walkFrames[i].y = 0;
		this->walkFrames[i].w = this->frameWidth;
		this->walkFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::LoadRunningFrames(int startFrame, int endFrame)
{
	if (startFrame > endFrame)
	{
		printf("Animation Start frame %n is higher than End Frame %n", startFrame, endFrame);
		return;
	}

	// Get number of frames
	this->numberOfRunFrames = endFrame - startFrame + 1;

	this->runFrames = new SDL_Rect[numberOfRunFrames];

	// const int FRAME_WIDTH = 80;
	// const int FRAME_HEIGH = 110;
	const int FRAME_WIDTH = 63;
	const int FRAME_HEIGH = 100;

	for (int i = startFrame; i <= endFrame; i++)
	{
		this->runFrames[i].x = i * (this->frameWidth);
		this->runFrames[i].y = 0;
		this->runFrames[i].w = this->frameWidth;
		this->runFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::LoadIdleFrames(int startFrame, int endFrame)
{
	// throw new NotImplementedException();
}


void SpriteSheet::RenderNextWalkFrame(int& posX, int& posY, int stepspeed, int basespeed)
{
	SDL_Delay(ANIMATION_TIME_DELAY);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->walkFrames[this->currentFrame].w, this->walkFrames[this->currentFrame].h };

	// Render to screen
	SDL_RenderCopyEx(renderer, texture, this->walkFrames + currentFrame, &renderQuad, 0, NULL, this->flip);

	this->currentFrame++;

	if (this->currentFrame > 5)
	{
		currentFrame = 0;
	}

	if (this->currentFrame == 0 || this->currentFrame == 3)		// uh oh! Magic Numbers!
	{
		posX += stepspeed;
	}
	else
	{
		posX += basespeed;
	}
}
