#include "Application.h"
#include "ModuleScene.h"
#include "ModuleProgram.h"
#include "ModuleInput.h"
#include "ComponentLight.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"

#include "SDL\include\SDL_mouse.h"

// Constructor
GameObject::GameObject() 
{
	
}

// Constructor
GameObject::GameObject(const char* goName, const aiMatrix4x4& transform, const char* fileLocation) 
{
	name = goName;

	if (fileLocation != nullptr) 
	{
		filePath = fileLocation;
	}

	this->parent = App->scene->root;
	this->transform = (ComponentTransform*)AddComponent(ComponentType::TRANSFORM);
	this->transform->AddTransform(transform);
	App->scene->root->goChilds.push_back(this);
}

GameObject::GameObject(const char* goName, const aiMatrix4x4& transform, GameObject* goParent, const char* fileLocation) 
{
	name = goName;

	if (goParent != nullptr) 
	{
		this->parent = goParent;
		goParent->goChilds.push_back(this);
	}
	else 
	{
		this->parent = App->scene->root;
		App->scene->root->goChilds.push_back(this);
	}

	this->transform = (ComponentTransform*)AddComponent(ComponentType::TRANSFORM);
	this->transform->AddTransform(transform);

	if (fileLocation != nullptr) 
	{
		filePath = fileLocation;
	}
}

// Constructor
GameObject::GameObject(const GameObject& duplicateGameObject) 
{
	char* copyName = new char[strlen(duplicateGameObject.name)];
	strcpy(copyName, duplicateGameObject.name);
	name = copyName;
	filePath = duplicateGameObject.filePath;
	bbox = duplicateGameObject.bbox;

	for (const auto &component : duplicateGameObject.components) 
	{
		Component* duplicatedComponent = component->Duplicate();
		components.push_back(duplicatedComponent);
		
		if (duplicatedComponent->componentType == ComponentType::TRANSFORM) 
		{
			transform = (ComponentTransform*)duplicatedComponent;
		}
	}

	for (const auto &child : duplicateGameObject.goChilds) 
	{
		GameObject* duplicatedChild = new GameObject(*child);
		duplicatedChild->parent = this;
		goChilds.push_back(duplicatedChild);
	}
}

// Destructor
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
		}

		if ((*itChild)->moveGODown) 
		{
			(*itChild)->moveGODown = false;
		}

		if ((*itChild)->toBeCopied) 
		{
			(*itChild)->toBeCopied = false;
			GameObject* goCopied = new GameObject(**itChild);
			goCopied->parent = this;
			goChilds.push_back(goCopied);
			LOG("Duplicated GO: %s", (*itChild)->name);
		}

		if ((*itChild)->toBeDeleted) 
		{
			(*itChild)->toBeDeleted = false;
			(*itChild)->CleanUp();
			LOG("Removed GO: %s", (*itChild)->name);
			delete *itChild;
			goChilds.erase(itChild++);
		}
		else 
		{
			++itChild;
		}
	}

}

void GameObject::Draw() const 
{
	if (!enabled)
	{
		return;
	}

	for (const auto& child : goChilds) 
	{
		child->Draw();
	}
	if (transform == nullptr)
	{
	
		return;
	}

	ComponentMaterial* material = (ComponentMaterial*)GetComponent(ComponentType::MATERIAL);
	unsigned shader = 0u;
	Texture* texture = nullptr;

	if (material != nullptr && material->enabled) 
	{
		shader = material->GetShader();
		texture = material->GetTexture();
	}
	else 
	{
		shader = App->program->textureProgram;
	}

	if (texture == nullptr) 
	{
		texture = App->textures->defaultTexture;
	}

	glUseProgram(shader);
	ModelTransform(shader);

	Component* mesh = GetComponent(ComponentType::MESH);
	
	if (mesh != nullptr && mesh->enabled) 
	{
		((ComponentMesh*)mesh)->Draw(shader, texture);
	}

	if (drawGOBBox) 
	{
		DrawBBox();
	}

	if (drawChildsBBox) 
	{
		for (auto& child : goChilds) 
		{
			child->DrawBBox();
		}
	}

	glUseProgram(0);
}

void GameObject::CleanUp() 
{
	for (auto& child : goChilds) 
	{
		child->CleanUp();
	}

}

void GameObject::DrawProperties() 
{
	assert(name != nullptr);

	ImGui::InputText("Name", (char*)name, 30.0f); ImGui::SameLine();
	ImGui::Checkbox("Enabled", &enabled);

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

std::string GameObject::GetFileFolder() const 
{
	std::string s(filePath);
	std::size_t found = s.find_last_of("/\\");
	s = s.substr(0, found + 1);
	return s;
}

Component* GameObject::AddComponent(ComponentType type) 
{
	Component* component = nullptr;

	switch (type) 
	{
	case ComponentType::CAMERA:
		break;

	case ComponentType::TRANSFORM:
		component = new ComponentTransform(this, aiMatrix4x4());
		transform = (ComponentTransform*)component;
		break;

	case  ComponentType::MESH:
		if (GetComponent(ComponentType::MESH) != nullptr)
		{
			LOG("CAUTION: The Game Object already has a mesh");
		}
		else
		{
			component = new ComponentMesh(this, nullptr);
		}
		break;

	case ComponentType::MATERIAL:
		component = new ComponentMaterial(this);
		break;

	case ComponentType::EMPTY:
	default:
		break;
	}

	components.push_back(component);

	return component;
}

void GameObject::RemoveComponent(Component* component) 
{
	assert(component != nullptr);

	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it) 
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
		return float4x4::identity;
	}

	return float4x4::FromTRS(transform->position, transform->rotation, transform->scale);
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

AABB GameObject::ComputeBBox() const 
{
	bbox.SetNegativeInfinity();

	// Current Game Object meshes
	for (const auto &mesh : GetComponents(ComponentType::MESH)) 
	{
		bbox.Enclose(((ComponentMesh *)mesh)->bbox);
		ComponentMesh* mesh = (ComponentMesh*)GetComponent(ComponentType::MESH);
		
		if (mesh != nullptr)
		{
			bbox.Enclose(mesh)->bbox;
		}
	}

	// Apply transformation of our Game Object
	bbox.TransformAsAABB(GetGlobalTransform());

	// Child meshes
	for (const auto &child : goChilds) 
	{
		if (child->GetComponents(ComponentType::MESH)) 
		{
			bbox.Enclose(child->ComputeBBox());
		}
	}

	return bbox;
}

void GameObject::DrawBBox() const 
{
	glUseProgram(App->program->basicProgram);
	AABB bbox = ComputeBBox();
	GLfloat vertices[] = {
		-0.5, -0.5, -0.5, 1.0,
		0.5, -0.5, -0.5, 1.0,
		0.5,  0.5, -0.5, 1.0,
		-0.5,  0.5, -0.5, 1.0,
		-0.5, -0.5,  0.5, 1.0,
		0.5, -0.5,  0.5, 1.0,
		0.5,  0.5,  0.5, 1.0,
		-0.5,  0.5,  0.5, 1.0,
	};

	GLuint vbo_vertices;
	glGenBuffers(1, &vbo_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort elements[] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 4, 1, 5,
		2, 6, 3, 7
	};

	GLuint ibo_elements;
	glGenBuffers(1, &ibo_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	math::float4x4 boxtransform = math::float4x4::FromTRS(bbox.CenterPoint(), Quat::identity, bbox.Size());
	glUniformMatrix4fv(glGetUniformLocation(App->program->basicProgram, "model"), 1, GL_TRUE, &(boxtransform)[0][0]);

	float color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
	glUniform4fv(glGetUniformLocation(App->program->basicProgram, "Vcolor"), 1, color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	glLineWidth(4.f);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
	glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, (GLvoid*)(4 * sizeof(GLushort)));
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_SHORT, (GLvoid*)(8 * sizeof(GLushort)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glLineWidth(1.0f);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo_vertices);
	glDeleteBuffers(1, &ibo_elements);
	glUseProgram(0);
}