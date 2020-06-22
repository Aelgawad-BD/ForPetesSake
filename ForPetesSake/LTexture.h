#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

class LTexture
{
public:
	LTexture(bool spriteSheet = false);
	LTexture(SDL_Renderer* renderer, bool spriteSheet = false);
	~LTexture();
	bool LoadFromFile(const std::string);
	void Free();
	void loadFrames(int startFrame, int endFrame, int frameWidth, int frameHeight);
	// void loadWalkFrames(int startFrame, int endFrame, int frameWidth, int frameHeight);
	// void loadIdleFrames(int startFrame, int endFrame, int frameWidth, int frameHeight);
	void Render(int x, int y, SDL_Rect* clip);
	void RenderNextWalkFrame(int posX, int posY);
	void RenderNextIdleFrame(int posX, int posY);
	

	SDL_Rect* SpliceSpriteSheet(int startFrame, int endFrame, int noOfFrames);


	// Getters
	int GetWidth();
	int GetHeight();
	bool IsSpriteSheet();

	// Settters
	void SetRenderer(SDL_Renderer* renderer);
	void SetIsSpriteSheet(bool spriteShhet);
	// Properties Setters
	void SetColor(Uint8 red, Uint8 green, Uint8 blue);
	void SetBlendMode(SDL_BlendMode blending);
	void SetAlpha(Uint8 alpha);

private:
	// The actual hardware texture
	//  this is what we are wrapping
	SDL_Texture* texture;

	// keep a copy of the SDL_Renderer pointer with the object
	//  so that the render method is self sufficient
	SDL_Renderer* renderer;

	// Image Dimensions
	int width;
	int height;

	// Indicates if the file is a sprite sheet
	bool isSpriteSheet;

	// the following applies only if isSpriteSheet is true
	// the following constitutes an array, 
	//		the pointer to the first element and how many elements are there
	int numberOfFrames = 0;
	SDL_Rect* spriteFrames = NULL;
	int currentFrame = 0;
	// enum pose is it in .standing .idle .walking .running .fighting .getting hit .dying state
};

// you should create a new class SpriteSheet that inherits from texture