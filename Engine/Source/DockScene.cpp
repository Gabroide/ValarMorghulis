#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "DockScene.h"

#include "ImGuizmo\ImGuizmo.h"

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

	winSize = ImGui::GetWindowSize();
	ImVec2 pos = ImGui::GetWindowPos();
	
	viewport.x = ImGui::GetCursorPosX() + pos.x;
	viewport.y = ImGui::GetCursorPosY() + pos.y;

	ImGui::Image((ImTextureID)App->camera->sceneCamera->renderTexture, winSize, { 0,1 }, { 1,0 });
	App->renderer->DrawImGuizmo(winSize.x, winSize.y, pos.x, pos.y);

	App->camera->sceneFocused == ImGui::IsMouseHoveringWindow();

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}

bool DockScene::IsFocused() const 
{ 
	
	return focus; 
}
