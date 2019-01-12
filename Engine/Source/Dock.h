#ifndef __Dock_h__
#define __Dock_h__

#include "IMGUI\imgui.h"

class Dock
{
	public:
		Dock();
		~Dock();

		virtual void Draw()
		{
		
		}

		bool IsEnabled() const 
		{
			return enabled;
		}

		bool IsFocused() const 
		{
			return focused;
		}

		void ToggleEnabled() 
		{
			enabled = !enabled;
		}

	protected:
		bool enabled = true;
		bool focused = false;
};

#endif // __Dock_h__