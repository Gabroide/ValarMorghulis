#ifndef __ComponentLight_h__
#define __ComponentLight_h__

#include "Component.h"

class ComponentLight : public Component
{
	public:
		ComponentLight(GameObject* goContainer);
		~ComponentLight();
};

#endif // __ComponentLight_h__
