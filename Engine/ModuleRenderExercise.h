#ifndef __ModuleRenderExercise_h__
#define __ModuleRenderExercise_h__

#include "Module.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool			Init();
	bool			CleanUp();

	update_status	Update()	override;

private:
	unsigned vbo = 0;;
};

#endif // __ModuleRenderExercise_h__