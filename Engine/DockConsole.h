#ifndef __DockConsole_h__
#define __DockConsole_h__

#include "Dock.h"

class DockConsole : public Dock
{
public:
	DockConsole();
	~DockConsole();

	void Clear() 
	{ 
		buf.clear(); lineOffsets.clear(); 
	}

	void AddLog(const char* log);
	
	void Draw()	override;

private:
	bool                scrollToBottom = true;

	ImGuiTextBuffer     buf;

	ImVector<int>       lineOffsets;

};

#endif // __DockConsole_h__
