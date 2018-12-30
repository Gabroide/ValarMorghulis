#ifndef __MpduleEditor_h__
#define __ModuleEditor_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include "imgui\imgui.h"
#include "imgui\examples\imgui_impl_sdl.h"
#include "imgui\examples\imgui_impl_opengl3.h"

class ModuleEditor : public Module
{
	public:
		ModuleEditor();
		~ModuleEditor();

		bool				Init()		override;
		bool				CleanUp()	override;

		update_status		PreUpdate()	override;
		update_status		Update()	override;

public:
	ImGuiIO io;

};

#endif // __ModuleEditor_h__