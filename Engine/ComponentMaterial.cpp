#include "ComponentMaterial.h"
#include "ModuleTextures.h"
#include "Application.h"
#include "ModuleProgram.h"

// Constructor
ComponentMaterial::ComponentMaterial(GameObject* goContainer) : Component(goContainer, ComponentType::MATERIAL)
{
	this->shader = App->program->textureProgram;
}

ComponentMaterial::ComponentMaterial(GameObject* goContainer, const aiMaterial* material) : Component(goContainer, ComponentType::MATERIAL) 
{
	this->shader = App->program->textureProgram;
	ComputeMaterial(material);
}

// Destructor
ComponentMaterial::~ComponentMaterial() 
{
	DeleteTexture();
}

void ComponentMaterial::ComputeMaterial(const aiMaterial* material) 
{
	std::string texturePath;
	if (material != nullptr) 
	{
		aiTextureMapping mapping = aiTextureMapping_UV;
		aiString file;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &file, &mapping, 0);
		texturePath = goContainer->GetFileFolder() + file.C_Str();
	}
	else 
	{
		texturePath = "checkersTexture.jpg";
	}

	DeleteTexture();
	texture = App->textures->Load(texturePath.c_str());
}

void ComponentMaterial::DeleteTexture() 
{
	if (texture != nullptr) 
	{
		glDeleteTextures(1, (GLuint*)&texture->id);
	}

	delete texture;
	texture = nullptr;
}