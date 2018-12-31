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

	enum CameraMovement {
		Upwards = 0,
		Downwards,
		Left,
		Right,
		Forward,
		Backwards
	};

	enum CameraRotation {
		PositivePitch = 0,
		NegativePitch,
		PositiveYaw,
		NegativeYaw
	};

public:
	ModuleCamera();
	~ModuleCamera();

	bool			Init()		override;
	bool			CleanUp()	override;

	update_status	PreUpdate()	override;
	update_status	Update()	override;
	
	void			InitFrustum();
	void			MouseUpdate(int mouseXPos, int mouseYPos);
	void			SetFOV();
	void			MoveCamera(CameraMovement cameraSide);
	void			RotateCamera(CameraRotation cameraRotation);

	math::float4x4	LookAt(math::float3& target, math::float3& eye, math::float3& up);
	math::float4x4	ProjectionMatrix();
	
public:
	bool			firstMouse	= true;
	
	float			cameraSpeed		= 0.5f;
	float			rotationSpeed	= 0.8f;
	float			pitch;
	float			yaw;
	float			lastX			= SCREEN_WIDTH / 2;
	float			lastY			= SCREEN_HEIGHT / 2;
	float			screenRatio		= SCREEN_WIDTH / SCREEN_HEIGHT;

	Frustum			frustum;

	math::float3&	target		= math::float3(0.0f, 0.0f, 0.0f);
	math::float3&	eye			= math::float3(0.0f, 0.0f, 0.0f);
	math::float3&	up			= math::float3(0.0f, 0.0f, 0.0f);
	math::float3	forw;
	math::float3	sidew;
	math::float3	upw;

};

#endif // __ModuleCamera_h__