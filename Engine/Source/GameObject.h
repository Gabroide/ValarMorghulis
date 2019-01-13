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

#include "rapidjson-1.1.0\include\rapidjson\document.h"
#include "rapidjson-1.1.0\include\rapidjson\prettywriter.h"

class Component;
class ComponentMesh;
class ComponentMaterial;
class ComponentTransform;
class Config;

enum class ComponentType;

class GameObject
{
	public:
		GameObject();
		GameObject(const char* goName, const math::float4x4& transform);
		GameObject(const char* goName, const math::float4x4& transform, GameObject* goParent);
		GameObject(const GameObject& duplicateGameObject);
		~GameObject();

		bool					Save(Config* config);

		void					Update();
		void					Draw(const math::Frustum& frustum) const;
		void					CleanUp();
		void					DrawProperties();
		void					DrawHierarchy(GameObject* goSelected);
		void					DrawBBox() const;n
		void					RemoveComponent(Component* component);
		void					ComputeBBox();
		void					ModelTransform(unsigned shader) const;
		void					Load(Config* config, rapidjson::Value& value);

		math::float4x4			GetLocalTransform() const;
		math::float4x4			GetGlobalTransform() const;

	public:
		Component*				AddComponent(ComponentType type);
		Component*				GetComponent(ComponentType type) const;
		
		std::vector<Component*> GetComponents(ComponentType type) const;

	public:
		bool					enabled		= true;
		bool					drawGOBBox	= false;
		bool					duplicating	= false;
		bool					toBeDeleted = false;
		bool					toBeCopied	= false;
		bool					moveGOUp	= false;
		bool					moveGODown	= false;
		bool					staticGo	= false;

		math::AABB				bbox;

	public:
		const char*				name		= DEFAULT_GO_NAME;
		const char*				uuid		= nullptr;
		const char*				parentUuid	= nullptr;

		GameObject*				parent		= nullptr;
		
		ComponentTransform*		transform	= nullptr;
		ComponentMesh*			mesh		= nullptr;
		ComponentMaterial*		material	= nullptr;

		std::list<GameObject*>	goChilds;
		std::list<Component*>	components;
	
};

#endif // __GameObject_h__
