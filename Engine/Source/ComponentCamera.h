#ifndef __ComponentCamera_h__
#define __ComponentCamera_h__

#include "Globals.h"
#include "Component.h"

#include "SDL\include\SDL.h"

#include "glew-2.1.0\include\GL\glew.h"

#include "MathGeoLib\include\Math\Quat.h"
#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Math\float4x4.h"
#include "MathGeoLib\include\Math\MathFunc.h"
#include "MathGeoLib\include\Geometry\Frustum.h"

class GameObject;

class ComponentCamera : public Component
{
	public:
		ComponentCamera(GameObject* goParent);
		~ComponentCamera();

		void			DrawProperties(bool enabled)	override;
		void			Update();
		void			InitFrustum(math::float3 camPos = math::float3(0.0f, 3.0f, 10.0f), math::float3 camFront = math::float3(0.0f, 0.0f, -1.0f), math::float3 camUp = float3::unitY);
		void			LookAt(math::float3 target);
		void			Rotate(float dx, float dy);
		void			Orbit(float dx, float dy);
		void			SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight);
		void			SetHorizontalFOV(float fovXDegrees);
		void			SetVerticalFOV(float fovYDegrees);
		void			CreateFrameBuffer(float winWidth, float winHeight);
		void			Save(Config* config) override;
		void			Load(Config* config, rapidjson::Value& value) override;

		Component*		Duplicate()			override;
		
		math::float4x4	GetViewMatrix();
		math::float4x4	GetProjectionMatrix();

	public:
		bool			debugDraw			= true;

		unsigned		screenWidth			= SCREEN_WIDTH;
		unsigned		screenHeight		= SCREEN_HEIGHT;
		unsigned		fbo					= 0u;
		unsigned		rbo					= 0u;
		unsigned		renderTexture		= 0u;

		float			maxFov				= 100.0f;
		float			minFov				= 10.0f;
		float			screenRatio			= screenWidth / screenHeight;
		float			cameraSpeed			= 35.0f;
		float			rotationSpeed		= 65.0f;
		float			mouseSensitivity	= 0.2f;
		float			fovY				= 45.0f;
		float			fovX				= 45.0f;
		float			zoomValue			= 0.0f;

		int				wireFrame			= GL_FILL;

		math::Frustum	frustum;

};

#endif // __ComponentCamera_h__