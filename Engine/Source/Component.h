#ifndef __Component_h__
#define __Component_h__

#include "rapidjson-1.1.0\include\rapidjson\document.h"
#include "rapidjson-1.1.0\include\rapidjson\prettywriter.h"

class Config;
class GameObject;

enum class ComponentType {
	EMPTY = 0,
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT
};

class Component
{
	public:
		Component(GameObject* goContainer, ComponentType type);
		Component(const Component& duplicateComponent);
		virtual ~Component();

		bool				DrawComponentState();

		virtual void		Update();
	public:
		virtual void DrawProperties(bool enabled) 
		{

		};
	
		virtual void Enable() 
		{ 
			enabled = true; 
		};


		virtual void Disable() 
		{ 
			enabled = false; 
		};

		virtual void Save(Config* config) 
		{
		
		};

		virtual void Load(Config* config, rapidjson::Value& value) 
		{
		
		};

	public:
		virtual Component*	Duplicate() 
		{ 
			return nullptr; 
		};

	
	public:
		bool				toBeDeleted		= false;
		bool				enabled			= true;
	
		char				uuid[37];
		char				parentUuid[37];

		ComponentType		componentType	= ComponentType::EMPTY;
	
	public:
		GameObject*			goContainer		= nullptr;

};

#endif // __Component_h__