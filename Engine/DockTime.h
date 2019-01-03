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

	void	Draw()	override;

public:
	bool	resizedLastFrame	= false;

private:
	bool	gamePaused			= false;
	bool	step				= false;

	float	gameTime			= 0;

};

#endif //__DockTime_h__

