#include "ComponentTransform.h"

// Constructor
ComponentTransform::ComponentTransform(GameObject* goContainer, const aiMatrix4x4& transform) : Component(goContainer, ComponentType::TRANSFORM) 
{
	AddTransform(transform);
}

// Destructor
ComponentTransform::~ComponentTransform() { }

void ComponentTransform::AddTransform(const aiMatrix4x4 & transform) 
{
	aiVector3D translation;
	aiVector3D scaling;
	aiQuaternion airotation;
	transform.Decompose(scaling, airotation, translation);

	position = { translation.x, translation.y, translation.z };
	scale = { scaling.x, scaling.y, scaling.z };
	rotation = Quat(airotation.x, airotation.y, airotation.z, airotation.w);
	RotationToEuler();
}

void ComponentTransform::SetRotation(const Quat & rot) 
{
	rotation = rot;
	RotationToEuler();
}

void ComponentTransform::RotationToEuler() 
{
	eulerRotation = rotation.ToEulerXYZ();
	eulerRotation.x = math::RadToDeg(eulerRotation.x);
	eulerRotation.y = math::RadToDeg(eulerRotation.y);
	eulerRotation.z = math::RadToDeg(eulerRotation.z);
}

void ComponentTransform::SetPosition(const float3 & pos) 
{
	position = pos;
}