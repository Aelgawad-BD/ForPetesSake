#pragma once
#include "Entity.h"
#include "SpriteSheet.h"

// All characters are moving entities and must support the following animations:
// - Idle animation
// - Walk animation
// - Run animation
// - attack animation
// - Get Hit animation
// - Death animation

class Character : public Entity
{
private:
	SpriteSheet spriteSheet;

	std::string Name;
	int healthPoints;
	int stepSpeed;
	int baseSpeed;

public:
	Character();
	Character(int frameWidth, int frameHeight, std::string name, int hp, int sspeed, int bspeed);

	bool LoadTextureFromFile(const std::string file) override;
	void SetRenderer(SDL_Renderer*) override;
	void Walk();

	void SetDirection(Direction direction);
};