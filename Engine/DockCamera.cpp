#include "DockCamera.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"

// Constructor
DockCamera::DockCamera()
{
	
}

// Destructor
DockCamera::~DockCamera()
{
	
}

void DockCamera::Draw() 
{
	ImGui::Begin("Game", &enabled, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetCursorPos(ImVec2(-(App->window->width - size.x) * 0.5f, -(App->window->height - size.y) * 0.5f));

	if (App->camera->selectedCamera != nullptr) 
	{
		ImGui::Image((ImTextureID)App->camera->selectedCamera->renderTexture, { (float)App->camera->selectedCamera->screenWidth, (float)App->camera->selectedCamera->screenHeight }, { 0,1 }, { 1,0 });
	}
}

bool DockCamera::IsFocused() const 
{
	
	return focus;
}
