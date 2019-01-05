#ifndef __ComponentMaterial_h__
#define __ComponentMaterial_h__

#include "assert.h"
#include "Component.h"
#include "Model.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "IMGUI\imgui.h"

#include "assimp\material.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* goContainer, const aiMaterial* material);
	~ComponentMaterial();

	void			ComputeMaterial(const aiMaterial* material);
	void			DeleteTexture();

public:
	unsigned int	shader = 0u;

public:
	Texture*		texture = nullptr;

};

#endif // __ComponentMaterial_h__