#ifndef __DockConfig_h__
#define __DockConfig_h__

#include <vector>

#include "Dock.h"

#define NUMFPS 100

class DockConfig : public Dock
{
public:
	DockConfig();
	~DockConfig();

	void	Draw()			override;
	void	DrawFPSgraph()	const;
	void	AddFps(float fps);

private:
	std::vector<float> fps = std::vector<float>();

};

#endif // __DockConfig_h__