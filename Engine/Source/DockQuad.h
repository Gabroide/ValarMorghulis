#ifndef __DockQuad_h__
#define __DockQuad_h__

#include "Dock.h"

class DockQuad : public Dock
{
public:
	DockQuad();
	~DockQuad();

	void	Draw() override;
	bool	IsFocused() const;

public:
	bool	focus = false;

};

#endif // __DockQuad_h__