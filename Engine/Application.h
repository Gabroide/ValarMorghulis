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
class ModuleProgram;
class ModuleTime;
class ModuleModel;

class Application
{
public:

	Application();
	~Application();

	bool			Init();
	bool			CleanUp();

	update_status	Update();
	
public:
	ModuleRender*	renderer	= nullptr;
	ModuleWindow*	window		= nullptr;
	ModuleInput*	input		= nullptr;
	ModuleTextures*	textures	= nullptr;
	ModuleEditor*	editor		= nullptr;
	ModuleCamera*	camera		= nullptr;
	ModuleProgram*	program		= nullptr;
	ModuleTime*		time		= nullptr;
	ModuleModel*	model		= nullptr;

private:
	std::list<Module*> modules;

};

extern Application* App;

#endif // __Applicaton_h__