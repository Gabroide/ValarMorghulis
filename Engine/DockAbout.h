#ifndef __DockAbout_h__
#define __DockAbout_h__

#include "Dock.h"

class DockAbout : public Dock
{
public:
	DockAbout();
	~DockAbout();

	void Draw()	override;

};

#endif //__DockAbout_h__