#ifndef _ModuleDebugDraw_h__
#define _ModuleDebugDraw_h__

#include "Module.h"

class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

public:

	ModuleDebugDraw();
	~ModuleDebugDraw();

	bool            Init();
	update_status   Update();
	bool            CleanUp();

	void            Draw(Camera* camera, unsigned fbo, unsigned fb_width, unsigned fb_height);
private:

	static DDRenderInterfaceCoreGL* implementation;
};

#endif // __ModuleDebugDraw_h__
