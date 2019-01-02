#ifndef __ModuleCamera_h__
#define __ModuleCamera_h__

#include "Module.h"
#include "Globals.h"
#include "Point.h"

#include "SDL\include\SDL.h" // TODO: clean SDL

#include "glew-2.1.0\include\GL\glew.h"

#include "Math\float2.h"
#include "Math\float3.h"
#include "Math\float4x4.h"
#include "Math\MathConstants.h"
#include "Math\MathFunc.h"
#include "Geometry\Frustum.h"
#include "MathGeoLib.h" // TODO: find out the owners of IsNan and Clamp

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
	
	void			LookAt(math::float3& cameraPos, math::float3& cameraFront);
	void			InitFrustum();
	void			CameraMovementKeyboard();
	void			CameraMovementMouse();
	void			MouseUpdate(const iPoint& mousePosition);
	void			SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
	void			MoveCamera(CameraMovement cameraSide);
	void			RotateCamera(CameraMovement cameraSide);
	void			SetHorizontalFOV(float& fovXDegrees);
	void			SetVerticalFOV(float& fovYDegrees);
	void			Zooming(bool positive);
	void			FocusObject(math::float3& objectCenterPos);
	void			UpdatePitchYaw();

	math::float4x4	ProjectionMatrix();
	
public:
	bool			firstMouse	= true;
	
	int				lastX		= 0;
	int				lastY		= 0;

	float			cameraSpeed;
	float			rotationSpeed;
	float			mouseSensitivity;
	float			fov;
	float			screenRatio = screenWidth / screenHeight;
	float			fovY			= 45.0f;
	float			fovX			= 45.0f;
	float			zoomValue		= 0.0f;
	float			pitch;
	float			yaw;

	unsigned		screenWidth		= SCREEN_WIDTH;
	unsigned		screenHeight	= SCREEN_HEIGHT;

	Frustum			frustum;
	
	math::float3	cameraPos;
	math::float3	cameraFront;
	math::float3	front;
	math::float3	side;
	math::float3	up;
	math::float3	sceneCenter		= math::float3(0.0f, 0.0f, 0.0f);

	math::float4x4	viewMatrix;

};

#endif // __ModuleCamera_h__