#ifndef __GameObject_h__
#define __GameObject_h__

#include <list>
#include <vector>

#include "assert.h"
#include "Globals.h"

#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Geometry\AABB.h"

#include "IMGUI\imgui.h"

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
		void					Draw(const math::Frustum& frustum) const;
		void					CleanUp();
		void					DrawProperties();
		void					DrawHierarchy(GameObject* goSelected);
		void					DrawBBox() const;
		void					RemoveComponent(Component* component);
		void					ComputeBBox();
		void					ModelTransform(unsigned shader) const;

		std::string				GetFileFolder() const;

		math::float4x4			GetLocalTransform() const;
		math::float4x4			GetGlobalTransform() const;

	public:
		Component*				AddComponent(ComponentType type);
		Component*				GetComponent(ComponentType type) const;
		
		std::vector<Component*> GetComponents(ComponentType type) const;

	public:
		bool					enabled = true;
		bool					drawGOBBox = false;
		bool					duplicating = false;
		bool					toBeDeleted = false;
		bool					toBeCopied = false;
		bool					moveGOUp = false;
		bool					moveGODown = false;

		math::AABB				bbox;


		std::string				uuid		= "";
		std::string				parentUuid	= "";
		
	public:
		const char*				filePath	= nullptr;
		const char*				name		= DEFAULT_GO_NAME;
		
		GameObject*				parent		= nullptr;
		
		ComponentTransform*		transform	= nullptr;
		ComponentMesh*			mesh		= nullptr;
		ComponentMaterial*		material	= nullptr;

		std::list<GameObject*>	goChilds;
		std::vector<Component*>	components;

};

#endif // __GameObject_h__
