#ifndef __MODULEPROGRAM_H__
#define __MODULEPROGRAM_H__

#include "Module.h"
#include "assert.h"
#include "GL/glew.h"

class ModuleProgram : public Module
{
	public:
		ModuleProgram();
		~ModuleProgram();

		bool		CleanUp() override;
		bool		LoadPrograms();
		unsigned	LoadProgram(const char* vertShaderPath, const char* fragShaderPath);

	public:
		unsigned	basicProgram = 0u;
		unsigned	textureProgram = 0u;
		unsigned	blinnProgram = 0u;
		unsigned	vertShader = 0u;
		unsigned	fragShader = 0u;

	private:
		char*		ReadShaderFile(const char* shaderPath);
		bool		CompileShader(unsigned shaderAddress, const char* shaderContent);
		void		CompileProgram(unsigned programAddress);
};

#endif