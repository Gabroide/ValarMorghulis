#include "Application.h"
#include "ModuleCamera.h"
#include "DockScene.h"

// Constrctor
DockScene::DockScene() 
{

}

// Destructor
DockScene::~DockScene() 
{

}

void DockScene::Draw() 
{
	ImGui::Begin("Scene", &enabled, ImGuiWindowFlags_NoScrollbar);

	ImVec2 size = ImGui::GetWindowSize();
	ImGui::SetCursorPos(ImVec2(-(App->window->width - size.x) * 0.5f, -(App->window->height - size.y) * 0.5f));
	ImGui::Image((ImTextureID)App->camera->sceneCamera->renderTexture, { (float)App->window->width, (float)App->window->height }, { 0,1 }, { 1,0 });

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}

bool DockScene::IsFocused() const 
{ 
	
	return focus; 
}
