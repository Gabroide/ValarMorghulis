#ifndef __Application_h__
#define __Application_h__

#include<list>

#include "Globals.h"
#include "Module.h"
#include "Timer.h"

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

	bool				Init();
	bool				CleanUp();

	update_status		Update();
	
	void				PreUpdate();
	void				FinishUpdate();

public:
	ModuleRender*		renderer			= nullptr;
	ModuleWindow*		window				= nullptr;
	ModuleInput*		input				= nullptr;
	ModuleTextures*		textures			= nullptr;
	ModuleEditor*		editor				= nullptr;
	ModuleCamera*		camera				= nullptr;
	ModuleProgram*		program				= nullptr;
	ModuleTime*			time				= nullptr;
	ModuleModel*		model				= nullptr;

public:
	bool				gamePaused			= false;
	bool				gameModeEnabled		= false;
	bool				counting			= false;

	float				deltaTime			= 0.0f;
	float				gameDeltaTime		= 0.0f;

	int					frameRateCap		= 60;
	int					gameFrameRateCap	= 60;

	Timer				gameTime;

private:
	Timer				msTimer;
	
	std::list<Module*>	modules;

};

extern Application* App;

#endif // __Applicaton_h__