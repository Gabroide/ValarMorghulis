#ifndef __ModuleWindow_h__
#define __ModuleWindow_h__

#include "Module.h"

#include "SDL\include\SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool			Init()		override;

	// Called before quitting
	bool			CleanUp()	override;

	void			WindowResized(unsigned width, unsigned height);

public:
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;
};

#endif // __ModuleWindow_h__