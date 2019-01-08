#ifndef __DockInspector_h__
#define __DockInspector_h__

#include "Dock.h"
#include "Component.h"

class DockInspector : public Dock
{
public:
	DockInspector();
	~DockInspector();

	void	Draw() override;

public:
	void	Focus(GameObject* gameobject);

private:
	bool	focus = false;

};

#endif // __DockInspector_h__