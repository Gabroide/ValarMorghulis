#ifndef __DockInspector_h__
#define __DockInspector_h__

#include "Dock.h"

class GameObject;

class DockInspector : public Dock
{
	public:
		DockInspector();
		~DockInspector();

		void Draw() override;
		void Focus(GameObject* gameobject);

	private:
		bool focus = false;

};

#endif // __DockInspector_h__