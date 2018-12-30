#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool			Init()			override;
	bool			CleanUp()		override;

	update_status	PreUpdate()		override;
	update_status	Update()		override;
	update_status	PostUpdate()	override;

	void WindowResized(unsigned width, unsigned height);

public:
	void* context;

};

#endif // __ModuleRender_h__