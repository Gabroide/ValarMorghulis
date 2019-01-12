#ifndef __MeshImporter_h__
#define __MeshImporter_h__

#include <string>
#include <vector>

#include "Assimp\scene.h"
#include "Assimp\cimport.h"
#include "Assimp\postprocess.h"

struct Mesh;

class MeshImporter
{
public:
	static void	ImportFBX(const char* filePath);
	static bool	Import(const aiMesh* aiMesh, const char* meshName);
	static bool	Load(Mesh* mesh, const char* meshName);
	static bool	Save(const Mesh& mesh, const char* meshName);

};

#endif // __MeshImporter_h__