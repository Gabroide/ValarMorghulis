#ifndef __ModuleTextures_h__
#define __ModuleTextures_h__

#include<list>

#include "Module.h"
#include "Globals.h"

#include "SDL\include\SDL.h" // TODO: Try to reduce SDL.
#include "SDL_image\include\SDL_image.h"

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

	unsigned	 	Load(const char* path);

	void			ReloadTexture(const char* newPath, unsigned texture);
	void			Unload(unsigned texture);
	void			SetNewParameter(const char* newPath, unsigned texture, unsigned newTextFilter, unsigned newResizeMethod, unsigned newWrapMethod, unsigned newClampMethod);
	void			SwitchMipMaps(const char* newPath, unsigned texture, bool state);

public:
	bool			generateMipMaps = false;

	unsigned		textFilter = 0;
	unsigned		resizeMethod = 0;
	unsigned		wrapMethod = 0;
	unsigned		clampMethod = 0;
		
public:
	char*		imgFormat;

};

#endif // __ModueTextures_h__