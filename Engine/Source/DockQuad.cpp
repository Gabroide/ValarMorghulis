#include "DockQuad.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

// Constructor
DockQuad::DockQuad() 
{

}

// Destructor
DockQuad::~DockQuad() 
{

}

void DockQuad::Draw() 
{
	if (!ImGui::Begin("QuadTree", &enabled)) 
	{
		ImGui::End();
	
		return;
	}

	ImGui::Checkbox("Draw", &App->renderer->showQuad);

	if (App->renderer->showQuad) 
	{
		if (App->camera->quadCamera != nullptr) 
		{
			ImGui::Image((ImTextureID)App->camera->quadCamera->renderTexture, { ImGui::GetWindowWidth(), ImGui::GetWindowWidth() }, { 0,1 }, { 1,0 });
		}
	}

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}

bool DockQuad::IsFocused() const 
{
	return focus; 
}
