#include "ModuleResourceManager.h"

// Constructor
ModuleResourceManager::ModuleResourceManager() 
{
	
}

// Destructor
ModuleResourceManager::~ModuleResourceManager() 
{
	
}

std::string ModuleResourceManager::NewGuuid() 
{
	std::string uuid(xg::newGuid().str());

	return uuid;
}
