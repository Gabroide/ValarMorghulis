#include "Application.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleCamera.h"
#include "ModuleProgram.h"
#include "ComponentMesh.h"
#include "ComponentLight.h"
#include "ComponentCamera.h"
#include "ComponentMaterial.h"
#include "ComponentTransform.h"
#include "ModuleFileSystem.h"
#include "Config.h"

#include "SDL\include\SDL_mouse.h"

#include "debugdraw.h"

// Constructor
GameObject::GameObject() 
{
	uuid = App->fileSystem->NewGuuid();
	transform = (ComponentTransform*)AddComponent(ComponentType::TRANSFORM);
}

// Constructor Overloaded
GameObject::GameObject(const char* goName, GameObject* goParent) 
{
	uuid = App->fileSystem->NewGuuid();
	char* copyName = new char[strlen(goName)];
	strcpy(copyName, goName);
	name = copyName;

	if (goParent != nullptr)
	{
		parent = goParent;
		parentUuid = goParent->uuid;
		goParent->goChilds.push_back(this);
	}
}

// Constructor Overloaded
GameObject::GameObject(const char* goName, const math::float4x4& parentTransform) 
{
	uuid = App->fileSystem->NewGuuid();

	char* copyName = new char[strlen(goName)];
	strcpy(copyName, goName);
	name = copyName;

	parent = App->scene->root;
	parentUuid = App->scene->root->uuid;
	transform = (ComponentTransform*)AddComponent(ComponentType::TRANSFORM);
	transform->AddTransform(parentTransform);
	App->scene->root->goChilds.push_back(this);
}

// Constructor Overloaded
GameObject::GameObject(const char* goName, const math::float4x4& parentTransform, GameObject* goParent) 
{
	uuid = App->fileSystem->NewGuuid();

	char* copyName = new char[strlen(goName)];
	strcpy(copyName, goName);
	name = copyName;

	if (goParent != nullptr) 
	{
		parent = goParent;
		parentUuid = goParent->uuid;
		goParent->goChilds.push_back(this);
	}
	else 
	{
		parent = App->scene->root;
		parentUuid = App->scene->root->uuid;
		App->scene->root->goChilds.push_back(this);
	}

	transform = (ComponentTransform*)AddComponent(ComponentType::TRANSFORM);
	transform->AddTransform(parentTransform);
}

// Constructor Overloaded
GameObject::GameObject(const GameObject& duplicateGameObject) 
{
	uuid = App->fileSystem->NewGuuid();
	parentUuid = duplicateGameObject.parentUuid;

	char* copyName = new char[strlen(duplicateGameObject.name)];
	strcpy(copyName, duplicateGameObject.name);
	name = copyName;

	filePath = duplicateGameObject.filePath;
	bbox = duplicateGameObject.bbox;

	for (const auto &component : duplicateGameObject.components) 
	{
		Component* duplicatedComponent = component->Duplicate();
		components.push_back(duplicatedComponent);
		duplicatedComponent->goContainer = this;
		duplicatedComponent->parentUuid = uuid;
		
		if (duplicatedComponent->componentType == ComponentType::TRANSFORM) 
		{
			transform = (ComponentTransform*)duplicatedComponent;
		}
		
		if (duplicatedComponent->componentType == ComponentType::MESH) 
		{
			mesh = (ComponentMesh*)duplicatedComponent;
		}
		
		if (duplicatedComponent->componentType == ComponentType::MATERIAL) 
		{
			material = (ComponentMaterial*)duplicatedComponent;
		}
	}

	for (const auto &child : duplicateGameObject.goChilds) 
	{
		GameObject* duplicatedChild = new GameObject(*child);
		duplicatedChild->parent = this;
		duplicatedChild->parentUuid = uuid;
		goChilds.push_back(duplicatedChild);
	}
}

//Destructor
GameObject::~GameObject() 
{
	for (auto &component : components) 
	{
		delete component;
		component = nullptr;
	}
	
	components.clear();

	for (auto &child : goChilds) 
	{
		delete child;
		child = nullptr;
	}

	goChilds.clear();

	parent = nullptr;
	transform = nullptr;
	mesh = nullptr;
	material = nullptr;
}

void GameObject::Update() 
{
	if (!enabled)
	{
		return;
	}

	for (std::list<GameObject*>::iterator itChild = goChilds.begin(); itChild != goChilds.end();) 
	{
		(*itChild)->Update();

		if ((*itChild)->moveGOUp) 
		{
			(*itChild)->moveGOUp = false;
			
			if (std::abs(std::distance(goChilds.begin(), itChild)) != 0) 
			{
				std::swap(*itChild, *std::prev(itChild));
			}
		}

		if ((*itChild)->moveGODown) 
		{
			(*itChild)->moveGODown = false;
			
			if (std::abs(std::distance(goChilds.begin(), itChild)) != goChilds.size() - 1) 
			{
				std::swap(*itChild, *std::next(itChild));
			}
		}

		if ((*itChild)->toBeCopied) 
		{
			(*itChild)->toBeCopied = false;
			GameObject* goCopied = new GameObject(**itChild);
			goCopied->parent = this;
			goChilds.push_back(goCopied);
			LOG("Duplicated GameObject: %s", (*itChild)->name);
		}

		if ((*itChild)->toBeDeleted) 
		{
			(*itChild)->toBeDeleted = false;
			(*itChild)->CleanUp();
			LOG("Removed GameObject: %s", (*itChild)->name);
			delete *itChild;
			goChilds.erase(itChild++);
		}
		else 
		{
			++itChild;
		}
	}
}

void GameObject::Draw(const math::Frustum& frustum) const 
{
	if (!enabled)
	{
		return;
	}

	for (const auto &child : goChilds) 
	{
		child->Draw(frustum);
	}

	if (transform == nullptr)
	{
		return;
	}

	if (App->scene->goSelected == this) 
	{
		DrawBBox();
	}

	if (mesh == nullptr || mesh != nullptr && !mesh->enabled || mesh != nullptr && mesh->mesh.vbo == 0) 
	{
	
		return;
	}

	if (!frustum.Intersects(bbox)) 
	{
		DrawBBox();
	
		return;
	}

	unsigned program = App->program->blinnProgram;
	
	if (material == nullptr) 
	{
		program = App->program->textureProgram;
	}
	else if (!material->enabled) 
	{
		program = App->program->colorProgram;
	}

	glUseProgram(program);
	ModelTransform(program);

	if (material != nullptr) 
	{
		((ComponentMesh*)mesh)->Draw(program, material);
	}

	glUseProgram(0);
}

void GameObject::CleanUp() 
{
	for (auto &child : goChilds) 
	{
		child->CleanUp();
	}
}

void GameObject::DrawProperties() 
{
	assert(name != nullptr);

	ImGui::InputText("Name", (char*)name, 50.0f); ImGui::SameLine();

	if (ImGui::Checkbox("Enabled", &enabled)) 
	{
		for (auto &component : components) 
		{
			component->enabled = enabled;
		}
	}

	if (ImGui::CollapsingHeader("Info")) 
	{
		ImGui::Text("UUID: "); ImGui::SameLine();
		ImGui::TextColored({ 0.4f,0.4f,0.4f,1.0f }, uuid);
		ImGui::Text("Parent UUID: "); ImGui::SameLine();
		ImGui::TextColored({ 0.4f,0.4f,0.4f,1.0f }, parentUuid);
	}

	for (auto &component : components) 
	{
		component->DrawProperties();
	}
}

void GameObject::DrawHierarchy(GameObject* goSelected) 
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (goSelected == this ? ImGuiTreeNodeFlags_Selected : 0);

	ImGui::PushID(this);
	
	if (goChilds.empty()) 
	{
		node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
	}

	bool obj_open = ImGui::TreeNodeEx(this, node_flags, name);

	if (ImGui::IsItemClicked()) 
	{
		if (App->scene->goSelected != nullptr) 
		{
			App->scene->goSelected->drawGOBBox = false;
		}
	
		App->scene->goSelected = this;
		drawGOBBox = true;
	}

	if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) 
	{
		GameObject* draggedGo = this;
		ImGui::SetDragDropPayload("DragDropHierarchy", &draggedGo, sizeof(GameObject*), ImGuiCond_Once);
		ImGui::Text("%s", name);
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget()) 
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragDropHierarchy")) 
		{
			IM_ASSERT(payload->DataSize == sizeof(GameObject*));
			GameObject* droppedGo = (GameObject*)*(const int*)payload->Data;

			if (droppedGo->parent != this) 
			{
				bool droppedIntoChild = false;
				GameObject* inheritedTrasnform = this;
				
				while (inheritedTrasnform->parent != nullptr) 
				{
					if (inheritedTrasnform->parent == droppedGo) 
					{
						droppedIntoChild = true;
					}
				
					inheritedTrasnform = inheritedTrasnform->parent;
				}
				
				inheritedTrasnform = nullptr;

				if (!droppedIntoChild) 
				{
					goChilds.push_back(droppedGo);

					if (droppedGo->transform != nullptr) 
					{
						droppedGo->transform->SetLocalToWorld(droppedGo->GetGlobalTransform());
					}
					
					droppedGo->parent->goChilds.remove(droppedGo);
					droppedGo->parent = this;
					droppedGo->parentUuid = uuid;
					
					if (droppedGo->transform != nullptr) 
					{
						droppedGo->transform->SetWorldToLocal(droppedGo->parent->GetGlobalTransform());
					}
				}
			}
		}
	
		ImGui::EndDragDropTarget();
	}

	if (ImGui::IsItemHovered() && App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN) 
	{
		ImGui::OpenPopup("Modify_GameObject");
		App->scene->goSelected = this;
	}

	if (ImGui::BeginPopup("Modify_GameObject")) 
	{
		if (ImGui::Selectable("Add Empty GameObject")) 
		{
			App->scene->CreateGameObject(DEFAULT_GO_NAME, this);
		}
		
		if (ImGui::Selectable("Duplicate") && App->scene->goSelected != nullptr) 
		{
			toBeCopied = true;
		}
		
		if (ImGui::Selectable("Remove") && App->scene->goSelected != nullptr) 
		{
			toBeDeleted = true;
			
			if (App->scene->goSelected == this) 
			{
				App->scene->goSelected = nullptr;
			}
		}

		if (ImGui::Selectable("Move up") && App->scene->goSelected != nullptr) 
		{
			moveGOUp = true;
		}
		
		if (ImGui::Selectable("Move down") && App->scene->goSelected != nullptr) 
		{
			moveGODown = true;
		}

		ImGui::EndPopup();
	}

	if (obj_open) 
	{
		for (auto &child : goChilds) 
		{
			child->DrawHierarchy(goSelected);
		}

		if (!(node_flags & ImGuiTreeNodeFlags_NoTreePushOnOpen)) 
		{
			ImGui::TreePop();
		}
	}

	ImGui::PopID();
}

Component* GameObject::AddComponent(ComponentType type) 
{
	Component* component = nullptr;

	switch (type) 
	{
	case ComponentType::CAMERA:
		component = new ComponentCamera(this);
		
		if (App->camera->selectedCamera == nullptr) 
		{
			App->camera->selectedCamera = (ComponentCamera*)component;
		}

		App->camera->gameCameras.push_back((ComponentCamera*)component);
		break;

	case ComponentType::TRANSFORM:
		if (GetComponent(ComponentType::TRANSFORM) == nullptr) 
		{
			component = new ComponentTransform(this, math::float4x4().identity);
			transform = (ComponentTransform*)component;
		}
		else 
		{
			LOG("Warn: Transform already exist");
		}

		break;

	case  ComponentType::MESH:
		if (GetComponent(ComponentType::MESH) == nullptr) {
			component = new ComponentMesh(this, nullptr);
			mesh = (ComponentMesh*)component;
			AddComponent(ComponentType::MATERIAL);
		}
		else
		{
			LOG("Warn: Mesh already exist");
		}
	
		break;
	
	case ComponentType::MATERIAL:
		if (GetComponent(ComponentType::MATERIAL) == nullptr) 
		{
			component = new ComponentMaterial(this);
			material = (ComponentMaterial*)component;
		}
		else 
		{
			LOG("Warn: Material already exist");
		}
		
		break;
	
	case ComponentType::EMPTY:
	default:
		break;
	}

	if (component != nullptr) 
	{
		components.push_back(component);
	}

	return component;
}

void GameObject::RemoveComponent(Component* component) 
{
	assert(component != nullptr);

	for (std::list<Component*>::iterator it = components.begin(); it != components.end(); ++it) 
	{
		if ((*it) == component) 
		{
			components.erase(it);
			delete component;
			component = nullptr;

			return;
		}
	}
}

Component* GameObject::GetComponent(ComponentType type) const 
{
	for (auto &component : components) 
	{
		if (component->componentType == type) 
		{
		
			return component;
		}
	}

	return nullptr;
}

std::vector<Component*> GameObject::GetComponents(ComponentType type) const 
{
	std::vector<Component*> list;
	
	for (auto &component : components) 
	{
		if (component->componentType == type) 
		{
			list.push_back(component);
		}
	}

	return list;
}

math::float4x4 GameObject::GetLocalTransform() const 
{
	if (transform == nullptr) 
	{
	
		return math::float4x4::identity;
	}

	return math::float4x4::FromTRS(transform->position, transform->rotation, transform->scale);
}

math::float4x4 GameObject::GetGlobalTransform() const 
{
	if (parent != nullptr) 
	{
	
		return parent->GetGlobalTransform() * GetLocalTransform();
	}

	return GetLocalTransform();
}

void GameObject::ModelTransform(unsigned shader) const 
{
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_TRUE, &GetGlobalTransform()[0][0]);
}

void GameObject::ComputeBBox() 
{
	for (auto& child : goChilds) 
	{
		if (child->mesh != nullptr) 
		{
			child->ComputeBBox();
		}
	}

	if (mesh != nullptr) 
	{
		bbox.SetNegativeInfinity();
		bbox.Enclose(mesh->mesh.bbox);
		bbox.TransformAsAABB(GetGlobalTransform());
	}
}

void GameObject::DrawBBox() const 
{
	if (mesh != nullptr) 
	{
		dd::aabb(bbox.minPoint, bbox.maxPoint, math::float3(0.0f, 1.0f, 0.0f), true);
	}

	for (auto& child : goChilds) 
	{
		child->DrawBBox();
	}
}

/* RapidJson storage */
bool GameObject::Save(Config* config) 
{
	config->StartObject();

	config->AddString("uuid", uuid);
	config->AddString("name", name);

	if (parent != nullptr) 
	{
		config->AddString("parent", parent->uuid);
	}

	config->AddBool("enabled", enabled);

	config->StartArray("components");

	for (std::list<Component*>::iterator it = components.begin(); it != components.end(); ++it) 
	{
		(*it)->Save(config);
	}

	config->EndArray();

	config->EndObject();

	return true;
}

void GameObject::Load(Config* config, rapidjson::Value& value) 
{
	uuid = config->GetString("uuid", value);
	enabled = config->GetBool("enabled", value);

	rapidjson::Value components = value["components"].GetArray();

	for (rapidjson::Value::ValueIterator it = components.Begin(); it != components.End(); ++it) 
	{
		Component* component = AddComponent(config->GetComponentType("componentType", (*it)));

		if (component != nullptr) 
		{
			component->Load(config, (*it));
		}
	}
}