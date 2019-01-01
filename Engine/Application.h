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
class ModuleRenderExercise;
class ModuleShader;

class Application
{
public:

	Application();
	~Application();

	bool			Init();
	bool			CleanUp();

	void			Tick();

	update_status	Update();

public:
	ModuleRender*			renderer	= nullptr;
	ModuleWindow*			window		= nullptr;
	ModuleTextures*			textures	= nullptr;
	ModuleEditor*			editor		= nullptr;
	ModuleCamera*			camera		= nullptr;
	ModuleInput*			input		= nullptr;
	ModuleRenderExercise*	exercise	= nullptr;
	ModuleShader*			shader		= nullptr;

public:
	float	lastTickTime	= 0;
	float	deltaTime		= 0;
	float	auxTimer		= 0;

	int		FPS				= 0;
	int		frameCounter	= 0;
	
private:
	std::list<Module*> modules;

};

extern Application* App;

#endif // __Applicaton_h__