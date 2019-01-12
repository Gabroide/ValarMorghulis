#ifndef __ModuleLibrary_h__
#define __ModuleLibrary_h__

#include <map>
#include <vector>
#include <string>

#include "Module.h"

class ModuleLibrary : public Module
{
public:
	ModuleLibrary();
	~ModuleLibrary();

	bool					Init()		override;
	bool					CleanUp()	override;

	update_status			Update()	override;
	
	void					UpdateMeshesList();
	void					UpdateTexturesList();

public:
	bool					 toBeDeleted	= false;
	bool			  		 removeHead		= false;
	
	std::vector<std::string> fileMeshesList;
	std::vector<std::string> fileTexturesList;

};

#endif // __ModuleLibrary_h__
