#ifndef __Component_h__
#define __Component_h__

#include "GameObject.h"

class GameObject;

enum class ComponentType
{
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL,
	AUDIO,
	LIGHT
};

class Component
{
public:
	Component(GameObject* goContainer, ComponentType type);
	virual ~Component();

	virtual void Update();

public:
	virtual void Enable()
	{
		enabled = true;
	};
	
	virtual void Disable()
	{
		enabled = false;
	};

public:
	bool			enabled			= false;

	ComponentType	componentType	= ComponentType::EMPTY;

public:
	GameObject*		goConainer		= nullptr;

};

