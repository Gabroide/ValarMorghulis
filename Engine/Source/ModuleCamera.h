#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "MathGeoLib.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "GameObject.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h

class Camera;

class ModuleCamera : public Module
{
	enum CameraMovement {
		Upwards,
		Downwards,
		Left,
		Right,
		Forward,
		Backwards
	};

	public:

		ModuleCamera();
		~ModuleCamera();

		bool							Init()		override;
		bool							CleanUp()	override;

		update_status					PreUpdate()	override;
		update_status					Update()	override;
		
		void							DrawGUI();
		void							Move();
		void							MovementSpeed();
		void							FocusSelectedObject();
		void							Zoom();
		void							SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);

	public:
		bool							firstMouse			= true;

		float							mouseSensitivity	= 65.0f;
		float							rotationSpeed		= 65.0f;
		float							cameraSpeed			= 17.0f;
		float							lastX				= 0.0f;
		float							lastY				= 0.0f;

	public:
		ComponentCamera*				sceneCamera			= nullptr;
		ComponentCamera*				selectedCamera		= nullptr;
		ComponentCamera*				quadCamera			= nullptr;

		GameObject*						goSelected			= nullptr;
		
		std::list<ComponentCamera*>		gameCameras;
		
};

#endif // __ModuleCamera_h__