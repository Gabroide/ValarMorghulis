#ifndef __ModuleSceneLoader_h__
#define __ModuleSceneLoader_h__

#include <list>

#include "Module.h"
#include "Globals.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib.h"
/*
"Math/float3.h"
"Math/float4.h"
"Math/Quat.h"
*/
#include "assimp\cimport.h"
#include "assimp\postprocess.h"
#include "assimp\scene.h"
#include "assimp\matrix4x4.h"

struct aiNode;
struct aiScene;
class GameObject;

class ModuleSceneLoader : public Module
{
public:
	ModuleSceneLoader();
	~ModuleSceneLoader();

	bool Start();

	void		LoadFile(const char* path);
	void		LoadScene(const aiScene* scene);
	
public:
	GameObject*	ProcessTree(const aiNode* node, const aiScene* scene, const aiMatrix4x4 &parentTransform, GameObject* parent);

public:
	const char* filepath = nullptr;

};

#endif // __ModuleSceneLoader_h__