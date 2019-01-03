#ifndef __DockScene_h__
#define __DockScene_h__

#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "Dock.h"

class DockScene : public Dock
{
public:
	DockScene();
	~DockScene();

	void	Draw()		override;
	
	bool	IsFocused()	const;
	bool	focus = false;

};

#endif //__DockScene_h__