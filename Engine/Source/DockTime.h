#ifndef __DockTime_h__
#define __DockTime_h__

#include "Dock.h"

class DockTime : public Dock
{
	public:
		DockTime();
		~DockTime();

		void	Draw() override;

};

#endif // __DockTime_h__