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
	Component(const Component& duplicateComponent);
	virtual ~Component();

	virtual void	 Update();
	
	bool			DrawComponentsState();

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

	virtual void	DrawProperties()
	{

	};

public:
	bool			enabled			= true;

	ComponentType	componentType	= ComponentType::EMPTY;

public:
	GameObject*		goContainer		= nullptr;


};

