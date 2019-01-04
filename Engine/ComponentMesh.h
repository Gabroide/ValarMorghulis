#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include "Mesh.h"
#include "assert.h"
#include "Component.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer);
	~ComponentMesh();

	void						ComputeMesh(aiMesh* mesh);
	void						CleanUp();
	void						Draw(unsigned shaderProgram, const std::vector<Texture>& textures) const;

public:
	int							numIndices = 0;
	int							materialIndex = 0;
	
	AABB						bbox;

	std::vector<math::float3>	vertices;
	
public:
	const char*					name = nullptr;

private:
	unsigned					vao = 0u;
	unsigned					vbo = 0u;
	unsigned					ibo = 0u;

};

#endif // __Component_h__