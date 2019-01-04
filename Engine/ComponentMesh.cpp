#include "ComponentMesh.h"

// Constructor
ComponentMesh::ComponentMesh(GameObject* goContainer) : Component(goContainer, ComponentType::MESH)
{
}

// Destructor
ComponentMesh::~ComponentMesh()
{
}
