#include "Application.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "DockHierarchy.h"
#include "GameObject.h"

#include "SDL\include\SDL_mouse.h"

// Constructor
DockHierarchy::DockHierarchy() 
{

}

// Destrucor
DockHierarchy::~DockHierarchy() 
{

}

void DockHierarchy::Draw() 
{
	if (!ImGui::Begin("Hierarchy", &enabled)) 
	{
		ImGui::End();
	
		return;
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN && ImGui::IsWindowHovered()) 
	{
		ImGui::OpenPopup("NewElement");
	}

	if (ImGui::BeginPopup("NewElement")) 
	{
		if (ImGui::Selectable("Add Empty GameObject")) 
		{
			App->scene->CreateGameObject();
		}
		
		ImGui::Separator();
		
		if (ImGui::Selectable("Camera")) 
		{
			App->scene->CreateCamera();
		}
		
		ImGui::EndPopup();
	}

	App->scene->DrawHierarchy();
	focused = ImGui::IsWindowFocused();
	ImGui::End();
}