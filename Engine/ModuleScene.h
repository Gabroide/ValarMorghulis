#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Module.h"
#include "GameObject.h"

#include "math\float4x4.h"
#include "math\float3.h"
#include "math\Quat.h"

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool			Init()		override;
	
	update_status	Update()	override;

	void			Draw();
	void			DrawHierarchy();

public:
	GameObject*		CreateGameObject(const char* goName = nullptr, GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity, const char* fileLocation = nullptr);
	GameObject*		CreateCamera(GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity);
	GameObject*		GenerateSphere(GameObject* goParent, int slices, int stacks, const math::float3& pos, const math::Quat& rot, const float size, const math::float4& color);
	GameObject*		GenerateTorus(GameObject* goParent, const math::float3& pos, const math::Quat& rot, float innerRadius, float outterRadius, unsigned slices, unsigned stacks, math::float4& color);

public:
	GameObject*		root		= nullptr;
	GameObject*		goSelected	= nullptr;

};

#endif // __ModuleScene_h__