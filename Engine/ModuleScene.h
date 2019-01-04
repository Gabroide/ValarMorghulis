#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include <list>

#include "Module.h"
#include "GameObject.h"

class GameObject;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool			Init()		override;
	bool			CleanUp()	override;
	
	update_status	Update()	override;
	
	void			Draw();
	void			DrawHierarchy();

public:
	GameObject*		CreateGameObject(const char* goName, GameObject* goParent);

public:
	GameObject*		root		= nullptr;
	GameObject*		goSelected	= nullptr;
};

#endif // __ModuleScene_h__
