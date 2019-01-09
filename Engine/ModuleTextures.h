#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include "Module.h"
#include "Globals.h"
#include "Model.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "IMGUI\imgui.h"

#include "DevIL\include\IL\ilut.h"

struct Texture
{
	int id = 0;
	int width = 0;
	int height = 0;
	Texture(int id, int width, int height) : id(id), width(width), height(height) {};
};

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool			Init() override;
	
	void			DrawGUI();
	void			LoadDefaultTexture();

public:
	Texture* const   Load(const char* path);
	
public:
	bool			mipmaping			= false;
	
	int				filterType			= GL_LINEAR;
	int				mipMapMode			= GL_NEAREST_MIPMAP_NEAREST;
	int				wrapMode			= GL_CLAMP;

public:
	Texture*		defaultTexture		= nullptr;
	Teture*			noCameraSelected	= nullptr;
};

#endif // __ModueTextures_h__