#include "Character.h"

Character::Character()
{
}

Character::Character(std::string name, int hp, int wspeed, int rspeed) /* :spriteSheet(fw, fh)*/
{
	this->Name = name;
	this->healthPoints = hp;
	this->walkSpeed = wspeed;
	this->runSpeed = rspeed;
}
//
//bool Character::LoadTexturesFromFile(const std::string* textureFiles, int count)
//{
//	bool isSuccess = true;
//
//	// Make sure the array passed in doesn't contain more files than poses (idle, walk, etc)
//	if (count > SpriteSheet_Animation::count)
//	{
//		printf("More textures are being loaded for %s than there are poses. %n poses as of this writting", this->Name, SpriteSheet_Animation::count);
//		return false;
//	}
//
//	for (size_t i = 0; i < count; i++)
//	{
//		isSuccess &= this->spriteSheet.textures[i].LoadFromFile(textureFiles[i]);
//	}
//
//	return isSuccess;
//}
//

//Load Textures and setup animation frames
void Character::LoadAllFrames(std::string file)
{
	this->spriteSheet.LoadFromFile(file);
	this->spriteSheet.SetFrameDimensions(133, 126);

	this->LoadIdleFrames(8);

	this->LoadRunFrames(8);
	this->LoadAttackFrames(9);
}

void Character::LoadIdleFrames(int frameCount)
{
	return this->spriteSheet.LoadIdleFrames(frameCount);
}

void Character::LoadWalkFrames(int frameCount)
{
	return this->spriteSheet.LoadWalkFrames(frameCount);
}

void Character::LoadRunFrames(int frameCount)
{
	return this->spriteSheet.LoadRunFrames(frameCount);
}

void Character::LoadAttackFrames(int frameCount)
{
	return this->spriteSheet.LoadAttackFrames(frameCount);
}

int Character::GetRunSpeed()
{
	return this->runSpeed;
}

Direction Character::GetDirection()
{
	return this->spriteSheet.direction;
}

SpriteSheet_Animation Character::GetCurrentAnimation()
{
	return this->spriteSheet.getCurrentAnimation();
}

void Character::SetRenderer(SDL_Renderer* renderer)
{
	this->spriteSheet.SetRenderer(renderer);
}

void Character::SetDirection(Direction dir)
{
	this->spriteSheet.direction = dir;

	switch (dir)
	{
	case Direction::RIGHT:
		this->spriteSheet.flip = SDL_FLIP_NONE;

		if (walkSpeed < 0)
		{
			walkSpeed = -walkSpeed;
			runSpeed = -runSpeed;
		}
		break;

	case Direction::LEFT:
		this->spriteSheet.flip = SDL_FLIP_HORIZONTAL;
		if (walkSpeed >= 0)
		{
			walkSpeed = -walkSpeed;
			runSpeed = -runSpeed;
		}
		break;
	}
}

void Character::SetScale(float scale)
{
	this->spriteSheet.SetScale(scale);
}

void Character::Stand()
{
	this->spriteSheet.RenderNextIdleFrame(this->XPosition, this->YPosition);
}

void Character::Walk()
{
	if (XPosition >= 0 && XPosition <= SCREEN_WIDTH)
	{
		this->spriteSheet.RenderNextWalkFrame(this->XPosition, this->YPosition, this->walkSpeed, this->runSpeed);
	}
	if (XPosition < 0)
	{
		XPosition = SCREEN_WIDTH;
	}
	if (XPosition > SCREEN_WIDTH)
	{
		XPosition = 0;
	}
}

void Character::Run()
{
	if (XPosition >= 0 && XPosition <= SCREEN_WIDTH)
	{
		this->spriteSheet.RenderNextRunFrame(this->XPosition, this->YPosition, this->runSpeed);
	}
	if (XPosition < 0)
	{
		XPosition = 0;
	}
	if (XPosition > SCREEN_WIDTH)
	{
		XPosition = SCREEN_WIDTH;
	}
}

void Character::Attack()
{
	this->spriteSheet.RenderNextAttackFrame(this->XPosition, this->YPosition);
}