#include "Application.h"
#include "ModuleScene.h"
#include "Component.h"
#include "DockLight.h"


// Constructor
DockLight::DockLight() 
{

}

// Destructor
DockLight::~DockLight() 
{

}

void DockLight::Draw() 
{
	ImGui::Begin("Lights", &enabled, ImGuiWindowFlags_NoScrollbar);
	
	ImGui::Text("Ambient");
	ImGui::Separator();
	ImGui::SliderFloat("Intensity", &App->scene->ambientLight, 0.0f, 1.0f);
	ImGui::Text("Position");
	ImGui::DragFloat3("", (float*)&App->scene->lightPosition, 0.25f, -500.f, 500.f);

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}

bool DockLight::IsFocused() const 
{ 

	return focus; 
}
