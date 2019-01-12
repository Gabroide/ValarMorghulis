#ifndef __Component_h__
#define __Component_h__

#include "GameObject.h"

class GameObject;

enum class ComponentType {
	EMPTY = 0,
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT,
	AUDIO
};

class Component
{
	public:
		Component(GameObject* goContainer, ComponentType type);
		Component(const Component& duplicateComponent);
		virtual ~Component();

		bool				DrawComponentState();
		
		void				Remove();
		virtual void		Update();
		
public:
		virtual void DrawProperties() 
		{
		
		};
		
		virtual Component* Duplicate()
		{ 
			return nullptr; 
		};

		virtual void Enable() 
		{
			enabled = true;
		};
		
		virtual void Disable() 
		{ 
			enabled = false; 
		};
		
public:
		bool				enabled			= true;
		
		ComponentType		componentType	= ComponentType::EMPTY;
		
		std::string			uuid			= "";
		std::string			parentUuid		= "";
		
public:
		GameObject*			goContainer		= nullptr;

};

#endif // __Component_h__