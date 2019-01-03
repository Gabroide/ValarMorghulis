#ifndef __Component_h__
#define __Component_h__

#include "GameObject.h"

class GameObject;

enum class componentType
{
	CAMERA,
	TRANSFORM,
	MESH,
	MATERIAL,
	AUDIO
};

class Component
{
public:
	Component();
	~Component();

	virtual void Enable();
	virtual void Update();
	virtual void Disable();

};

