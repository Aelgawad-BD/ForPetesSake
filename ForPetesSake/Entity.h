#pragma once
#include <SDL.h>
#include "Texture.h"

// Anything that has an image file on the screen is an Entity
//  be it moving characters or inanimate props

class Entity
{
protected:
	int XPosition;
	int YPosition;
	Texture texture;
	bool isAnimate;

public:

	// Con-structor
	Entity();
	// ~De-structor
	~Entity();
	void Free();

	// Set the renderer for the texture
	virtual void SetRenderer(SDL_Renderer*);
	void SetPosition(int X, int Y);

	// Getters
	bool IsAnimate();
	int GetXPos();
	int GetYPos();

	virtual bool LoadTextureFromFile(const std::string);
	void Draw(SDL_Rect* sdlRect);
};

