#ifndef __ComponentMesh_h__
#define __ComponentMesh_h__

#include "Component.h"

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* goContainer);
	~ComponentMesh();
};

#endif // __Component_h__