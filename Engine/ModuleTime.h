#ifndef __ModuleTime_h__
#define __ModuleTime_h__

#include "Module.h"

class ModuleTime : public Module
{
public:
	ModuleTime();
	~ModuleTime();

	update_status PreUpdate() override;

public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

};

#endif // __ModuleTime_h__