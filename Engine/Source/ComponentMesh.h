#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include <vector>

#include "ModuleTextures.h"
#include "Component.h"

#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Geometry\AABB.h"

#include "Assimp\mesh.h"

struct par_shapes_mesh_s;
class ComponentMaterial;

class ComponentMesh : public Component
{
	public:
		ComponentMesh(GameObject* goContainer, aiMesh* mesh);
		ComponentMesh(const ComponentMesh& duplicatedComponent);
		~ComponentMesh();

		void						ComputeMesh(aiMesh* mesh);
		void						ComputeMesh(par_shapes_mesh_s* mesh);
		void						CleanUp();
		void						Draw(unsigned shaderProgram, const ComponentMaterial* material) const;
		void						DrawProperties() override;
		
		const unsigned				MaterialIndex();
		
	public:
		Component*					Duplicate() override;

	public:
		
		int							numIndices = 0;
		int							materialIndex = 0;
		std::vector<math::float3>	vertices;
		math::AABB					bbox;

	public:
		const char*					name = nullptr;
	
private:
		unsigned					vao = 0u;
		unsigned					vbo = 0u;
		unsigned					ibo = 0u;

};

#endif // __ComponentMesh_h__
