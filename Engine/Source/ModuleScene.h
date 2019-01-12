#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Module.h"
#include "GameObject.h"

#include "MathGeoLib\include\Math\float4.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Math/Quat.h"

enym class GeometryType {
	SPHERE = 0,
	TORUS,
	PLANE,
	CUBE
};

class ModuleScene : public Module
{
	public:
		ModuleScene();
		~ModuleScene();

		bool			Init()		override;

		update_status	Update()	override;
		
		void			Draw(const math::Frustum& frustum) const;
		void			DrawHierarchy();
		void			LoadGeometry(GameObject* goParent, GeometryType geometryType);

	public:
		GameObject*		CreateGameObject(const char* goName = nullptr, GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity, const char* fileLocation = nullptr);
		GameObject*		CreateCamera(GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity);
		
	public:
		float			ambientLight	= 0.3f;

		math::float3	lightPosition	= math::float3(0.0f, 10.0f, 10.0f);

	public:
		GameObject*		root			= nullptr;
		GameObject*		goSelected		= nullptr;

};

#endif // __ModuleScene_h__
