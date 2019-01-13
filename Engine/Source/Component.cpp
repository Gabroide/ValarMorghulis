#include "Application.h"
#include "Component.h"
#include "GameObject.h"
#include "ModuleFileSystem.h"

// Construcor
Component::Component(GameObject* gameObject, ComponentType type) 
{
	sprintf_s(uuid, App->fileSystem->NewGuuid());
	
	if (gameObject != nullptr) 
	{
		sprintf_s(parentUuid, gameObject->uuid);
		goContainer = gameObject;
	}

	componentType = type;
}

// Constructor Overloaded
Component::Component(const Component& duplicateComponent) 
{
	sprintf_s(uuid, App->fileSystem->NewGuuid());
	sprintf_s(parentUuid, duplicateComponent.parentUuid);
	goContainer = duplicateComponent.goContainer;
	componentType = duplicateComponent.componentType;
	enabled = duplicateComponent.enabled;
}

// Destructor
Component::~Component() 
{

}

void Component::Update() 
{

}

bool Component::DrawComponentState() 
{
	ImGui::Checkbox("Active", &enabled); ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.8f, 0.8f));

	bool removed = ImGui::SmallButton("Remove Component");

	ImGui::Text("UUID: "); ImGui::SameLine();
	ImGui::TextColored({ 0.4f,0.4f,0.4f,1.0f }, uuid);
	
	if (removed) 
	{
		toBeDeleted = true;
	}

	ImGui::PopStyleColor(3);

	return removed;
}
