#ifndef __ComponentMaterial_h__
#define __ComponentMaterial_h__

#include "Component.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* goContainer);
	~ComponentMaterial();
};

#endif // __ComponentMaterial_h__