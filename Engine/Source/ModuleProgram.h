#ifndef __ModuleProgram_h__
#define __ModuleProgram_h__

#include "assert.h"
#include "Module.h"

#include "glew-2.1.0\include\GL\glew.h"

class ModuleProgram : public Module
{
	public:
		ModuleProgram();
		~ModuleProgram();

		bool		CleanUp() override;
		bool		LoadPrograms();
		unsigned	LoadProgram(const char* vertShaderPath, const char* fragShaderPath);

	public:
		unsigned	colorProgram = 0u;
		unsigned	textureProgram = 0u;
		unsigned	blinnProgram = 0u;
		
	private:
		char*		ReadShaderFile(const char* shaderPath);
		bool		CompileShader(unsigned shaderAddress, const char* shaderContent);
		void		CompileProgram(unsigned programAddress);
};

#endif