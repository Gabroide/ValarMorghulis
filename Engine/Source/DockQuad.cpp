#include "DockQuad.h"
#include "Application.h"
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

	focus = ImGui::IsWindowFocused();
	ImGui::End();
}

bool DockQuad::IsFocused() const 
{
	
	return focus;
}
