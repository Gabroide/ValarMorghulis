#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include "Module.h"
#include "Globals.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "IMGUI\imgui.h"

#include "DevIL\include\IL\ilut.h"

struct Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool			Init() override;
	
	void			DrawGUI();

	Texture const   Load(const char* path);
	
public:
	bool			anisotropic_filter	= false;
	bool			mipmaping			= false;

	int				pixelDepth			= 0;
	int				height				= 0;
	int				format				= 0;
	int				width				= 0;
	int				filterType			= GL_LINEAR;
	int				wrapMode			= 0;

};

#endif // __ModueTextures_h__