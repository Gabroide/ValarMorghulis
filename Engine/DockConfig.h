#ifndef __DockConfig_h__
#define __DockConfig_h__

#include <vector>

#include "Dock.h"

#define LOGSSIZE 100

class DockConfig : public Dock
{
public:
	DockConfig();
	~DockConfig();

	void	Draw()			override;
	void	AddFps(float fps, float ms);

private:
	std::vector<float> fps;
	std::vector<float> gameFps;
	std::vector<float> gameMs;
	std::vector<float> mem;

};

#endif // __DockConfig_h__