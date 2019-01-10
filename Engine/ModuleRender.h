#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"
#include "Globals.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_sdl.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
class ComponentCamera;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool			Init()			override;
	bool			CleanUp()		override;
	bool			Start();

	update_status	PreUpdate()		override;
	update_status	Update()		override;
	update_status	PostUpdate()	override;

	void			InitSDL();
	void			InitOpenGL() const;
	void			SetViewMatrix(ComponentCamera* camera) const;
	void			SetProjectionMatrix(ComponentCamera* camera) const;
	void			GenerateBlockUniforms();

private:
	void			DrawDebugData(ComponentCamera* camera);

public:
	bool			vsyncEnabled	= false;
	
	unsigned		ubo				= 0u;

public:
	void*			context			= nullptr;

protected:
	bool   showAxis					= true;
	bool   showGrid					= true;

};

#endif // __ModuleRender_h__
