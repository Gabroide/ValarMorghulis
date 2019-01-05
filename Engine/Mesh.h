#ifndef __Mesh_h__
#define __Mesh_h__

#include <vector>
#include <assert.h>

#include "Globals.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"

#include "assimp\mesh.h"

struct Texture;

class Mesh
{
public:
	Mesh(aiMesh* mesh);
	~Mesh();

	void						Draw(unsigned shaderProgram, const Texture* texture) const;

public:
	int							numIndices		= 0;
	int							materialIndex	= 0;

	std::vector<math::float3>	vertices;

private:
	unsigned					vao				= 0u;
	unsigned					vbo				= 0u;
	unsigned					ibo				= 0u;

};

#endif // __Mesh_h__
