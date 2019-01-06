#ifndef __Model_h__
#define __Model_h__

#include <list>
#include <vector>
#include <string>

#include "Mesh.h"
#include "GameObject.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"

#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"
#include "assimp\material.h""
#include "assimp\mesh.h"

struct Texture 
{
	int id = 0;
	int width = 0;
	int height = 0;
	Texture(int id, int width, int height) : id(id), width(width), height(height) {}
};

class Model
{
public:
	Model(const char* file);
	~Model();

	void					DrawInfo() const;

public:
	AABB					boundingBox = AABB({ 0, 0, 0}, { 0, 0, 0});
	
private:
	bool					LoadModel(const char* pathFile);
	
	void					GetModelBoundingBox();

private:
	GameObject*				ProcessTree(const aiNode* node, const aiScene* scene, const aiMatrix4x4& parentTransform, GameObject* goParent);

private:
	std::list<Mesh>			meshes;
	std::vector<Texture>	textures;

private:
	const char*				path		= nullptr;
	
};

#endif // __Model_h__