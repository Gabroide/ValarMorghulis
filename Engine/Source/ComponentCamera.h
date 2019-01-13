#ifndef __ComponentCamera_h__
#define __ComponentCamera_h__

#include "Globals.h"
#include "Component.h"

#include "MathGeoLib\include\Math\Quat.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Math\MathFunc.h"
#include "MathGeoLib\include\Geometry\Frustum.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

class GameObject;

class ComponentCamera : public Component
{
	public:
		ComponentCamera(GameObject* goParent);
		~ComponentCamera();

		void			DrawProperties(bool enabled) override;
		void			Update();
		void			InitFrustum(math::float3 camPos = math::float3(0.0f, 300.0f, 1000.0f), math::float3 camFront = math::float3(0.0f, 0.0f, -1.0f), math::float3 camUp = float3::unitY);
		void			InitOrthographicFrustum(math::float3 camPos = math::float3(0.0f, 300.0f, 1000.0f), math::float3 camFront = math::float3(0.0f, 0.0f, -1.0f), math::float3 camUp = float3::unitY);
		void			CreateFrameBuffer(float winWidth, float winHeight);
		void			LookAt(math::float3 target);
		void			Rotate(float dx, float dy);
		void			Orbit(float dx, float dy);
		void			SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
		void			SetHorizontalFOV(float fovXDegrees);
		void			SetVerticalFOV(float fovYDegrees);
		void			Save(Config* config) override;
		void			Load(Config* config, rapidjson::Value& value) override;

		math::float4x4	GetViewMatrix();
		math::float4x4	GetProjectionMatrix();

	public:
		Component*		Duplicate() override;
	
	public:
		bool			debugDraw			= true;
	
		unsigned		screenWidth			= SCREEN_WIDTH;
		unsigned		screenHeight		= SCREEN_HEIGHT;
		unsigned		fbo					= 0u;
		unsigned		rbo					= 0u;
		unsigned		renderTexture		= 0u;

		int				wireFrame			= GL_FILL;

		float			maxFov				= 100.0f;
		float			minFov				= 10.0f;
		float			fovY				= 45.0f;
		float			fovX				= 45.0f;
		float			cameraSpeed			= 350.0f;
		float			rotationSpeed		= 650.0f;
		float			mouseSensitivity	= 0.2f;
		float			zoomValue			= 0.0f;
		float			screenRatio			= screenWidth / screenHeight;

		math::Frustum	frustum;

};

#endif // __ComponentCamera_h__