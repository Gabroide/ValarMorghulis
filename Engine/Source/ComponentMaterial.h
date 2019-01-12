#ifndef __ComponentTMaterial_h__
#define __ComponentTMaterial_h__

#include "assert.h"
#include "ModuleTextures.h"
#include "Component.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib\include\Math\float4.h"

#include "IMGUI\imgui.h"

#include "Assimp\material.h"

class ComponentMaterial : public Component
{
	public:
		ComponentMaterial(GameObject* goContainer);
		ComponentMaterial(GameObject* goContainer, const aiMaterial* material);
		ComponentMaterial(const ComponentMaterial& duplicatedComponent);
		~ComponentMaterial();

		void		ComputeMaterial(const aiMaterial* material);
		void		DeleteTexture();
		void		DrawProperties() override;

	public:
		Component*	Duplicate() override;

	public:
		unsigned		occlusionMap	= 0u;
		unsigned		diffuseMap		= 0u;
		unsigned		specularMap		= 0u;
		unsigned		emissiveMap		= 0u;
		unsigned		shader			= 0u;

		int				ambientWidth	= 0;
		int				ambientHeight	= 0;
		int				diffuseWidth	= 0;
		int				diffuseHeight	= 0;
		int				specularWidth	= 0;
		int				specularHeight	= 0;
		int				emissiveWidth	= 0;
		int				emissiveHeight	= 0;
		int				width			= 0;
		int				height			= 0;

		float			ambientK		= 0.5f;
		float			diffuseK		= 1.0f;
		float			specularK		= 0.6f;
		float			shininess		= 64.0f;

		math::float4	diffuseColor	= float4(1.0f, 1.0f, 1.0f, 1.0f);
		math::float4	specularColor	= float4(1.0f, 1.0f, 1.0f, 1.0f);
		math::float4	emissiveColor	= float4(0.0f, 0.0f, 0.0f, 0.0f);
		math::float4	color			= math::float4::one;

	public:
		Texture*		texture			= nullptr;
};

#endif // __ComponentTMaterial_h__
