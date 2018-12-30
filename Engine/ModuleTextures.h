#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include<list>

#include "Module.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

public:
	SDL_Texture* const Load(const char* path);

private:
	std::list<SDL_Texture*> textures;
};

#endif // __ModuleTextures_h__