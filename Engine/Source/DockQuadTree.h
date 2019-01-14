#ifndef __DockQuadTree_h__
#define __DockQuadTree_h__

#include "Dock.h"

class DockQuadTree : public Dock
{
public:
	DockQuadTree();
	~DockQuadTree();

	void	Draw() override;
	bool	IsFocused() const;

public:
	bool	focus = false;

};

#endif // __DockQuadTree_h__