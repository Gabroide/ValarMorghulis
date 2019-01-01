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

	void			ReloadTexture(const char* newPath, GLuint& texture);
	void			SetNewParameter(const char* newPath, GLuint& texture, GLuint newTextFilter, GLuint newResizeMethod, GLuint newWrapMethod, GLuint newClampMethod);
	void			SwitchMipMaps(const char* newPath, GLuint& texture, bool state);

	GLuint const	Load(const char* path);

public:
	bool	generateMipMaps = false;

	int		imgWidth;
	int		imgHeight;
	int		imgPixelDepth;
	
	GLuint	textFilter		= 0;
	GLuint	resizeMethod	= 0;
	GLuint	wrapMethod		= 0;
	GLuint	clampMethod		= 0;

public:
	const char* currentPathLoaded;
	char*		imgFormat;

};

#endif // __ModueTextures_h__