#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleTextures.h"
#include "ModuleEditor.h"
#include "ModuleScene.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

// Constructor
ModuleEditor::ModuleEditor()
{
	docks.push_back(console = new DockConsole());
	docks.push_back(config = new DockConfig());
	docks.push_back(scene = new DockScene());
	docks.push_back(about = new DockAbout());
	docks.push_back(hierarchy = new DockHierarchy());
	docks.push_back(inspector = new DockInspector());
	docks.push_back(time = new DockTime());
	docks.push_back(camera = new DockCamera());
	docks.push_back(light = new DockLight());
}

// Destructor
ModuleEditor::~ModuleEditor() 
{
	
}

bool ModuleEditor::Init() 
{
	const char* glsl_version = "#version 130"; 

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::StyleColorsDark();

	return true;
}

update_status ModuleEditor::PreUpdate() 
{	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	CreateDockSpace();
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update() 
{
	ImGui::ShowDemoWindow();
	if (ImGui::BeginMainMenuBar()) 
	{
		if (ImGui::BeginMenu("App")) 
		{
			if (ImGui::MenuItem("New Scene"))
			{
				App->scene->ClearScene();
			}

			if (ImGui::MenuItem("Save scene"))
			{
				App->scene->SaveScene();
			}

			if (ImGui::MenuItem("Load Scene"))
			{
				App->scene->LoadScene();
			}

			if (ImGui::MenuItem("Exit"))
			{
				ImGui::EndMenu();
				ImGui::EndMainMenuBar();
				ImGui::End();
				ImGui::EndFrame();
			
				return UPDATE_STOP;
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Elements")) 
		{
			if (ImGui::BeginMenu("Select camera")) 
			{
				if (App->camera->gameCameras.size() == 0) 
				{
					ImGui::Text("No game cameras availables");
				}
				else
				{
					for (auto& camera : App->camera->gameCameras) 
					{
						if (ImGui::MenuItem(camera->goContainer->name, NULL, App->camera->selectedCamera == camera)) 
						{
							App->camera->selectedCamera = camera;
						}
					}
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Add new")) 
			{
				if(ImGui::MenuItem("Empty GameObject")) 
				{
					new GameObject(DEFAULT_GO_NAME, math::float4x4().identity, nullptr);
				}

				if (ImGui::MenuItem("Sphere")) 
				{
					GameObject* sphereGO = new GameObject("Sphere", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(sphereGO, GeometryType::SPHERE);
					App->scene->goSelected = sphereGO;
				}
				
				if (ImGui::MenuItem("Torus")) 
				{
					GameObject* torusGO = new GameObject("Torus", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(torusGO, GeometryType::TORUS);
					App->scene->goSelected = torusGO;
				}

				if (ImGui::MenuItem("Cube")) 
				{
					GameObject* cubeGO = new GameObject("Cube", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(cubeGO, GeometryType::CUBE);
					App->scene->goSelected = cubeGO;
				}

				if (ImGui::MenuItem("Plane")) 
				{
					GameObject* planeGO = new GameObject("Plane", math::float4x4().identity, App->scene->goSelected);
					App->scene->LoadGeometry(planeGO, GeometryType::PLANE);
					App->scene->goSelected = planeGO;
				}


				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window")) 
		{
			if (ImGui::MenuItem("Scene", NULL, scene->IsEnabled())) 
			{
				scene->ToggleEnabled();
			}

			if (ImGui::MenuItem("Game", NULL, camera->IsEnabled())) 
			{
				camera->ToggleEnabled();
			}

			if (ImGui::MenuItem("Hierarchy", NULL, hierarchy->IsEnabled())) 
			{
				hierarchy->ToggleEnabled();
			}

			if (ImGui::MenuItem("Lights", NULL, light->IsEnabled())) 
			{
				light->ToggleEnabled();
			}

			if ("Assets", NULL, assets->IsEnabled())
			{
				assets->ToggleEnabled();
			}

			if (ImGui::MenuItem("Time", NULL, time->IsEnabled()))
			{
				time->ToggleEnabled();
			}

			if (ImGui::MenuItem("Logs", NULL, console->IsEnabled())) 
			{
				console->ToggleEnabled();
			} 

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help")) 
		{
			if (ImGui::MenuItem("About")) 
			{
				about->ToggleEnabled();
			}
			
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	PrintDocks();

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleEditor::RenderGUI() 
{
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ModuleEditor::PrintDocks() 
{
	for (std::list<Dock*>::iterator it = docks.begin(); it != docks.end(); ++it)
	{
		if ((*it)->IsEnabled())
		{
			(*it)->Draw();
		}
	}
}

void ModuleEditor::CreateDockSpace()
{
	ImGui::SetNextWindowPos({ 0,0 });
	ImGui::SetNextWindowSize({ (float)App->window->width, (float)App->window->height });
	ImGui::SetNextWindowBgAlpha(0.0f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoMove;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("DockSpace", NULL, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
}

bool ModuleEditor::SceneFocused() const 
{

	return scene->IsFocused();
}

void ModuleEditor::ProcessInputEvent(SDL_Event* event) const 
{
	ImGui_ImplSDL2_ProcessEvent(event);
}

void ModuleEditor::AddFPSCount(float fps, float ms) const 
{
	config->AddFps(fps, ms);
}

void ModuleEditor::AddGameFPSCount(float fps, float ms) const 
{
	config->AddGameFps(fps, ms);
}