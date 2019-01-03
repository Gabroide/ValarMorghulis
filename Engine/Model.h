#ifndef __Model_h__
#define __Model_h__

#include <list>
#include <vector>
#include <string>

#include "Mesh.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"

#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"
#include "assimp\material.h""
#include "assimp\mesh.h"

struct Texture 
{
	int id;
	int width;
	int height;
	Texture(int id, int width, int height) : id(id), width(width), height(height) {}
};

class Model
{
public:
	Model(const char* file);
	~Model();

	void					Draw() const;
	void					UpdateTexture(Texture texture);
	
public:
	AABB					boundingBox;
	
private:
	bool					LoadModel(const char* pathFile);
	
	void					GenerateMeshData(const aiNode* node, const aiScene* scene);
	void					GenerateMaterialData(const aiScene* scene);
	void					GetAABB();

	std::list<Mesh>			meshes;
	std::vector<Texture>	textures;

private:
	const char*				path;
	
};

#endif // __Model_h__