#include <assert.h>

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModuleProgram.h"
#include "ModuleModel.h"
#include "ModuleScene.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "GameObject.h"

#include "glew-2.1.0\include\GL\glew.h"

// Constructor
ModuleModel::ModuleModel() 
{
	
}

// Destructor
ModuleModel::~ModuleModel() 
{ 
	
}

unsigned ModuleModel::Load(const char* path) 
{
	assert(path != nullptr);

	std::string fullFilePath(path);
	std::size_t found = fullFilePath.find_last_of("/");
	std::string name = fullFilePath.substr(found + 1, fullFilePath.length().c_str());

	GameObject(name.c_str(), nullptr);
	models.emplace_back(path);

	LOG("Loaded Model: %s", path);

	return 1;
}

void ModuleModel::DrawModels() 
{
	for (auto const& model : models) 
	{
		model.Draw();
	}
}

void ModuleModel::ApplyTexture(Texture texture) 
{
	for (auto& model : models) 
	{
		model.UpdateTexture(texture);
	}
}

void ModuleModel::DeleteModels() 
{
	models.clear();
}

void ModuleModel::DrawGUI() 
{
	if (ImGui::Checkbox("Checkers Texture", &checkersTexture)) 
	{
		if (checkersTexture && checkTexture.id == 0) 
		{
			checkTexture = App->textures->Load("checkersTexture.jpg");
		}
	}
}
