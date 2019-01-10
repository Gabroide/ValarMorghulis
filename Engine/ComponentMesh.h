#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include <vector>

#include "Component.h"
#include "ModuleTextures.h"

#include "Geometry\AABB.h"
#include "Math\float3.h"
#include "Math\Quat.h"

#include "assimp\mesh.h"

struct par_shapes_mesh_s;

class ComponentMaterial;
class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer, aiMesh* mesh);
	ComponentMesh(const ComponentMesh& duplicatedComponent);
	~ComponentMesh();

	void			CleanUp();
	void			Draw(unsigned shaderProgram, ComponentMaterial* material) const;
	void			DrawProperties() override;
	void			ComputeMesh(aiMesh* mesh);
	void			ComputeMesh(par_shapes_mesh_s* mesh);

	const unsigned	MaterialIndex();

public:
	
	int							numIndices = 0;
	int							materialIndex = 0;
	
	math::AABB						bbox;

	std::vector<math::float3>	vertices;
	
public:
	const char*					name = nullptr;

private:
	unsigned					vao = 0u;
	unsigned					vbo = 0u;
	unsigned					ibo = 0u;

};

#endif // __Component_h__