#include "DockHierarchy.h"
#include "Application.h"
#include "ModuleScene.h"
#include "GameObject.h"

// Constructor
DockHierarchy::DockHierarchy() 
{
	
}

// Destructor
DockHierarchy::~DockHierarchy() 
{
	
}

void DockHierarchy::Draw() 
{
	if (!ImGui::Begin("Hierarchy", &enabled)) {
		ImGui::End();
		return;
	}

	App->scene->DrawHierarchy();
	focused = ImGui::IsWindowFocused();
	ImGui::End();
}