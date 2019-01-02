#ifndef __ModuleRender_h__
#define __ModuleRender_h__

#include "Module.h"
#include "Globals.h"
#include "ModuleModelLoader.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "SDL\include\SDL.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_sdl.h"

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

	void			RenderMesh(const ModuleModelLoader::Mesh& mesh, const ModuleModelLoader::Material& material, unsigned program, const math::float4x4& model, const math::float4x4& view, const math::float4x4& proj);

public:
	unsigned		program0;
	unsigned		program1;

public:
	void*			context;

private:
	void			DrawReferenceDebug(unsigned program, const math::float4x4& model, const math::float4x4& view, const math::float4x4& proj);

};

#endif // __ModuleRender_h__