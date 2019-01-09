#include "ModuleScene.h"
#include "Application.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

#include "par_shapes.h"

#pragma warning(pop)

#define PAR_SHAPES_IMPLEMENTATIONS


// Constructor
ModuleScene::ModuleScene() 
{
	
}

// Destructor
ModuleScene::~ModuleScene() 
{
	
}

bool ModuleScene::Init() 
{
	root = new GameObject();
	root->name = "root";

	return true;
}

update_status ModuleScene::Update() 
{
	update_status ret = UPDATE_CONTINUE;

	root->Update();

	return ret;
}

void ModuleScene::Draw() 
{
	root->Draw();
}

void ModuleScene::DrawHierarchy() 
{
	for (auto& child : root->goChilds) 
	{
		child->DrawHierarchy(goSelected);
	}
}

GameObject* ModuleScene::CreateGameObject(const char* goName, GameObject* goParent, const math::float4x4& transform, const char* fileLocation) 
{
	GameObject* gameObject = nullptr;

	if (goName != nullptr) 
	{
		char* go_name = new char[strlen(goName)];
		strcpy(go_name, goName);

		gameObject = new GameObject(go_name, transform, goParent, fileLocation);

	}
	else 
	{
		if (goParent != nullptr) 
		{
			std::string childName = "ChildOf";
			std::string childNameStr = "ChildOf";
			childNameStr += goParent->name;
			char* childName = new char[strlen(childNameStr.c_str())];
			strcpy(childName, childNameStr.c_str());

			gameObject = new GameObject(childName, transform, goParent, fileLocation);
		}
		else 
		{
			char* goName = new char[strlen(DEFAULT_GO_NAME)];
			strcpy(goName, DEFAULT_GO_NAME);

			gameObject = new GameObject(goName, transform, goParent, fileLocation);
		}
	}

	return gameObject;
}

GameObject* ModuleScene::CreateCamera(GameObject* goParent, const math::float4x4& transform)
{
	GameObject* gameObject = nullptr;

	char* cameraName = new char[strlen(DEFAULT_CAMERA_NAME)];
	strcpy(cameraName, DEFAULT_CAMERA_NAME);

	gameObject = new GameObject(cameraName, transform, goParent, nullptr);
	gameObject->AddComponent(ComponentType::CAMERA);

	return gameObject;
}
