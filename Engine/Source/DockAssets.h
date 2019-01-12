#ifndef __DockAssets_h__
#define __DockAssets_h__

#include "Dock.h"

class DockAssets : public Dock
{
public:
	DockAssets();
	~DockAssets();

	void		Draw() override;
	void		DrawTreeNode(const char* name, bool isLeaf);
	void		ClickBehaviour(const char* name);

	bool		IsFocused() const;

public:
	bool		focus = false;

	std::string itemSelected;

};

#endif // __DockAssets_h__