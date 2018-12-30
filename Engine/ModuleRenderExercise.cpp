#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"
#include "ModuleShader.h"

ModuleRenderExercise::ModuleRenderExercise()
{

}

ModuleRenderExercise::~ModuleRenderExercise()
{

}

bool ModuleRenderExercise::Init()
{
	InitFrustum();
		
	program = App->shader->LoadShaders("./default.vs", "./default.fs");
	
	if (!program)
	{
		LOG("Error: Program cannot be compiled");

		return false;
	}

	glUseProgram(program);

	float vboData[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vboData), vboData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

update_status ModuleRenderExercise::Update()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(
		0,					// attribute 0
		3,					// number of componente (3 floats)
		GL_FLOAT,			//	data type
		GL_FALSE,			// should be normalize
		0,					// stride
		(void*)0			// aarray buffer offset
	);

	// Use shaders loaders
	glUseProgram(program);

	// Fragments
	int fragUnifLocation = glGetUniformLocation(program, "newColor");
	float color[4] = { 0.5f, 1.0f,0.0f, 1.0f };
	glUniform4fv(fragUnifLocation, 1, color);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

math::float4x4 ModuleRenderExercise::ProjectionMatrix()
{
	math::float4x4 projectMatrix;
	projectMatrix = frustum.ProjectionMatrix();

	return projectMatrix;
}

bool ModuleRenderExercise::CleanUp()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
	}

	return true;
}

math::float4x4 ModuleRenderExercise::LookAt(math::float3 & target, math::float3& eye, math::float3& up)
{
	math::float4x4 matrix;

	math::float3 f(target - eye);
	f.Normalize();
	math::float3 s(f.Cross(up));
	s.Normalize();
	math::float3 u(s.Cross(f));

	matrix[0][0] = s.x;			matrix[0][1] = s.y;			matrix[0][2] = s.z;
	matrix[1][0] = u.x;			matrix[1][1] = u.y;			matrix[1][2] = u.z;
	matrix[2][0] = -f.x;		matrix[2][1] = -f.y;		matrix[2][2] = -f.z;
	matrix[0][3] = -s.Dot(eye);	matrix[1][3] = -u.Dot(eye);	matrix[2][3] = -f.Dot(eye);
	matrix[3][0] = 0.0f;		matrix[3][1] = 0.0f;		matrix[3][2] = 0.0f;		matrix[3][3] = 1.0f;

	return matrix;
}

void ModuleRenderExercise::InitFrustum()
{
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::pi / 4.0f;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov * 0.5f) * (SCREEN_WIDTH / SCREEN_HEIGHT));
}

bool ModuleRenderExercise::CleanUp()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
	}

	return true;
}