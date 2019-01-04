#include "GameObject.h"

// Constructor
GameObject::GameObject(const char* goName)
{
	assert(goName != nullptr);

	this->name = goName;
}

// Destructor
GameObject::~GameObject()
{

}

void GameOnject::Update()
{
	
}

Component* GameObject::CreateComponent(componentType type)
{
	return nullptr;
}