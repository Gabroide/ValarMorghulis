#include <list>

#include "ModuleScene.h"
#include "Application.h"
#include "ModuleProgram.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"

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

GameObject* ModuleScene::GenerateSphere(GameObject* goParent, int slices, int stacks, const math::float3& pos, const math::Quat& rot, const float size, const math::float4& color) 
{
	assert(slices >= 1);
	assert(stacks >= 1);

	par_shapes_mesh* mesh = par_shapes_create_parametric_sphere(slices, stacks);

	if (mesh)
	{
		GameObject* sphere = new GameObject("Sphere", math::float4x4::identity, nullptr);
		sphere->transform->SetRotation(rot);
		sphere->transform->SetPosition(pos);

		par_shapes_scale(mesh, size, size, size);

		ComponentMesh* sphereMesh = (ComponentMesh*)sphere->AddComponent(ComponentType::MESH);
		sphereMesh->ComputeMesh(mesh);

		par_shapes_free_mesh(mesh);

		ComponentMaterial* sphereMaterial = (ComponentMaterial*)sphere->AddComponent(ComponentType::MATERIAL);
		sphereMaterial->shader = App->program->basicProgram;
		sphereMaterial->color = color;

		goSelected = sphere;

		return sphere;
	}

	LOG("ERROR: Sphere cannot be created because of par_shape error");

	return nullptr;
}
