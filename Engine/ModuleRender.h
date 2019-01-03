#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"
#include "Globals.h"
#include "ModuleModel.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

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

	update_status	PreUpdate()		override;
	update_status	Update()		override;
	update_status	PostUpdate()	override;
	
	void			DrawGUI();
	void			InitFrustum();
	void			InitSDL();
	void			InitOpenGL();
	void			ViewMatrix(unsigned programUsed);
	void			ProjectionMatrix(unsigned programUsed);
	void			ModelTransform(unsigned programUsed);
	void			LookAt(math::float3& cameraPos, math::float3& target);
	void			SetScreenNewScreenSize();

private:
	void			DrawReferenceDebug();
	void			CreateFrameBuffer();

public:
	bool			vsyncEnabled	= false;

	float			bgColor[4]		= { 0.0f, 0.0f, 0.0f, 1.0f };
	
	unsigned		fbo				= 0;
	unsigned		rbo				= 0;
	unsigned		renderTexture	= 0;

	Frustum			frustum;
	
	math::float4x4	viewMatrix;
	
public:
	void*			context			= nullptr;
	
};

#endif // __ModuleRender_h__