#include "ModuleScene.h"

// Contructor
ModuleScene::ModuleScene() { }

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
	root->Update();

	return UPDATE_CONTINUE;
}


void ModuleScene::Draw() 
{
	root->Draw();
}

void ModuleScene::DrawHierarchy() 
{
	for (auto& child : this->root->goChilds)
	{
		child->DrawHierarchy(goSelected);
	}
}

GameObject* ModuleScene::CreateGameObject(const char* goName, GameObject* goParent, const aiMatrix4x4& transform, const char* fileLocation)
{
	GameObject* gameObject = nullptr;

	if (goName != nullptr) 
	{
		char* go_name = new char[strlen(goName)];
		strcpy(go_name, goName);

		gameObject = new GameObjec(go_name, transform, goParent, fileLocation);
	}
	else 
	{
		if (goParent != nullptr) 
		{
			std::string childName = "ChildOf";
			childName += goParent->name;

			gameObject = new GameObject(childName.c_str, transform, goParent, fileLocation);
		}
		else 
		{
			gameObject = new GameObject(std::string("GameObject").c_str, transform, root, fileLocation);
		}
	}

	return gameObject;
}


