#ifndef __GameObject_h__
#define __GameObject_h__

#include <list>
#include <vector>

#include "assert.h"
#include "Globals.h"

#include "IMGUI\imgui.h"

#include "MathGeoLib.h"
/*
#include "Math\float4x4.h"
#include "Geometry\AABB.h"
*/

#include "assimp\matrix4x4.h"


class Component;
class ComponentTransform;

enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(const char* goName, const aiMatrix4x4& transform, const char* fileLocation);
	GameObject(const char* goName, const aiMatrix4x4& transform, GameObject* goParent, const char* fileLocation);
	GameObject(const GameObject& duplicateGameObject);
	~GameObject();

	void					Update();
	void					Draw() const;
	void					CleanUp();
	void					DrawProperties();
	void					DrawHierarchy(GameObject* goSelected);
	void					DrawBBox() const;
	void					RemoveComponent(Component* component);
	void					ModelTransform(unsigned shader) const;

	AABB					ComputeBBox() const;

	std::string				GetFileFolder() const;

	math::float4x4			GetLocalTransform() const;
	math::float4x4			GetGlobalTransform() const;


public:
	Component*				AddComponent(ComponentType type);
	Component*				GetComponent(ComponentType type) const;

	std::vector<Component*> GetComponents(ComponentType type) const;

public:
	bool					enabled			= true;
	bool					drawGOBBox		= false;
	bool					drawChildsBBox	= false;
	bool					duplicating		= false;
	bool					toBeDeleted		= false;
	bool					toBeCopied		= false;
	bool					moveGOUp		= false;
	bool					moveGODown		= false;

public:
	const char*				filePath		= nullptr;
	const char*				name			= DEFAULT_GO_NAME;

	GameObject*				parent			= nullptr;
	
	std::vector<Component*>	components;
	std::list<GameObject*>	goChilds;

	ComponentTransform*		transform		= nullptr;

public:
	AABB&					bbox			= AABB();

};

#endif // __GameObject_h__