#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Globals.h"
#include "Point.h"
#include "MathGeoLib.h"
#include "GL/glew.h"
#include "SDL.h"

class ModuleCamera : public Module
{
	enum CameraMovement 
	{
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

	bool			Init()		override;
	bool			CleanUp()	override;

	update_status	PreUpdate() override;
	
	void			DrawGUI();
	void			CameraMovementKeyboard();
	void			RotateCamera(const fPoint& mousePosition, bool orbit = false);
	void			MoveCamera(CameraMovement cameraSide);
	void			FocusSelectedObject();
	void			UpdatePitchYaw();
	void			Zoom();

public:
	bool			firstMouse			= true;
	
	float			mouseSensitivity	= 65.0f;
	float			rotationSpeed		= 65.0f;;
	float			cameraSpeed			= 17.0f;
	float			pitch;
	float			yaw;
	float			lastX				= 0.0f;
	float			lastY				= 0.0f;
	float			maxFov				= 100.0f;
	float			minFov				= 1.0f;

	math::float3	cameraPos			= math::float3(10.0f, 10.0f, 10.0f);
	math::float3	front				= math::float3(-0.577350259f, -0.577350259f, -0.577350259f);
	math::float3	side;
	math::float3	up					= math::float3(0.0f, 1.0f, 0.0f);

	AABB			selectedObjectBB;

};

#endif // __ModuleCamera_h__