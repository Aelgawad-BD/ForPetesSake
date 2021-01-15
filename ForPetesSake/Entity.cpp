#include "Entity.h"

Entity::Entity()
{
	// init texture object
}

Entity::~Entity()
{
	this->texture.Free();
}

void Entity::Free()
{
	this->texture.Free();
}

void Entity::SetRenderer(SDL_Renderer* renderer)
{
	this->texture.SetRenderer(renderer);
}

void Entity::SetPosition(int posX, int posY)
{
	this->XPosition = posX;
	this->YPosition = posY;
}

void Entity::SetScale(float scale)
{
	this->texture.SetScale(scale);
}

void Entity::SetBlendMode(SDL_BlendMode blendMode)
{
	this->texture.SetBlendMode(blendMode);
}

bool Entity::IsAnimate()
{
	return this->isAnimate;
}

int Entity::GetXPos()
{
	return this->XPosition;
}

int Entity::GetYPos()
{
	return this->YPosition;
}

int Entity::GetWidth()
{
	return this->texture.GetFileWidth();
}

int Entity::GetHeight()
{
	return this->texture.GetFileHeight();
}

int Entity::GetScaledWidth()
{
	return this->texture.GetFileWidth() * this->texture.GetScale();
}

int Entity::GetScaledHeight()
{
	return this->texture.GetFileHeight() * this->texture.GetScale();
}

bool Entity::LoadTextureFromFile(const std::string file)
{
	return this->texture.LoadFromFile(file);
}

void Entity::Draw(SDL_Rect* sdlRect)
{
	// Todo: Set all arguments on this call, some are set here and some are set in the "called" function! Either do it all here or all there!
	this->texture.Render(this->XPosition, this->YPosition, sdlRect);
}