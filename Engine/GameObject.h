#ifndef __GameObject_h__
#define __GameObject_h__

#include <vector>
#include <assert.h>

#include "Globals.h"
#include "Component.h"

class Component;

class GameObject
{
public:
	GameObject(const char* goName);
	~GameObject();

	void	Update();

public:
	Component*	CreaeComponent(componentType type);

public:
	std::vector<Component*>		components;
	std::vector<GameObject*>	children;

public:
	const char* name	= nullptr;
	GameObject* parent	= nullptr;

};

#endif // __GameObject_h__