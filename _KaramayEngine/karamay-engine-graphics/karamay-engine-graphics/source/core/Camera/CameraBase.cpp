#include "CameraBase.h"
#include "Core/SpicesRendererGlobal.h"

glm::mat4 CameraBase::GetViewMatrix()
{
	glm::vec3 CameraDirection(glm::cos(Pitch) * glm::sin(Yaw), glm::sin(Pitch), glm::cos(Pitch) * glm::cos(Yaw));

	glm::vec3 CameraRight = glm::normalize(glm::cross(CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::vec3 CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
	return glm::lookAt(Position, Position + CameraDirection, glm::vec3(0.0f, 1.0f, 0.0f));
}

void CameraBase::Tick(float DeltaTime)
{
	//Position.z += 0.01f;
}

CameraBase::CameraBase()
{
	Pitch = Yaw = Roll = 0.0f;
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
}

CameraBase::~CameraBase()
{
}
