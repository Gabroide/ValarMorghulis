#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include<list>

#include "Module.h"
#include "Globals.h"

#include "SDL\include\SDL.h" // TODO: Try to reduce SDL.h

#include "glew-2.1.0\include\GL\glew.h"

#include "DevIL\include\IL\il.h"
#include "DevIL\include\IL\ilut.h"
#include "DevIL\include\IL\ilu.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool			Init()		override;
	bool			CleanUp()	override;

	GLuint const	Load(const char* path);

public:
	SDL_Texture* const	Load(const char* path);

private:
	std::list<SDL_Texture*> textures;

};

#endif // __ModueTextures_h__