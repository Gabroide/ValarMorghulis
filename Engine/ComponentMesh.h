#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include <vector>

#include "assert.h"
#include "Component.h"
#include "ModuleTextures.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"
/*
#include "Geometry\AABB.h"
#include "Math\float3.h"
#include "Math\Quat.h"
*/

#include "assimp\mesh.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer, aiMesh* mesh);
	ComponentMesh(ComponentMesh* duplicatedComponent);
	~ComponentMesh();

	void			CleanUp();
	void			Draw(unsigned shaderProgram, const Texture* textures) const;
	void			DrawProperties() override;
	void			ComputeMesh(aiMesh* mesh);
	
	const unsigned	MaterialIndex();

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