#ifndef _ModuleDebugDraw_h__
#define _ModuleDebugDraw_h__

#include "Module.h"
#include "ComponentCamera.h"

class DDRenderInterfaceCoreGL;
class Camera;

class ModuleDebugDraw : public Module
{

public:

	ModuleDebugDraw();
	~ModuleDebugDraw();

	bool            Init()		override;
	bool            CleanUp()	override;

	update_status   Update()	override;

	void            Draw(ComponentCamera* camera, unsigned fbo, unsigned fb_width, unsigned fb_height);

private:
	static DDRenderInterfaceCoreGL* implementation;
};

#endif // __ModuleDebugDraw_h__
