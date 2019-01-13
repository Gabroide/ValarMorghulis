#ifndef __ModuleWindow_h__
#define __ModuleWindow_h__

#include "Module.h"

#include "SDL\include\SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	virtual ~ModuleWindow();

	bool			Init()		override;
	bool			CleanUp()	override;

	void			DrawGUI();
	void			WindowResized(unsigned width, unsigned height);

public:
	bool			fullscreen		= false;
	bool			resizable		= true;
	bool			borderless		= false;
	
	int				width			= SCREEN_WIDTH;
	int				height			= SCREEN_HEIGHT;
	
	float			screenRatio		= SCREEN_WIDTH / SCREEN_HEIGHT;

public:
	SDL_Window*		window			= nullptr;
	SDL_Surface*	screen_surface	= nullptr;

};

#endif // __ModuleWindow_h__