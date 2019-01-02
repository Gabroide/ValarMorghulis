#ifndef __ModuleModelLoader_h__
#define __ModuleModelLoader_h__

#include <vector>

#include "Module.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "SDL\include\SDL.h"

#include "MathGeoLib.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/material.h"
#include "assimp/mesh.h"

class ModuleModelLoader : public Module
{
public:
	ModuleModelLoader();
	~ModuleModelLoader();

	bool	Init()		override;
	bool    CleanUp()	override;
	bool	LoadModel(const char* pathFile);

	struct Mesh
	{
		unsigned vbo = 0;
		unsigned ibo = 0;
		unsigned material = 0;
		unsigned num_vertices = 0;
		unsigned num_indices = 0;
	};

	struct Material
	{
		unsigned texture0 = 0;
	};

public:
	std::vector<Mesh>     meshes;
	std::vector<Material> materials;

private:
	void	GenerateMeshData(const aiScene* scene);
	void	GenerateMaterialData(const aiScene* scene);

};

#endif // __ModuleModelLoader_h__ 