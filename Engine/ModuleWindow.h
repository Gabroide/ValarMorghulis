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

	bool Init();
	bool CleanUp();

public:
	SDL_Window* window = NULL;
	SDL_Surface* screen_surface = NULL;

};

#endif // __ModuleWindow_H__