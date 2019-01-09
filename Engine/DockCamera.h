#ifndef __DockCamera_h__
#define __DockCamera_h__

#include "Dock.h"

class DockCamera
{
public:
	DockCamera();
	~DockCamera();

	void	Draw()	override;

	bool	IsFocused() const;

public:
	bool	focus = false;

};

#endif // __DockCamera_h__