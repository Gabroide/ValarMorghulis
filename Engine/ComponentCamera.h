#ifndef __ComponentCamera_h__
#define __ComponentCamera_h__

#include "Globals.h"
#include "Component.h"
#include "GameObject.h"

#include "MathGeoLib.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* goParent);
	~ComponentCamera();

	void			DrawProperties()	override;
	void			SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
	void			InitFrustum(GameObject* goParent);
	void			SetHorizontalFOV(float fovXDegrees);
	void			SetVerticalFOV(float fovYDegrees);
	void			UpdatePitchYaw();

	Component*		Duplicate()			override;

	math::float4x4	ProjectionMatrix();
	math::float4x4	LookAt(math::float3& cameraPosition, math::float3& cameraFront, math::float3& cameraUp);
	math::float4x4	ComponentCamera::LookAt(math::float3& cameraPos, math::float3& target);

public:
	bool			firstMouse = true;

	float			maxFov				= 100.0f;
	float			minFov				= 10.0f;
	float			pitch				= 0.0f;
	float			yaw					= 0.0f;
	float			screenRatio			= screenWidth / screenHeight;
	float			cameraSpeed			= 15.0f;
	float			rotationSpeed		= 65.0f;
	float			mouseSensitivity	= 0.2f;
	float			fovY				= 45.0f;
	float			fovX				= 45.0f;
	float			zoomValue			= 0.0f;

	unsigned		screenWidth			= SCREEN_WIDTH;
	unsigned		screenHeight		= SCREEN_HEIGHT;

	int				lastX				= 0;
	int				lastY				= 0;

	math::Frustum	frustum;

	math::float3	cameraPosition		= math::float3(0.0f, 3.0f, 20.0f);
	math::float3	cameraFront			= math::float3(0.0f, 0.0f, -1.0f);
	math::float3	cameraUp			= math::float3(0.0f, 1.0f, 0.0f);

};

#endif // __ComponentCamera_h__
