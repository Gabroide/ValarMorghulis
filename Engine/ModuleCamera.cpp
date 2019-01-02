#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleEditor.h"
#include "ModuleCamera.h"

// Constructor
ModuleCamera::ModuleCamera() 
{
	front = math::float3(-0.5f, -0.5f, -0.5f);
	up = math::float3(0.0f, 1.0f, 0.0f);
	cameraPos = math::float3(7.0f, 7.0f, 7.0f);

	cameraSpeed = 17.0f;
	rotationSpeed = 65.0f;
	mouseSensitivity = 0.5f;
}

// Destructor
ModuleCamera::~ModuleCamera() 
{

}

// Called before render is available
bool ModuleCamera::Init() 
{
	InitFrustum();
	UpdatePitchYaw();
	LookAt(cameraPos, (cameraPos + front));

	return true;
}

// Called every draw update
update_status ModuleCamera::PreUpdate() 
{
	if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT) 
	{
		CameraMovementKeyboard();
		SDL_ShowCursor(SDL_DISABLE);
		RotateCameraMouse(App->input->GetMousePosition());
	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP) 
	{
		SDL_ShowCursor(SDL_ENABLE);
		firstMouse = true;
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) 
	{
		FocusObject(objectCenter);
	}

	if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT) 
	{
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) 
		{
			SDL_ShowCursor(SDL_DISABLE);
			RotateCameraMouse(App->input->GetMousePosition(), true);
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT) 
		{
			SDL_ShowCursor(SDL_ENABLE);
		}
	}
	else if (App->input->GetKey(SDL_SCANCODE_LALT) == KEY_UP) 
	{
		SDL_ShowCursor(SDL_ENABLE);
	}

	if (App->input->GetMouseButtonDown(SDL_BUTTON_X1) == KEY_DOWN) 
	{
		fovX += zoomSpeed;
		Zooming();
	}
	else if (App->input->GetMouseButtonDown(SDL_BUTTON_X2) == KEY_DOWN) 
	{
		fovX -= zoomSpeed;
		Zooming();
	}

	if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_DOWN) 
	{
		cameraSpeed = cameraSpeed * 2;
		rotationSpeed = rotationSpeed * 2;
	}
	else if (App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_UP) 
	{
		cameraSpeed = cameraSpeed * 0.5f;
		rotationSpeed = rotationSpeed * 0.5f;
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleCamera::CleanUp() 
{

	return true;
}

void ModuleCamera::MoveCamera(CameraMovement cameraSide) 
{
	float normCameraSpeed = cameraSpeed * App->deltaTime;

	switch (cameraSide) 
	{
	case Upwards:
		cameraPos += up * normCameraSpeed;
		break;

	case Downwards:
		cameraPos -= up * normCameraSpeed;
		break;

	case Left:
		cameraPos += up.Cross(front) * normCameraSpeed;
		break;

	case Right:
		cameraPos -= up.Cross(front) * normCameraSpeed;
		break;

	case Forward:
		cameraPos += front * normCameraSpeed;
		break;

	case Backwards:
		cameraPos -= front * normCameraSpeed;
		break;
	}

	LookAt(cameraPos, (cameraPos + front));
}

void ModuleCamera::RotateCameraKeyboard(CameraMovement cameraSide, bool orbit) 
{
	float normRotationSpeed = rotationSpeed * App->deltaTime;

	switch (cameraSide) 
	{
	case Upwards:
		pitch += normRotationSpeed;
		break;

	case Downwards:
		pitch -= normRotationSpeed;
		break;

	case Left:
		yaw -= normRotationSpeed;
		break;

	case Right:
		yaw += normRotationSpeed;
		break;
	}

	pitch = math::Clamp(pitch, -80.0f, 80.0f);

	math::float3 rotation;
	
	if (orbit) 
	{
		math::float3 cameraTarget = cameraPos + front * 5;
		cameraPos.x = cameraTarget.x + 5 * SDL_sinf(math::DegToRad(-yaw)) * -SDL_cosf(math::DegToRad(-pitch));
		cameraPos.y = cameraTarget.y + 5 * -SDL_sinf(math::DegToRad(-pitch));
		cameraPos.z = cameraTarget.z + 5 * -SDL_cosf(math::DegToRad(-yaw)) * -SDL_cosf(math::DegToRad(-pitch));
		front = (cameraTarget - cameraPos).Normalized();
	}
	else 
	{
		rotation.x = SDL_sinf(math::DegToRad(yaw)) * SDL_cosf(math::DegToRad(pitch));
		rotation.y = SDL_sinf(math::DegToRad(pitch));
		rotation.z = -SDL_cosf(math::DegToRad(yaw)) * SDL_cosf(math::DegToRad(pitch));
		front = rotation.Normalized();
	}

	LookAt(cameraPos, (cameraPos + front));
}

void ModuleCamera::RotateCameraMouse(const iPoint& mousePosition, bool orbit)
{
	if (firstMouse) 
	{
		lastX = mousePosition.x;
		lastY = mousePosition.y;
		firstMouse = false;
	}

	int xoffset = mousePosition.x - lastX;
	int yoffset = lastY - mousePosition.y;
	lastX = mousePosition.x;
	lastY = mousePosition.y;

	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	pitch = math::Clamp(pitch, -80.0f, 80.0f);

	math::float3 rotation;
	
	if (orbit) 
	{
		math::float3 cameraTarget = cameraPos + front * 5;
		cameraPos.x = cameraTarget.x + 5 * SDL_sinf(math::DegToRad(-yaw)) * -SDL_cosf(math::DegToRad(-pitch));
		cameraPos.y = cameraTarget.y + 5 * -SDL_sinf(math::DegToRad(-pitch));
		cameraPos.z = cameraTarget.z + 5 * -SDL_cosf(math::DegToRad(-yaw)) * -SDL_cosf(math::DegToRad(-pitch));
		front = (cameraTarget - cameraPos).Normalized();
	}
	else 
	{
		rotation.x = SDL_sinf(math::DegToRad(yaw)) * SDL_cosf(math::DegToRad(pitch));
		rotation.y = SDL_sinf(math::DegToRad(pitch));
		rotation.z = -SDL_cosf(math::DegToRad(yaw)) * SDL_cosf(math::DegToRad(pitch));
		front = rotation.Normalized();
	}

	LookAt(cameraPos, (cameraPos + front));
}

void ModuleCamera::LookAt(math::float3& cameraPos, math::float3& target) 
{
	front = math::float3(target - cameraPos); front.Normalize();
	
	// We are not implementing roll, so we will calculate the up again mantaining the verticalitiy
	side = math::float3(front.Cross(math::float3(0.0f, 1.0f, 0.0f))); side.Normalize();
	up = math::float3(side.Cross(front));

	viewMatrix[0][0] = side.x; viewMatrix[0][1] = side.y; viewMatrix[0][2] = side.z;
	viewMatrix[1][0] = up.x; viewMatrix[1][1] = up.y; viewMatrix[1][2] = up.z;
	viewMatrix[2][0] = -front.x; viewMatrix[2][1] = -front.y; viewMatrix[2][2] = -front.z;
	viewMatrix[0][3] = -side.Dot(cameraPos); viewMatrix[1][3] = -up.Dot(cameraPos); viewMatrix[2][3] = front.Dot(cameraPos);
	viewMatrix[3][0] = 0.0f; viewMatrix[3][1] = 0.0f; viewMatrix[3][2] = 0.0f; viewMatrix[3][3] = 1.0f;
}

math::float4x4 ModuleCamera::ProjectionMatrix() 
{

	return frustum.ProjectionMatrix();
}

void ModuleCamera::InitFrustum() 
{
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;
	frustum.nearPlaneDistance = 0.1f;
	frustum.farPlaneDistance = 100.0f;
	SetVerticalFOV(fovY);
}

void ModuleCamera::SetHorizontalFOV(float& fovXDegrees) 
{
	fovX = fovXDegrees;
	frustum.horizontalFov = math::DegToRad(fovX);
	frustum.verticalFov = 2.0f * atanf(tanf(frustum.horizontalFov * 0.5) * ((float)screenHeight / (float)screenWidth));
}

void ModuleCamera::SetVerticalFOV(float& fovYDegrees) 
{
	fovY = fovYDegrees;
	frustum.verticalFov = math::DegToRad(fovY);
	frustum.horizontalFov = 2.f * atanf(tanf(frustum.verticalFov * 0.5f) * ((float)screenWidth / (float)screenHeight));
}

void ModuleCamera::SetScreenNewScreenSize(unsigned newWidth, unsigned newHeight) 
{
	screenWidth = newWidth;
	screenHeight = newHeight;
	screenRatio = (float)screenWidth / (float)screenHeight;

	SetHorizontalFOV(fovX);
	SetVerticalFOV(fovY);
}

void ModuleCamera::Zooming() 
{
	zoomValue = 45.0f / fovX;

	SetHorizontalFOV(fovX);

	if (zoomValue != 1.0f)
	{
		App->editor->showZoomMagnifier = true;
	}
	else
	{
		App->editor->showZoomMagnifier = false;
	}
}

void ModuleCamera::FocusObject(math::float3& objectCenterPos) 
{
	front = objectCenterPos - cameraPos;
	UpdatePitchYaw();
	LookAt(cameraPos, (cameraPos + front));
}

void ModuleCamera::UpdatePitchYaw() 
{
	pitch = -math::RadToDeg(SDL_atanf(front.y / front.z));
	yaw = -math::RadToDeg(SDL_atanf(front.x / front.z));

	if (math::IsNan(pitch))
	{
		pitch = 0.0f;
	}

	if (math::IsNan(yaw))
	{
		yaw = 0.0f;
	}
}

void ModuleCamera::CameraMovementKeyboard() 
{
	if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) 
	{
		MoveCamera(Upwards);
	}
	else if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) 
	{
		MoveCamera(Downwards);
	}
	else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) 
	{
		MoveCamera(Left);
	}
	else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) 
	{
		MoveCamera(Right);
	}
	else if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) 
	{
		MoveCamera(Forward);
	}
	else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) 
	{
		MoveCamera(Backwards);
	}
}