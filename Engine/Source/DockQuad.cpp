#include "DockQuad.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"

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

	if (ImGui::Button("Enable Camera"))
	{
		App->camera->quadCamera->createFrameBuffer(ImGui::GetWindowWidth());
	}

	if (App->render->showQuad)
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
