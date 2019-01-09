#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include <list>

#include "Module.h"
#include "GameObject.h"

#include "MathGeoLib.h"
/*
#include "math\float4x4.h"
#include "math\float3.h"
#include "math\Quat.h"
*/

class GameObject;
enum class ComponentType;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool			Init()		override;
	void			Draw();
	void			DrawHierarchy();

	update_status	Update()	override;

public:
	GameObject*		CreateGameObject(const char* goName = nullptr, GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity, const char* fileLocation = nullptr);
	GameObject*		CreateCamera(GameObject* goParent = nullptr, const math::float4x4& transform = math::float4x4().identity);

public:
	GameObject*		root		= nullptr;
	GameObject*		goSelected	= nullptr;

};

#endif // __ModuleScene_h__