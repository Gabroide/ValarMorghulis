#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include <list>

#include "Module.h"
#include "GameObject.h"

#include "Assimp\matrix4x4.h"

class GameObject;

enum class ComponentType;

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
	GameObject*		CreateGameObject(const char* goName, GameObject* goParent, const aiMatrix4x4& transform, const char* fileLocation);
	GameObject*		duplicateGO(GameObject* goToDuplicate);

public:
	GameObject*		root		= nullptr;
	GameObject*		goSelected	= nullptr;

};

#endif // __ModuleScene_h__
