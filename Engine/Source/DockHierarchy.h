#ifndef __DockHeriarchy_h__
#define __DockHeriarchy_h__

#include "Dock.h"

class DockHierarchy : public Dock
{
	public:
		DockHierarchy();
		~DockHierarchy();

		void Draw() override;

};

#endif // __DockHeriarchy_h__