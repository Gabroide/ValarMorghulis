#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Globals.h"
#include "ComponentMesh.h"
#include "ComponentTransform.h"
#include "ComponentCamera.h"
#include "GameObject.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "SDL\include\SDL.h"

class Camera;

class ModuleCamera : public Module
{
	enum CameraMovement {
		Upwards = 0,
		Downwards,
		Left,
		Right,
		Forward,
		Backwards
	};

	public:

		ModuleCamera();
		~ModuleCamera();

		bool						Init()		override;
		bool						CleanUp()	override;

		update_status				PreUpdate() override;
		update_status				Update() override;
	
		void						DrawGUI();
		void						SelectGameObject();
		void						Move();
		void						MovementSpeed();
		void						FocusSelectedObject();
		void						Zoom();
		void						SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);

	public:
		bool						firstMouse			= true;

		float						mouseSensitivity	= 0.5f;
		float						rotationSpeed		= 0.5f;
		float						cameraSpeed			= 1700.0f;
		float						lastX				= 0.0f;
		float						lastY				= 0.0f;

	public:
		ComponentCamera*			quadCamera			= nullptr;
		ComponentCamera*			sceneCamera			= nullptr;
		ComponentCamera*			selectedCamera		= nullptr;

		std::list<ComponentCamera*>	gameCameras;

		GameObject*					goSelected			= nullptr;

		std::vector<GameObject*>	objectsPossiblePick;

};

#endif // __ModuleCamera_h__