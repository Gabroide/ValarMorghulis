#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleWindow.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

ModuleRenderExercise::ModuleRenderExercise()
{

}

ModuleRenderExercise::~ModuleRenderExercise()
{

}

bool ModuleRenderExercise::Init()
{
	float vertex_buffer_data[] = {
		-1.0f , -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
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

	glDrawArrays(GL_TRIANGLES, 0, 3);	// starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
	}

	return true;
}