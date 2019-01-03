#ifndef __Dock_h__
#define __Dock_h__

#include "IMGUI\imgui.h"

class Dock
{
public:
	Dock();
	~Dock();

	virtual void Draw() 
	{
		
	}

	bool IsEnabled() const 
	{
		return enabled;
	}

	void ToggleEnabled() 
	{
		enabled = !enabled;
	}

public:
	bool enabled = true;

};

#endif // __Dock_h__