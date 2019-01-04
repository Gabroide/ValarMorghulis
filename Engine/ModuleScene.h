#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Module.h"
#include "GameObject.h"

class GameObject;

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	GameObject* CreateGameObject(const char* goName);

public:
	GameObject* root = nullptr;

};

#endif // __ModuleScene_h__
