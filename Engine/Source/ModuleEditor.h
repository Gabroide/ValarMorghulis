#ifndef __ModuleEditor_h__
#define __ModuleEditor_h__

#include <vector>

#include "Globals.h"
#include "Module.h"
#include "Dock.h"
#include "DockAbout.h"
#include "DockAssets.h"
#include "DockCamera.h"
#include "DockConfig.h"
#include "DockConsole.h"
#include "DockHierarchy.h"
#include "DockInspector.h"
#include "DockLight.h"
#include "DockScene.h"
#include "DockTime.h"

#include "IMGUI\imgui.h"
#include "IMGUI\imgui_impl_sdl.h"
#include "IMGUI\imgui_impl_opengl3.h"

class Dock;
class DockConsole;
class DockScene;
class DockConfig;
class DockTime;
class DockHierarchy;
class DockInspector;
class DockCamera;
class DockLight;
class DockAssets;

class ModuleEditor : public Module
{
	public:
		ModuleEditor();
		~ModuleEditor();

		bool				Init()		override;
		bool				CleanUp()	override;
		bool				SceneFocused() const;

		update_status		PreUpdate()	override;
		update_status		Update()	override;
		
		// ImGUI info
		void				AddFPSCount(float fps, float ms) const;
		void				AddGameFPSCount(float fps, float ms) const;
		void				CreateDockSpace();
		void				PrintDocks();
		void				RenderGUI();
		void				ProcessInputEvent(SDL_Event* event) const; // SDL events

	public:
		//Docking
		DockAbout*			about		= nullptr;
		DockConsole*		console		= nullptr;
		DockScene*			scene		= nullptr;
		DockConfig*			config		= nullptr;
		DockTime*			time		= nullptr;
		DockHierarchy*		hierarchy	= nullptr;
		DockInspector*		inspector	= nullptr;
		DockCamera*			camera		= nullptr;
		DockLight*			light		= nullptr;
		DockAssets*			assets		= nullptr;

	private:
		std::list<Dock*>	docks;

};

#endif // __ModuleEditor_h__