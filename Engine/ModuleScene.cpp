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

bool ModuleScene::CleanUp() 
{

	for (std::list<GameObject*>::reverse_iterator it = root->goChilds.rbegin(); it != root->goChilds.rend(); ++it) {
		delete *it;
	}

	root->goChilds.clear();

	return true;
}

void ModuleScene::Draw() 
{
	root->Draw();
}

void ModuleScene::DrawHierarchy() 
{
	root->DrawHierarchy(goSelected);
}

GameObject* ModuleScene::CreateGameObject(const char* goName, GameObject* goParent, const aiMatrix4x4& transform, const char* fileLocation)
{
	GameObject* gameObject = nullptr;

	if (goName != nullptr) 
	{
		gameObject = new GameObject(goName, transform, fileLocation);

		if (goParent != nullptr) 
		{
			gameObject->parent = goParent;
			goParent->goChilds.push_back(gameObject);
		}
		else 
		{
			gameObject->parent = root;
			root->goChilds.push_back(gameObject);
		}

	}
	else 
	{
		if (goParent != nullptr) 
		{
			std::string childName = "ChildOf";
			childName += goParent->name;

			gameObject = new GameObject(childName, transform, goParent, fileLocation);
			goParent->goChilds.push_back(gameObject);
		}
		else 
		{
			gameObject = new GameObject(std::string("GameObject"), transform, root, fileLocation);
			root->goChilds.push_back(gameObject);
		}
	}

	return gameObject;
}


