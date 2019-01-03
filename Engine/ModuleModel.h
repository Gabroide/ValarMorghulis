#ifndef __ModuleModel_h__
#define __ModuleModel_h__

#include "Module.h"
#include "Model.h"

struct Texture;

class ModuleModel : public Module
{
public:
	ModuleModel();
	~ModuleModel();

	unsigned	Load(const char* path);
	
	void		DrawModels();
	void		ApplyTexture(Texture texture);
	void		DeleteModels();
	void		DrawGUI();

public:
	bool				checkersTexture	= false;
	
	Texture				checkTexture	= Texture(0, 0, 0);

	std::list<Model>	models;

};

#endif //__ModuleModel_h__
