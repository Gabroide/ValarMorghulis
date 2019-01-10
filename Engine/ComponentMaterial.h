#ifndef __ComponentMaterial_h__
#define __ComponentMaterial_h__

#include "assert.h"
#include "Component.h"
#include "ModuleTextures.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "Math\float4.h"

#include "IMGUI\imgui.h"

#include "assimp\material.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* goContainer);
	ComponentMaterial(GameObject* goContainer, const aiMaterial* material);
	ComponentMaterial(const ComponentMaterial& duplicatedComponent);
	~ComponentMaterial();

	void			DrawProperties() override;
	void			ComputeMaterial(const aiMaterial* material);
	void			DeleteTexture();

public:
	Component*		Duplicate();
	
public:
	unsigned		shader	= 0u;
	
	math::float4	color	= math::float4::one;

public:
	Texture*		texture	= nullptr;

};

#endif // __ComponentMaterial_h__