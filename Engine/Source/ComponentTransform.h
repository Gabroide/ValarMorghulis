#ifndef __ComponentTransform_h__
#define __ComponentTransform_h__

#include "Component.h"

#include "MathGeoLib\include\Math\MathFunc.h"
#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Math\Quat.h"

#include "IMGUI\imgui.h"

#include "Assimp\scene.h""

class ComponentTransform : public Component
{
	public:
		ComponentTransform(GameObject* goContainer, const math::float4x4& transform);
		ComponentTransform(const ComponentTransform& duplicatedTransform);
		~ComponentTransform();

		void			AddTransform(const math::float4x4& transform);
		void			SetRotation(const math::Quat& rot);
		void			SetPosition(const math::float3& pos);
		void			RotationToEuler();
		void			SetLocalToWorld(const math::float4x4& localTrans);
		void			SetWorldToLocal(const math::float4x4& parentTrans);
		void			DrawProperties() override;
		
	public:
		Component*		Duplicate() override;

	public:
		bool			edited			= false;

		math::float3	position		= math::float3::zero;
		math::float3	eulerRotation	= math::float3::zero;
		math::float3	scale			= math::float3::zero;

		math::Quat		rotation = math::Quat::identity;

};

#endif // __ComponentTransform_h__
