#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include <list>

#include "Module.h"
#include "GameObject.h"

#include "assimp\matrix4x4.h"

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
	GameObject*		CreateGameObject(const char* goName = nullptr, GameObject* goParent = nullptr, const aiMatrix4x4& transform = aiMatrix4x4(), const char* fileLocation = nullptr);

public:
	GameObject*		root		= nullptr;
	GameObject*		goSelected	= nullptr;

};

#endif // __ModuleScene_h__