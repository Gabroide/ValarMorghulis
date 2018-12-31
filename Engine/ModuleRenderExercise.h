#ifndef __ModuleRenderExercise_h__
#define __ModuleRenderExercise_h__

#include "Module.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "Math\float3.h"
#include "Math\float4.h"
#include "Math\float4x4.h"
#include "Math\MathConstants.h"
#include "Math\MathFunc.h"
#include "Geometry\Frustum.h""

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool			Init()		override;
	bool			CleanUp()	override;

	void			DrawReferenceGround();
	void			DrawReferenceAxis();

	update_status	Update()	override;

public:
	math::float3	target;
	math::float3	eye;
	math::float3	up;

private:
	unsigned		vbo		=	0;

	GLuint			progDefault = GL_FALSE;
	GLuint			progTexture = GL_FALSE;
	GLuint			texture0 = 0;

};

#endif // __ModuleRenderExercise_h__