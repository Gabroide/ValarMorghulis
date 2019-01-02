#ifndef __ModuleProgram_h__
#define __ModuleProgram_h__

#include "Module.h"

#include "glew-2.1.0\include\GL\glew.h"

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	unsigned	LoadProgram(const char* vertShaderPath, const char* fragShaderPath);

private:
	bool		CompileShader(unsigned shaderAddress, const char* shaderContent);
	
	void		CompileProgram(unsigned programAddress);

private:
	char*		ReadShaderFile(const char* shaderPath);

};

#endif // __ModuleProgram_h__
