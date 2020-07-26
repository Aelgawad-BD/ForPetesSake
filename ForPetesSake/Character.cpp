#include "Character.h"

Character::Character() :spriteSheet(63, 100)
{

}

Character::Character(int fw, int fh, std::string name, int hp, int sspeed, int bspeed) : spriteSheet(fw, fh)
{
	this->Name = name;
	this->healthPoints = hp;
	this->stepSpeed = sspeed;
	this->baseSpeed = bspeed;
}

bool Character::LoadTextureFromFile(const std::string file)
{
	return this->spriteSheet.LoadFromFile(file) && this->texture.LoadFromFile(file);
}

void Character::SetRenderer(SDL_Renderer* renderer)
{
	this->spriteSheet.SetRenderer(renderer);
	this->texture.SetRenderer(renderer);
}

void Character::SetDirection(Direction dir)
{
	this->spriteSheet.direction = dir;


	switch (dir)
	{
	case Direction::RIGHT:
		this->spriteSheet.flip = SDL_FLIP_NONE;

		if (stepSpeed < 0)
		{
			stepSpeed = -stepSpeed;
			baseSpeed = -baseSpeed;
		}
		break;

	case Direction::LEFT:
		this->spriteSheet.flip = SDL_FLIP_HORIZONTAL;
		if (stepSpeed >= 0)
		{
			stepSpeed = -stepSpeed;
			baseSpeed = -baseSpeed;
		}
		break;
	}
}

void Character::Walk()
{
	if (XPosition >= 0 && XPosition <= SCREEN_WIDTH)
	{
		this->spriteSheet.RenderNextWalkFrame(this->XPosition, this->YPosition, this->stepSpeed, this->baseSpeed);
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