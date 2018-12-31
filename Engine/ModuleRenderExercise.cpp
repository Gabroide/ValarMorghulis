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

	// Editor references
	DrawReferenceGround();
	DrawReferenceAis();

	// Fragments
	int fragUnifLocation = glGetUniformLocation(program, "newColor");
	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glUniform4fv(fragUnifLocation, 1, color);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_TRUE, &Model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, &App->camera->LookAt(App->camera->target, App->camera->eye, App->camera->up)[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "proj"), 1, GL_TRUE, &App->camera->ProjectionMatrix()[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return UPDATE_CONTINUE;
}

math::float4x4 ModuleRenderExercise::DrawReferenceGround()
{
	glLineWidth(1.0f);
	float d = 200.0f;
	glBegin(GL_LINES);

	for (float i = -d; i <= d; ++i)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();
}

void ModuleRenderExercise:: DrawReferenceAxis()
{
	glLineWidth(2.0f);

	// red x
	int xAxis = glGetUniformLocation(program, "newColor");
	float red[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glUniform4fv(xAxis, 1, red);

	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f);
	glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f);
	glVertex3f(1.0f, -0.1f, 0.0f);
	glEnd();

	// green y
	int yAxis = glGetUniformLocation(program, "newColor");
	float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glUniform4fv(yAxis, 1, green);

	glBegin(GL_LINES);
	glVertex4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.05f, 0.0f);
	glEnd();

	// blue z
	int zAxis = glGetUniformLocation(program, "newColor");
	float green[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glUniform4fv(zAxis, 1, blue);

	glBegin(GL_LINES);
	glVertex4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(0.05f, -0.1f, 1.05f);
	glEnd();

	glLineWidth(1.0f);
}

bool ModuleRenderExercise::CleanUp()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
	}

	return true;
}