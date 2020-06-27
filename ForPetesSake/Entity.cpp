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

bool Entity::LoadTextureFromFile(const std::string file)
{
	return this->texture.LoadFromFile(file);
}

void Entity::Draw(SDL_Rect* sdlRect)
{
	this->texture.Render(this->XPosition, this->YPosition, sdlRect);
}