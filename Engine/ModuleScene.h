#ifndef __ModuleScene_h__
#define __ModuleScene_h__

#include "Module.h"

#include "MathGeoLib.h"

#include "SDL\include\SDL.h" // TODO: find out the real SDL library needed

#include "glew-2.1.0\include\GL\glew.h"

#include "Math\float3.h"
#include "Math\float4.h"
#include "Math\float4x4.h"
#include "Math\MathConstants.h"
#include "Math\MathFunc.h"
#include "Geometry\Frustum.h""
#include "MathGeoLib.h" // TODO

class ModuleScene : public Module
{
public:
	ModuleScene();
	~ModuleScene();

	bool            Init()		override;
	bool            CleanUp()	override;

	update_status   Update()	override;
	
	void			DrawReferenceGround();
	void			DrawReferenceAxis();

public:
	GLuint			texture0 = 0;

	math::float3	target;
	math::float3	eye;
	math::float3	up;

private:
	unsigned		vbo			= 0;

	GLuint			progDefault = GL_FALSE;
	GLuint			progTexture = GL_FALSE;

};

#endif // __ModuleScene_h__
