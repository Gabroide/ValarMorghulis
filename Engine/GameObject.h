#ifndef __GameObject_h__
#define __GameObject_h__

#include <vector>

#include "Globals.h"
#include "Component.h"

class Component;

class GameObject
{
public:
	GameObject();
	~GameObject();

public:
	std::vector<Component*>		components;
	std::vector<GameObject*>	children;

public:
	const char* name	= nullptr;
	GameObject* parent	= nullptr;

};

#endif // __GameObject_h__