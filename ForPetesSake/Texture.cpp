#include "Texture.h"


// Constructors & Destructors
Texture::Texture()
{
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	this->scale = 1.0f;
	this->renderer = NULL;
}

Texture::Texture(SDL_Renderer* renderer)
{
	this->texture = NULL;
	this->width = 0;
	this->height = 0;
	this->renderer = renderer;
}

Texture::~Texture()
{
	Free();
}



// Core Functionality
bool Texture::LoadFromFile(const std::string path)
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
	return this->texture != NULL;
}

//  TDL_RenderCopyakes in the X & Y positions where sprite is rendered as well as the part (clip) 
//		of the sprite sheet to be rendered
void Texture::Render(int posX, int posY, SDL_Rect* clip)
{
	// Set rendering space and render to screen
	SDL_Rect renderQuad = { posX, posY, (this->width) * this->scale, (this->height) * this->scale };

	// Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Render to screen
	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

//// EXPIRMENTAL
//void Texture::RenderFadeIn(int posX, int posY, SDL_Rect* clip)
//{
//	// Set rendering space and render to screen
//	SDL_Rect renderQuad = { posX, posY, (this->width) * this->scale, (this->height) * this->scale };
//
//	// Set clip rendering dimensions
//	if (clip != NULL)
//	{
//		renderQuad.w = clip->w;
//		renderQuad.w = clip->w;
//		renderQuad.h = clip->h;
//	}
//
//	// Render to screen
//	SDL_RenderCopy(renderer, texture, clip, &renderQuad);
//}

void Texture::Free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		this->texture = NULL;
		this->width = 0;
		this->height = 0;
	}
}



// Getters
int Texture::GetFileWidth()
{
	return this->width;
}

int Texture::GetFileHeight()
{
	return this->height;
}

float Texture::GetScale()
{
	return this->scale;
}

SDL_Renderer* Texture::GetRenderer()
{
	return this->renderer;
}

SDL_Texture* Texture::GetTexture()
{
	return this->texture;
}



// Setters
void Texture::SetRenderer(SDL_Renderer* argRenderer)
{
	this->renderer = argRenderer;
}

void Texture::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
	// Modulate texture
	SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
	// Set blending function
	SDL_SetTextureBlendMode(this->texture, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(this->texture, alpha);
}

void Texture::SetScale(float scale)
{
	// Stretch image
	this->scale = scale;
}
