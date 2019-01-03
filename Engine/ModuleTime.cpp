#include "ModuleTime.h"

#include "SDL\include\SDL.h"

// Constructor
ModuleTime::ModuleTime() 
{
	
}

// Destructor
ModuleTime::~ModuleTime() 
{
	
}

update_status ModuleTime::PreUpdate() 
{
	float currentFrame = SDL_GetTicks();
	deltaTime = (currentFrame - lastFrame) * 0.001f;
	lastFrame = currentFrame;

	return UPDATE_CONTINUE;
}
