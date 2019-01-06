#ifndef __GameObject_h__
#define __GameObject_h__

#include <list>
#include <vector>

#include "assert.h"
#include "Globals.h"

#include "IMGUI\imgui.h"

#include "MathGeoLib.h"
/*
"Math/float4x4.h"
"Geometry/AABB.h"
*/

#include "assimp/matrix4x4.h"

class Component;
class ComponentTransform;
enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(const std::string goName, const aiMatrix4x4& transform, const char* fileLocation);
	GameObject(const std::string goName, const aiMatrix4x4& transform, GameObject* goParent, const char* fileLocation);
	~GameObject();

	void					Update();
	void					Draw();
	void					DrawHierarchy(GameObject* goSelected);
	void					RemoveComponent(Component* component);
	void					ModelTransform(unsigned shader) const;

	AABB&					ComputeBBox() const;

	std::string				GetFileFolder() const;
	std::vector<Component*> GetComponents(ComponentType type) const;
	
	math::float4x4			GetLocalTransform() const;
	math::float4x4			GetGlobalTransform() const;

public:
	Component*				AddComponent(ComponentType type);
	Component*				GetComponent(ComponentType type) const;

public:
	AABB&					bbox;

	std::string				name		= "GameObject";

public:
	const char*				filePath	= nullptr;

	ComponentTransform*		transform	= nullptr;

	GameObject*				parent		= nullptr;
	
	std::vector<Component*>	components;
	std::list<GameObject*>	goChilds;

};

#endif // __GameObject_h__