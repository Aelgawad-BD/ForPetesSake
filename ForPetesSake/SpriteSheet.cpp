#include "SpriteSheet.h"

SpriteSheet_Animation SpriteSheet::getCurrentAnimation()
{
	return this->currentAnimation;
}

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{
	Texture::~Texture();

	if (this->idleFrames != NULL)
	{
		delete idleFrames;
	}

	if (this->walkFrames != NULL)
	{
		delete walkFrames;
	}

	if (this->runFrames != NULL)
	{
		delete runFrames;
	}
}


int SpriteSheet::GetIdleFramesCount()
{
	return this->numberOfIdleFrames;
}

int SpriteSheet::GetWalkFramesCount()
{
	return this->numberOfWalkFrames;
}

int SpriteSheet::GetRunFramesCount()
{
	return this->numberOfRunFrames;
}

void SpriteSheet::SetFrameDimensions(int fw, int fh)
{
	if (fw > 0 && fh > 0)
	{
		this->frameWidth = fw;
		this->frameHeight = fh;
	}
}

void SpriteSheet::SetCurrentFrame(int frameNumber)
{
	switch (this->currentAnimation)
	{
	case SpriteSheet_Animation::IDLE:
		if (frameNumber >= 0 && frameNumber < numberOfIdleFrames)
		{
			currentFrame = frameNumber;
		}
		break;

	case SpriteSheet_Animation::RUN:
		if (frameNumber >= 0 && frameNumber < numberOfRunFrames)
		{
			currentFrame = frameNumber;
		}
	break; case SpriteSheet_Animation::ATTACK:
		if (frameNumber >= 0 && frameNumber < numberOfAttackFrames)
		{
			currentFrame = frameNumber;
		}
		break;
	}
}


// Chops up the sprite sheet into SDL_Rects and loads them in memory so they're there when needed at render time
// The purpose of the function is to supply the RenderClip with SDL_Rects
//   sliced from a sprite sheet. Frames are 0 based index

void SpriteSheet::LoadIdleFrames(int frameCount)
{
	this->numberOfIdleFrames = frameCount;

	if (numberOfIdleFrames <= 0)
	{
		printf("Idle animation has %n frames!", numberOfIdleFrames);
		return;
	}

	this->idleFrames = new SDL_Rect[numberOfIdleFrames];

	for (int i = 0; i <= numberOfIdleFrames; i++)
	{
		this->idleFrames[i].x = i * (this->frameWidth);
		this->idleFrames[i].y = SpriteSheet_Animation::IDLE * this->frameHeight;
		this->idleFrames[i].w = this->frameWidth;
		this->idleFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::LoadWalkFrames(int frameCount)
{

	this->numberOfWalkFrames = frameCount;

	if (numberOfWalkFrames <= 0)
	{
		printf("Walk animation has %n frames!", numberOfWalkFrames);
		return;
	}

	this->walkFrames = new SDL_Rect[numberOfWalkFrames];

	for (int i = 0; i <= numberOfWalkFrames; i++)
	{
		this->walkFrames[i].x = i * (this->frameWidth);
		this->walkFrames[i].y = SpriteSheet_Animation::WALK * this->frameHeight;
		this->walkFrames[i].w = this->frameWidth;
		this->walkFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::LoadRunFrames(int frameCount)
{
	this->numberOfRunFrames = frameCount;

	if (numberOfRunFrames <= 0)
	{
		printf("Run animation has %n frames!", numberOfRunFrames);
		return;
	}

	this->runFrames = new SDL_Rect[numberOfRunFrames];

	for (int i = 0; i <= numberOfRunFrames; i++)
	{
		this->runFrames[i].x = i * (this->frameWidth);
		this->runFrames[i].y = SpriteSheet_Animation::RUN * this->frameHeight;
		this->runFrames[i].w = this->frameWidth;
		this->runFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::LoadAttackFrames(int frameCount)
{
	this->numberOfAttackFrames = frameCount;

	if (numberOfAttackFrames <= 0)
	{
		printf("Attack animation has %n frames!", numberOfAttackFrames);
		return;
	}

	this->attackFrames = new SDL_Rect[numberOfAttackFrames];

	for (int i = 0; i <= numberOfAttackFrames; i++)
	{
		this->attackFrames[i].x = i * (this->frameWidth);
		this->attackFrames[i].y = SpriteSheet_Animation::ATTACK * this->frameHeight;
		this->attackFrames[i].w = this->frameWidth;
		this->attackFrames[i].h = this->frameHeight;
	}
}

void SpriteSheet::RenderNextIdleFrame(int& posX, int& posY)
{
	this->currentAnimation = SpriteSheet_Animation::IDLE;
	SDL_Delay(this->idleAnimationDelay);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->idleFrames[this->currentFrame].w * scale, this->idleFrames[this->currentFrame].h * scale };

	// Render to screen
	SDL_RenderCopyEx(GetRenderer(),
		GetTexture(),
		this->idleFrames + currentFrame, &renderQuad, 0, NULL, this->flip);

	// Get a random frame from 0 to 7
	currentFrame = rand() % numberOfIdleFrames;

}

void SpriteSheet::RenderNextWalkFrame(int& posX, int& posY, int stepspeed, int basespeed)
{
	this->currentAnimation = SpriteSheet_Animation::WALK;
	SDL_Delay(this->walkAnimationDelay);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->walkFrames[this->currentFrame].w, this->walkFrames[this->currentFrame].h };

	// Render to screen
	SDL_RenderCopyEx(GetRenderer(), GetTexture(),
		this->walkFrames + currentFrame, &renderQuad, 0, NULL, this->flip);

	this->currentFrame++;

	if (this->currentFrame > ((this->numberOfWalkFrames) - 1)) //7
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

void SpriteSheet::RenderNextRunFrame(int& posX, int& posY, int stepspeed)
{
	float scale = GetScale();

	this->currentAnimation = SpriteSheet_Animation::RUN;
	SDL_Delay(this->runAnimationDelay);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->runFrames[this->currentFrame].w * scale, this->runFrames[this->currentFrame].h * scale };

	// Render to screen
	SDL_RenderCopyEx(GetRenderer(), GetTexture(),
		this->runFrames + currentFrame,
		&renderQuad, 0, NULL, this->flip);

	this->currentFrame++;

	if (this->currentFrame > ((this->numberOfRunFrames) - 1))
	{
		currentFrame = 0;
	}

	posX += stepspeed;
}

void SpriteSheet::RenderNextAttackFrame(int& posX, int& posY)
{
	float scale = GetScale();

	this->currentAnimation = SpriteSheet_Animation::ATTACK;
	SDL_Delay(this->attackAnimationDelay);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->attackFrames[this->currentFrame].w * scale, this->attackFrames[this->currentFrame].h * scale };

	// Render to screen
	SDL_RenderCopyEx(GetRenderer(), GetTexture(),
		this->attackFrames + currentFrame,
		&renderQuad, 0, NULL, this->flip);

	this->currentFrame++;

	if (this->currentFrame > ((this->numberOfAttackFrames) - 1))
	{
		currentFrame = 0;
		this->currentAnimation = IDLE;
	}

}

void SpriteSheet::RenderAttackFrames(int& posX, int& posY)
{
	float scale = GetScale();

	this->currentAnimation = SpriteSheet_Animation::ATTACK;

	for (size_t i = 0; i < numberOfAttackFrames; i++)
	{
		SDL_Delay(this->attackAnimationDelay);
		// Set rendering space and render to screen
		SDL_Rect renderQuad = { posX, posY, this->attackFrames[this->currentFrame].w * scale, this->attackFrames[this->currentFrame].h * scale };

		// Render to screen
		SDL_RenderCopyEx(GetRenderer(), GetTexture(),
			this->runFrames + currentFrame,
			&renderQuad, 0, NULL, this->flip);
	}
}