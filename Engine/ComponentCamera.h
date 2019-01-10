#ifndef __ComponentCamera_h__
#define __ComponentCamera_h__

#include "Globals.h"
#include "Component.h"
#include "GameObject.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"


#include "MathGeoLib\include\Math\Quat.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include/Math\MathFunc.h"
#include "MathGeoLib\include\Geometry\Frustum.h"

class ComponentCamera : public Component
{
public:
	ComponentCamera(GameObject* goParent);
	~ComponentCamera();

	void			DrawProperties() override;
	void			Update();
	void			InitFrustum();
	void			LookAt(math::float3 target);
	void			Rotate(float dx, float dy);
	void			Orbit(float dx, float dy);
	void			SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
	void			SetHorizontalFOV(float fovXDegrees);
	void			SetVerticalFOV(float fovYDegrees);
	void			CreateFrameBuffer();

	math::float4x4	GetViewMatrix();
	math::float4x4	GetProjectionMatrix();

public:
	Component*		Duplicate();


public:
	bool			debugDraw			= true;

	int				wireFrame			= GL_FILL;

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
	unsigned		fbo					= 0u;
	unsigned		rbo					= 0u;
	unsigned		renderTexture		= 0u;

	math::Frustum	frustum;

	math::float3	cameraPosition		= math::float3(0.0f, 3.0f, 20.0f);
	math::float3	cameraFront			= math::float3(0.0f, 0.0f, -1.0f);
	math::float3	cameraUp			= math::float3(0.0f, 1.0f, 0.0f);

};

#endif // __ComponentCamera_h__
