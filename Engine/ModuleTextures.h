#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include "Module.h"
#include "Globals.h"
#include "Model.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "IMGUI\imgui.h"

#include "DevIL\include\IL\ilut.h"

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool			Init() override;
	
	void			DrawGUI();
	void			CreateComponentTexture();

public:
	Texture* const   Load(const char* path);
	
public:
	bool			mipmaping			= false;
	
	int				filterType			= GL_LINEAR;
	int				mipMapMode			= GL_NEAREST_MIPMAP_NEAREST;
	int				wrapMode			= GL_CLAMP;

};

#endif // __ModueTextures_h__