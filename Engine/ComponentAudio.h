#ifndef __ComponentAudio_h__
#define __ComponentAudio_h__

#include "Component.h"

class ComponentAudio : public Component
{
public:
	ComponentAudio(GameObject* goContainer);
	~ComponentAudio();
};

#endif // __ComponentAudio_h__