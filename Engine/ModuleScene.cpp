#include "ModuleScene.h"

// Contructor
ModuleScene::ModuleScene() { }

// Destructor
ModuleScene::~ModuleScene() 
{ 
	
}

bool ModuleScene::Init() 
{
	root = new GameObject("root", nullptr);

	return true;
}

update_status ModuleScene::Update() 
{
	update_status ret = UPDATE_CONTINUE;

	return ret;
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

GameObject* ModuleScene::CreateGameObject(const char* goName, GameObject* goParent) 
{
	GameObject* gameObject = nullptr;

	if (goName != nullptr) 
	{
		gameObject = new GameObject(goName);

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
		std::string childName = "MyParentIs";

		if (goParent != nullptr) 
		{
			childName += goParent->name;

			gameObject = new GameObject(childName.c_str(), goParent);
			goParent->goChilds.push_back(gameObject);
		}
		else 
		{
			childName += root->name;

			gameObject = new GameObject(childName.c_str(), root);
			root->goChilds.push_back(gameObject);
		}

	}

	return gameObject;
}
