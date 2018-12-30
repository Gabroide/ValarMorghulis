#ifndef __Application_h__
#define __Application_h__

#include <list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleEditor;
class ModuleInput;
class ModuleRenderExercise;
class ModuleShader;

class Application
{
public:
	Application();
	~Application();

	bool			Init();
	bool			CleanUp();

	update_status	Update();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleShader* shader = nullptr;

private:
	std::list<Module*>	modules;

};

extern Application* App;

#endif // __Applicaton_h__