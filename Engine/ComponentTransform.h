#ifndef __ComponentTransform_h__
#define __ComponentTransform_h__

#include "Component.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* goContainer);
	~ComponentTransform();
};

#endif // __ComponentTransform_h__