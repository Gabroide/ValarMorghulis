#ifndef __ComponentTMaterial_h__
#define __ComponentTMaterial_h__

#include "assert.h"
#include "ModuleTextures.h"
#include "Component.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib\include\Math\float4.h"

#include "IMGUI\imgui.h"

#include "Assimp\material.h"

enum class MaterialType {
	NO_TYPE_SELECTED = 0,
	OCCLUSION_MAP,
	DIFFUSE_MAP,
	SPECLAR_MAP,
	EMISSIVE_MAP
};

class ComponentMaterial : public Component
{
	public:
		ComponentMaterial(GameObject* goContainer);
		ComponentMaterial(GameObject* goContainer, const aiMaterial* material);
		ComponentMaterial(const ComponentMaterial& duplicatedComponent);
		~ComponentMaterial();

		void		DrawProperties() override;

	public:
		Component*	Duplicate() override;

	public:
		Material	material;

	private:
		void		DeleteTexture(unsigned id);
		void		DrawComboBoxMaterials(const char* id, MaterialType matType, static std::string& labelCurrentFileTextureSelected);

	private:
		std::string diffuseSelected;
		std::string occlusionSelected;
		std::string specularSelected;
		std::string emissiveSelected;

};

#endif // __ComponentTMaterial_h__
