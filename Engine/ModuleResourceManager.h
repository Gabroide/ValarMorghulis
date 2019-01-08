#ifndef __ModuleResourceManager_h__
#define __ModuleResourceManager_h__

#include "Module.h"

#include "Utils\crossguid\guid.hpp"

class ModuleResourceManager : public Module
{
public:
	ModuleResourceManager();
	~ModuleResourceManager();

	std::string	NewGuuid();

};

#endif // __ModuleResourceManager_h__