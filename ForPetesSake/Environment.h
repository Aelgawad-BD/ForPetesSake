#pragma once
#include <vector>

#include "Character.h"

class Game
{
public:
	std::vector<Character> characters;
	Character mainCharacter;
	Entity background;
	std::vector<Entity> tiles;
	SDL_Rect Camera;

	Game();
	~Game();
	bool OpenScene();
	void CloseScene();
	void Draw();
};

