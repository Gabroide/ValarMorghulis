#include "Component.h"

// Constructor
Component::Component(GameObject* goContainer, ComponentType type)
{
	this->goContainer = goContainer;
	this->componentType = type;
}

// Destructor
Component::~Component()
{

}

void Component::Update()
{
	
}

void Component::Remove()
{
	this->goContainer->RemoveComponent(this);
}