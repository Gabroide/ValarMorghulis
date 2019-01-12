#ifndef __DockLight_h__
#define __DockLight_h__

#include "Dock.h"
#include "Component.h"

class DockLight : public Dock
{
	public:
		DockLight();
		~DockLight();

		void	Draw() override;
		bool	IsFocused() const;

	public:
		bool	focus = false;

};

#endif // __DockLight_h__