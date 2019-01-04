#include "ComponentTransform.h"

// Constructor
ComponentTransform::ComponentTransform(GameObject* goContainer) : Component(goContainer, ComponentType::TRANSFORM)
{
}

// Destructor
ComponentTransform::~ComponentTransform()
{
}
