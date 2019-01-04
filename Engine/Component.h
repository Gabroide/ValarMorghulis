#ifndef __Component_h__
#define __Component_h__

#include "GameObject.h"

class GameObject;

enum class ComponentType
{
	EMPTY = 0,
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
	virtual ~Component();

	virtual void	 Update();

	void			Remove();

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
	GameObject*		goContainer		= nullptr;


};

