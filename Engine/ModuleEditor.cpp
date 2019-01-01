﻿#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModuleRenderExercise.h"
#include "ModuleEditor.h"

#include "SDL\include\SDL.h" // TODO: search the SDL

static void ShowMenuBar();
static void ShowAbout();
static void ShowHardware();
static void ShowSceneConfig();
static void ShowTextureConfig();
static void PrintTextureParams(const char* currentTexture);
static void PrintMipMapOption(const char* currentTexture);

// Constructor
ModuleEditor::ModuleEditor()
{

}

// Destructor
ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init() 
{
	const char* glsl_version = "#version 130";

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
																//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
																//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup style
	ImGui::StyleColorsDark();

	return true;
}

update_status ModuleEditor::PreUpdate() 
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{

	ImGui::ShowDemoWindow();
	ShowMenuBar();

	if (showAboutMenu) 
	{
		ShowAbout();
	}

	if (showHardwareMenu) 
	{
		ShowHardware();
	}

	if (showSceneConfig) 
	{
		ShowSceneConfig();
	}

	if (showTextureConfig) 
	{
		ShowTextureConfig();
	}

	if (requestedExit)
	{
	
		return UPDATE_STOP;
	}

	return UPDATE_CONTINUE;
}

void ModuleEditor::HandleInputs(SDL_Event& event) 
{
	ImGui_ImplSDL2_ProcessEvent(&event);
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

// General menu options
static void ShowMenuBar() 
{
	if (ImGui::BeginMainMenuBar()) 
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit")) 
			{ 
				App->editor->requestedExit = true;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Scene"))
		{
			if (ImGui::MenuItem("Configuration")) 
			{ 
				App->editor->showSceneConfig = true; 
			}
			
			if (ImGui::MenuItem("Textures")) 
			{ 
				App->editor->showTextureConfig = true; 
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) 
		{
			if (ImGui::MenuItem("Hardware")) 
			{ 
				App->editor->showHardwareMenu = true; 
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) 
		{
			if (ImGui::MenuItem("About")) 
			{ 
				App->editor->showAboutMenu = true; 
			}

			ImGui::EndMenu();
		}
	}

	ImGui::EndMainMenuBar();
}

// About
static void ShowAbout() 
{
	const char* MITLicense = "Copyright 2018 - QTEngine \n\nPermission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions";

	ImGui::Begin("About", &App->editor->showAboutMenu);

	ImGui::Text(TITLE);
	ImGui::Text("C++/C engine for game development");
	ImGui::Separator();
	ImGui::Text("Libraries:");
	
	if (ImGui::MenuItem("SDL v2.0.8")) 
	{ 
		ShellExecute(0, 0, "https://www.libsdl.org/index.php", 0, 0, SW_SHOW); 
	}

	if (ImGui::MenuItem("Glew v2.1.0")) 
	{ 
		ShellExecute(0, 0, "http://glew.sourceforge.net/", 0, 0, SW_SHOW); 
	}

	if (ImGui::MenuItem("ImGui v1.66"))
	{ 
		ShellExecute(0, 0, "https://github.com/ocornut/imgui/tree/docking", 0, 0, SW_SHOW);
	}

	ImGui::Separator();
	ImGui::Text("Author's Repository:");
	if (ImGui::MenuItem("Alfonso Mestres")) 
	{ 
		ShellExecute(0, 0, "https://github.com/Gabroide/", 0, 0, SW_SHOW); 
	}

	ImGui::Separator();
	ImGui::TextWrapped(MITLicense);
	ImGui::End();
}

// Hardware
static void ShowHardware() 
{
	ImGui::Begin("Hardware specs", &App->editor->showHardwareMenu);
	ImGui::Text("CPU Count: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.5f, 1.0f, 1.0f), "%d", SDL_GetCPUCount());
	ImGui::Text("System RAM: "); ImGui::SameLine(); ImGui::TextColored(ImVec4(0.8f, 0.5f, 1.0f, 1.0f), "%d", SDL_GetSystemRAM());
	ImGui::End();
}

// Scene config
static void ShowSceneConfig() 
{
	ImGui::Begin("Camera", &App->editor->showSceneConfig);
	ImGui::InputFloat("ms", &App->deltaTime);
	ImGui::InputInt("FPS", &App->FPS, 0, 0);
	
	float forward[3] = { App->camera->cameraFront.x, App->camera->cameraFront.y, App->camera->cameraFront.z };
	ImGui::InputFloat3("Front", forward, "%.3f");
	
	float up[3] = { App->camera->cameraUp.x, App->camera->cameraUp.y, App->camera->cameraUp.z };
	ImGui::InputFloat3("Up", up, "%.3f");
	
	float eye[3] = { App->camera->cameraPos.x, App->camera->cameraPos.y, App->camera->cameraPos.z };
	ImGui::InputFloat3("Position", eye, "%.3f");
	ImGui::Separator();
	ImGui::SliderFloat("Mov Speed", &App->camera->cameraSpeed, 0.0f, 100.0f);
	ImGui::SliderFloat("Rot Speed", &App->camera->rotationSpeed, 0.0f, 100.0f);
	ImGui::SliderFloat("Mouse Sens", &App->camera->mouseSensitivity, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::SliderFloat("Near Plane", &App->camera->frustum.nearPlaneDistance, 0.1f, App->camera->frustum.farPlaneDistance);
	ImGui::SliderFloat("Far Plane", &App->camera->frustum.farPlaneDistance, 0.1f, 1000.0f);
	
	ImGui::SliderFloat("Hotizontal FOV", &App->camera->frustum.horizontalFov, 0.01f, 1.0f);
	ImGui::SliderFloat("Vertical FOV", &App->camera->frustum.verticalFov, 0.01f, 1.0f);
	ImGui::InputFloat("AspectRatio", &App->camera->screenRatio, 0, 0, "%.3f");
	ImGui::Separator();
	ImGui::SliderFloat3("Background color", App->renderer->bgColor, 0.0f, 1.0f);
	ImGui::End();
}

//Texture config
static void ShowTextureConfig() 
{
	ImGui::Begin("Textures", &App->editor->showTextureConfig);
	const char* items[] = { "./textures/Lenna.png", "./textures/Lennin.dds", "./textures/Lolnope.jpg", "./textures/Lolyes.gif" };
	static const char* current_item = items[0];
	
	if (ImGui::BeginCombo("Available textures", current_item, ImGuiComboFlags_NoArrowButton))
	{
		for (int n = 0; n < IM_ARRAYSIZE(items); n++)
		{
			bool is_selected = (current_item == items[n]);
			
			if (ImGui::Selectable(items[n], is_selected)) {
				current_item = items[n];
				App->textures->ReloadTexture(items[n], App->exercise->texture0);
			}
		
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	ImGui::Separator();
	ImGui::Text(App->textures->imgFormat); ImGui::SameLine(); ImGui::Text("Format");
	ImGui::InputInt("Width", &App->textures->imgWidth, 0, 0);
	ImGui::InputInt("Height", &App->textures->imgHeight, 0, 0);
	ImGui::InputInt("Pixel depth", &App->textures->imgPixelDepth, 0, 0);
	ImGui::Separator();
	PrintMipMapOption(current_item);
	ImGui::Separator();
	PrintTextureParams(current_item);
	ImGui::End();
}

// Texture functions
static void PrintTextureParams(const char* currentTexture) 
{
	
	const char* wrapMethods[] = { "GL_TEXTURE_WRAP_R", "GL_TEXTURE_WRAP_S", "GL_TEXTURE_WRAP_T" };
	const int wrapMethodsValues[] = { GL_TEXTURE_WRAP_R, GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T };
	static const char* currentWrap = wrapMethods[0];
	
	if (ImGui::BeginCombo("Wrap methods", currentWrap, ImGuiComboFlags_NoArrowButton))
	{
		for (int wr = 0; wr < IM_ARRAYSIZE(wrapMethods); wr++)
		{
			bool wrapSelected = (currentWrap == wrapMethods[wr]);
			
			if (ImGui::Selectable(wrapMethods[wr], wrapSelected)) 
			{
				currentWrap = wrapMethods[wr];
				App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, App->textures->resizeMethod, wrapMethodsValues[wr], App->textures->clampMethod);
			}
			if (wrapSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	
	ImGui::Separator();
	
	const char* resizeMethods[] = { "Linear", "Nearest" };
	const int resizeMethodsValues[] = { GL_LINEAR, GL_NEAREST };
	static const char* currentResize = resizeMethods[0];
	
	if (ImGui::BeginCombo("Resize methods", currentResize, ImGuiComboFlags_NoArrowButton))
	{
		for (int rs = 0; rs < IM_ARRAYSIZE(resizeMethods); rs++)
		{
			bool resizeSelected = (currentResize == resizeMethods[rs]);
			
			if (ImGui::Selectable(resizeMethods[rs], resizeSelected)) 
			{
				currentResize = resizeMethods[rs];
				App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, resizeMethodsValues[rs], App->textures->wrapMethod, App->textures->clampMethod);
			}
	
			if (resizeSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
	}
	
		ImGui::EndCombo();
	}
	
	ImGui::Separator();
	
	const char* clampMethods[] = { "GL_CLAMP", "GL_CLAMP_TO_BORDER", "GL_REPEAT", "GL_MIRRORED_REPEAT" };
	const int clampMethodsValues[] = { GL_CLAMP, GL_CLAMP_TO_BORDER, GL_REPEAT, GL_MIRRORED_REPEAT };
	static const char* currentClamp = clampMethods[0];
	
	if (ImGui::BeginCombo("Clamp methods", currentClamp, ImGuiComboFlags_NoArrowButton))
	{
		for (int cl = 0; cl < IM_ARRAYSIZE(clampMethods); cl++)
		{
			bool clampSelected = (currentClamp == clampMethods[cl]);
			
			if (ImGui::Selectable(clampMethods[cl], clampSelected)) 
			{
				currentClamp = clampMethods[cl];
				App->textures->SetNewParameter(currentTexture, App->exercise->texture0, App->textures->textFilter, App->textures->resizeMethod, App->textures->wrapMethod, clampMethodsValues[cl]);
			}

			if (clampSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
	
		ImGui::EndCombo();
	}
	
	ImGui::Separator();
	
	const char* filterMethods[] = { "GL_TEXTURE_MIN_FILTER", "GL_TEXTURE_MAG_FILTER" };
	const int filterMethodsValues[] = { GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER };
	static const char* currentFilter = filterMethods[0];
	
	if (ImGui::BeginCombo("Filter methods", currentFilter, ImGuiComboFlags_NoArrowButton))
	{
		for (int fl = 0; fl < IM_ARRAYSIZE(filterMethods); fl++)
		{
			bool filterSelected = (currentFilter == filterMethods[fl]);
			
			if (ImGui::Selectable(filterMethods[fl], filterSelected)) 
			{
				currentFilter = filterMethods[fl];
				App->textures->SetNewParameter(currentTexture, App->exercise->texture0, filterMethodsValues[fl], App->textures->resizeMethod, App->textures->wrapMethod, App->textures->clampMethod);
			}

			if (filterSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}

static void PrintMipMapOption(const char* currentTexture) 
{
	const char* mipMapState[] = { "Disabled", "Enabled" };
	bool valueMipMapValue[] = { false, true };
	static const char* currentMMState = mipMapState[0];
	
	if (ImGui::BeginCombo("MipMap", currentMMState, ImGuiComboFlags_NoArrowButton))
	{
		for (int mm = 0; mm < IM_ARRAYSIZE(mipMapState); mm++)
		{
			bool is_selected = (currentMMState == mipMapState[mm]);
			
			if (ImGui::Selectable(mipMapState[mm], is_selected)) 
			{
				currentMMState = mipMapState[mm];
				App->textures->SwitchMipMaps(currentTexture, App->exercise->texture0, valueMipMapValue[mm]);
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}