#ifndef __DockTime_h__
#define __DockTime_h__

#include "Application.h"
#include "ModuleWindow.h"
#include "Dock.h"

#include "IMGUI\imgui.h"

class DockTime : public Dock
{
public:
	DockTime();
	~DockTime();

	void	Draw() override;

private:
	bool	gamePaused	= false;
	bool	step		= false;

	float	gameTime	= 0.0f;

};

#endif //__DockTime_h__

