#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "configurations.h" // TO-TEST: IS THAT SAFE?? 

class Texture
{
public:
	Texture();
	Texture(SDL_Renderer* renderer);
	~Texture();

	// Core Functionality
	bool LoadFromFile(const std::string);
	void Render(int x, int y, SDL_Rect* clip);
	virtual void Free();

	// Getters
	int GetFileWidth();
	int GetFileHeight();
	float GetScale();
	SDL_Renderer* GetRenderer();
	SDL_Texture* GetTexture();

	// Settters
	void SetRenderer(SDL_Renderer* renderer);

	// Property Setters
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);
	void SetScale(float scale);

protected:
	// The actual hardware texture
	//	this is what we are wrapping
	SDL_Texture* texture;

	// Keep a copy of the SDL_Renderer pointer with the object
	//  so that the render method is self sufficient
	SDL_Renderer* renderer;

	// Image File Dimensions
	int width;
	int height;

	// Scale applied to both L and W
	float scale = 1.0f;
};