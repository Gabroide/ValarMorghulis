#ifndef __GameObject_h__
#define __GameObject_h__

#include <list>
#include <assert.h>

#include "Globals.h"

#include "IMGUI\imgui.h"

class Component;
class ComponentTransform;

enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(const char* goName, const aiMatrix4x4& transform);
	GameObject(const char* goName, const aiMatrix4x4 transform, GameObject* goParent);
	~GameObject();

	void				Update();
	void				Draw();
	void				RemoveComponent(Component* component);
	void				DrawHierarchy(GameObject* goSelected);

public:
	Component*			AddComponent(ComponentType type);
	const char*			GetFileFolder() const;

public:
	std::list<Component*> components;
	std::list<GameObject*> goChilds;

public:
	const char*			name		= nullptr;

	GameObject*			parent		= nullptr;

	ComponentTransform*	transform	= nullptr;

};

#endif // __GameObject_h__