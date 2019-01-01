#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Globals.h"

#include "SDL\include\SDL.h" // TODO: clean SDL

#include "glew-2.1.0\include\GL\glew.h"

#include "Math\float2.h"
#include "Math\float3.h"
#include "Math\float4x4.h"
#include "Math\MathConstants.h"
#include "Math\MathFunc.h"
#include "Geometry\Frustum.h"

class ModuleCamera : public Module
{

	enum CameraMovement { // TODO: pass to class
		Upwards = 0,
		Downwards,
		Left,
		Right,
		Forward,
		Backwards
	};

	enum CameraRotation { // TODO: pass to class
		Pitch = 0,
		Yaw
	};

public:
	ModuleCamera();
	~ModuleCamera();

	bool			Init()		override;
	bool			CleanUp()	override;

	update_status	PreUpdate()	override;
	update_status	Update()	override;
	
	void			InitFrustum();
	void			MouseUpdate(int mouseXpos, int mouseYpos);
	void			SetHorizontalFOV(float& fovXDegrees);
	void			SetVerticalFOV(float& fovXDegrees);
	void			MoveCamera(CameraMovement cameraSide);
	void			RotateCamera();
	void			SetScreenNewScreenSize(float& newWidth, float& newHeight);
	void			MoveCamera(CameraMovement cameraSide);

	math::float4x4	ProjectionMatrix();
	math::float4x4	LookAt(math::float3& cameraPos, math::float3& cameraFront, math::float3& cameraUp);

public:
	bool			firstMouse	= true;

	int				lastX		= 0;
	int				lastY		= 0;
	
	float			cameraSpeed;
	float			rotationSpeed;
	float			mouseSensitivity;
	float			fov;
	float			screenWidth		= SCREEN_WIDTH;
	float			screenHeight	= SCREEN_HEIGHT;
	float			screenRatio		= screenWidth / screenHeight;
	float			fovY			= 45.0f;
	float			fovX			= 45.0f;
	float			pitch;
	float			yaw;

	Frustum			frustum;

	// Camera states
	math::float3 cameraPos;
	math::float3 cameraFront;
	math::float3 cameraUp;

};

#endif // __ModuleCamera_h__