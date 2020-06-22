#include "LTexture.h"

LTexture::LTexture(bool spriteSheet)
{
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	this->isSpriteSheet = spriteSheet;
	this->renderer = NULL;
}

LTexture::LTexture(SDL_Renderer* renderer, bool spriteSheet)
{
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	this->renderer = renderer;
	this->isSpriteSheet = spriteSheet;
}

LTexture::~LTexture()
{
	Free();
}

bool LTexture::LoadFromFile(const std::string path)
{
	// Get rid of previous texture
	Free();

	// final texture
	SDL_Texture* newTexture = NULL;

	// Load specified image
	SDL_Surface* loadedSurface = NULL;
	loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image from %s. SDL Error %s", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(this->renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s in function <%s>. SDL Error %s", path.c_str(), "<bool LTexture::LoadFromFile(const std::string path)>", SDL_GetError());
		}
		this->width = loadedSurface->w;
		this->height = loadedSurface->h;
	}

	this->texture = newTexture;

	// if it is a sprite sheet, splice it and store on heap ready to go
	if (this->isSpriteSheet)
	{
		// create an array on the heap
		loadFrames(0, 5, 80, 110);
	}

	return this->texture != NULL;
}

void LTexture::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		this->texture = NULL;
		this->width = 0;
		this->height = 0;
	}

	if (this->spriteFrames != NULL)
	{
		delete spriteFrames;
	}
}


// TODO: Need to make this generic
//  takes in the X & Y positions where sprite is rendered as well as the part (clip) 
//  of the sprite sheet to be rendered
void LTexture::Render(int posX, int posY, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->width, this->height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

// TODO: Need to make this generic
//  takes in the X & Y positions where sprite is rendered as well as the part (clip) 
//  of the sprite sheet to be rendered
void LTexture::RenderNextWalkFrame(int posX, int posY)
{
	SDL_Delay(150);
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, this->spriteFrames[this->currentFrame].w, this->spriteFrames[this->currentFrame].h};

	// Render to screen
	SDL_RenderCopy(renderer, texture, this->spriteFrames + currentFrame, &renderQuad);

	this->currentFrame++;

	if (this->currentFrame > 5)
	{
		currentFrame = 0;
	}
}

void LTexture::RenderNextIdleFrame(int posX, int posY)
{

}

// The purpose of the function is to supply the RenderClip with SDL_Rects
//  sliced from a sprite sheet. Frames are 0 based index
void LTexture::loadFrames(int startFrame, int endFrame, int frameWidth, int frameHeight)
{
	// NOTE: The following implementation is NOT geeric and has magic numbers
	//       specific for the current sprite sheet, developer discretion is advised

	if (startFrame > endFrame)
	{
		printf("Animation Start frame %n is higher than End Frame %n", startFrame, endFrame);
		return;
	}

	// Get number of frames
	this->numberOfFrames = endFrame - startFrame + 1;

	SDL_Rect* frameRects = new SDL_Rect[this->numberOfFrames];

	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGH = 110;

	for (int i = startFrame; i <= endFrame; i++)
	{
		frameRects[i].x = i * FRAME_WIDTH;
		frameRects[i].y = 0;
		frameRects[i].w = FRAME_WIDTH;
		frameRects[i].h = FRAME_HEIGH;
	}
	this->spriteFrames = frameRects;
}

void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(this->texture, blending);
}

void LTexture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(this->texture, alpha);
}
// Getters
int LTexture::GetWidth()
{
	return this->width;
}

int LTexture::GetHeight()
{
	return this->height;
}

bool LTexture::IsSpriteSheet()
{
	return this->isSpriteSheet;
}

// Setters
void LTexture::SetRenderer(SDL_Renderer* argRenderer)
{
	this->renderer = argRenderer;
}

void LTexture::SetIsSpriteSheet(bool setIsSptriteSheet)
{
	this->isSpriteSheet = setIsSptriteSheet;
}