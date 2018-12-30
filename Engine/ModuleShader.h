#ifndef __ModuleShader_h__
#define __ModuleShader_h__

#include "Module.h"

#include "glew-2.1.0\include\GL\glew.h"

class ModuleShader : public Module
{
public:
	ModuleShader();
	~ModuleShader();

	void	CheckCompilationErrors(GLuint shader);
	GLuint	LoadShaders(const char* vertShaderPath, const char* fragShaderPath);

public:
	char*	ReadShaderFile(const char* shaderPath);

};

#endif // __ModuleShader_h__