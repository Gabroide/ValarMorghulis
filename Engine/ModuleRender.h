#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"
#include "Globals.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"


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
	
	void			DrawGUI();
	void			InitFrustum();
	void			InitSDL();
	void			InitOpenGL();
	void			ViewMatrix();
	void			ProjectionMatrix();
	void			SetScreenNewScreenSize();
	void			DrawDebugData();
	void			CreateUniformBlocks();

	math::float4x4	LookAt(math::float3& cameraPos, math::float3& target);

private:
	void			DrawReferenceDebug();
	void			CreateFrameBuffer();
	void			DrawDebugData();

public:
	bool			vsyncEnabled	= false;

	float			bgColor[4]		= { 0.0f, 0.0f, 0.0f, 1.0f };
	
	unsigned		fbo				= 0u;
	unsigned		rbo				= 0u;
	unsigned		ubo				= 0u;
	unsigned		renderTexture	= 0u;

public:
	void*			context			= nullptr;
	
protected:
	bool			showAxis		= true;
	bool			showGrid		= true;

protected:
	bool			showAxis		= true;
	bool			showGrid		= true;

};

#endif // __ModuleRender_h__