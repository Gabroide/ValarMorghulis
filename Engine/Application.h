#ifndef __Application_h__
#define __Application_h__

#include<list>

#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleEditor;
class ModuleCamera;
class ModuleInput;
class ModuleScene;
class ModuleShader;

class Application
{
public:

	Application();
	~Application();

	bool			Init();
	bool			CleanUp();

	update_status	Update();
	
	void			Tick();

public:
	ModuleRender*	renderer		= nullptr;
	ModuleWindow*	window			= nullptr;
	ModuleTextures*	textures		= nullptr;
	ModuleEditor*	editor			= nullptr;
	ModuleCamera*	camera			= nullptr;
	ModuleInput*	input			= nullptr;
	ModuleScene*	scene			= nullptr;
	ModuleShader*	shader			= nullptr;

public:
	float			lastTickTime	= 0.0f;
	float			deltaTime		= 0.0f;
	float			auxTimer		= 0.0f;
	
	int				frameCounter	= 0;
	int				FPS				= 0;

private:
	std::list<Module*> modules;

};

extern Application* App;

#endif // __Applicaton_h__