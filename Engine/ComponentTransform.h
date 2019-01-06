#ifndef __ComponentTransform_h__
#define __ComponentTransform_h__

#include "Component.h"

#include "MathBuildConfig.h"
/*
#include "Math/MathFunc.h"
#include "Math/float4x4.h"
#include "Math/Quat.h"
*/

#include "IMGUI\imgui.h"

#include "assimp\scene.h" 

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* goContainer, const aiMatrix4x4& transform);
	ComponentTransform(ComponentTransform* duplicatedTransform);
	~ComponentTransform();

	void			DrawProperties() override;
	void			AddTransform(const aiMatrix4x4& transform);
	void			SetRotation(const math::Quat& rot);
	void			SetPosition(const float3& pos);
	void			RotationToEuler();

public:
	math::float3	position		= math::float3::zero;
	math::float3	eulerRotation	= math::float3::zero;
	math::float3	scale			= math::float3::zero;
	math::Quat		rotation		= math::Quat::identity;

};

#endif // __ComponentTransform_h__