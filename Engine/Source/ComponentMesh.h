#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include <vector>

#include "ModuleTextures.h"
#include "Component.h"

#include "MathGeoLib\include\Math\float3.h"

#include "Assimp\mesh.h"

struct par_shapes_mesh_s;

class ComponentMaterial;
class GameObject;

class ComponentMesh : public Component
{
	public:
		ComponentMesh(GameObject* goContainer, Mesh* mesh);
		ComponentMesh(const ComponentMesh& duplicatedComponent);
		~ComponentMesh();

		void			ComputeMesh();
		void			ComputeMesh(par_shapes_mesh_s* mesh);
		void			CleanUp();
		void			Draw(unsigned shaderProgram, const ComponentMaterial* material) const;
		void			DrawProperties() override;
		void			LoadMesh(const char* name);
		void			Save(Config* config)							override;
		void			Load(Config* config, rapidjson::Value& value)	override;

	public:
		Component*		Duplicate() override;

	public:
		Mesh			mesh;
		
	public:
		const char*		name = nullptr;
	
private:
	std::string			currentMesh;

};

#endif // __ComponentMesh_h__
