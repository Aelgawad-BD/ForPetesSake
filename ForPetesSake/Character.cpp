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

void Character::Walk(Direction dir)
{
	this->spriteSheet.direction = dir;

	if (XPosition >= 0 && XPosition <= SCREEN_WIDTH)
	{
		this->spriteSheet.RenderNextWalkFrame(this->XPosition, this->YPosition, this->stepSpeed, this->baseSpeed);
	}
	else
	{
		XPosition = 0;
	}
}