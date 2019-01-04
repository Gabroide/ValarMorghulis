#ifndef __ComponentTransform_h__
#define __ComponentTransform_h__

#include "Component.h"

#include "MathGeoLib.h"

#include "IMGUI\imgui.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* goContainer, const aiMatrix4x4 &transform);
	~ComponentTransform();

	void			AddTransform(const aiMatrix4x4 &transform);

public:
	math::float3	position		= math::float3::zero;
	math::float3	eulerRotation	= math::float3::zero;
	math::float3	scale			= math::float3::zero;

	math::Quat		rotation		= math::Quat::identity;

};

#endif // __ComponentTransform_h__