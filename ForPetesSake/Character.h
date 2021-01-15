#pragma once
#include "Entity.h"
#include "SpriteSheet.h"

// All characters are moving entities and must support the following animations:
// - Idle animation
// - Walk animation
// - Talk animation
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
	int walkSpeed;
	int runSpeed;
	int attackSpeed;

public:
	Character();
	Character(std::string name, int hp, int wspeed, int rspeed);

	void LoadAllFrames(std::string file);

	void LoadIdleFrames(int frameCount);
	void LoadWalkFrames(int frameCount);
	void LoadRunFrames(int frameCount);
	void LoadAttackFrames(int frameCount);

	int GetRunSpeed();
	Direction GetDirection();
	SpriteSheet_Animation GetCurrentAnimation();

	void SetFrame(int frameNumber);

	void SetRenderer(SDL_Renderer*) override;

	void Stand();
	void Walk();
	void Run();
	void Attack();

	void SetDirection(Direction direction);
	void SetScale(float scale);
};