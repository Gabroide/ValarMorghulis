#ifndef __MpduleEditor_h__
#define __ModuleEditor_h__

#include <vector>

#include "Module.h"
#include "Globals.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl.h"
#include "imgui\imgui_impl_opengl3.h"

class ModuleEditor : public Module
{
	public:
		ModuleEditor();
		~ModuleEditor();

		bool				Init()		override;
		bool				CleanUp()	override;

		update_status		PreUpdate()	override;
		update_status		Update()	override;

		void				HandleInputs(SDL_Event& event);

public:
	bool				showAboutMenu		= false;
	bool				showHardwareMenu	= false;
	bool				requestedExit		= false;
	bool				showSceneConfig		= false;
	bool				showTextureConfig	= false;
	
	ImGuiIO				io;
	
	std::vector<float>	fps_log;
	std::vector<float>	ms_log;

};

#endif // __ModuleEditor_h__