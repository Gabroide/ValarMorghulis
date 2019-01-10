#ifndef __GameObject_h__
#define __GameObject_h__

#include <list>
#include <vector>

#include "assert.h"
#include "Globals.h"

#include "IMGUI\imgui.h"

#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Geometry\AABB.h"

#include "assimp\matrix4x4.h"


class Component;
class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;

enum class ComponentType;

class GameObject
{
public:
	GameObject();
	GameObject(const char* goName, const math::float4x4& transform, const char* fileLocation);
	GameObject(const char* goName, const math::float4x4& transform, GameObject* goParent, const char* fileLocation);
	GameObject(const GameObject& duplicateGameObject);
	~GameObject();

	void					Update();
	void					Draw(const Frustum& frustum) const;
	void					CleanUp();
	void					DrawProperties();
	void					DrawHierarchy(GameObject* goSelected);
	void					DrawBBox() const;
	void					RemoveComponent(Component* component);
	void					ModelTransform(unsigned shader) const;

	AABB					ComputeBBox();

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

	std::string				uuid			= "";
	std::string				parentUuid		= "";

	math::AABB				bbox;

public:
	const char*				filePath		= nullptr;
	const char*				name			= DEFAULT_GO_NAME;

	GameObject*				parent			= nullptr;
	
	ComponentMesh*			mesh			= nullptr;

	ComponentMaterial*		material		= nullptr;

	std::list<GameObject*>	goChilds;

	std::vector<Component*>	components;

	ComponentTransform*		transform		= nullptr;

};

#endif // __GameObject_h__