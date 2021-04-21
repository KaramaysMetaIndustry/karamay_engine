#include "Camera_OpenGL.h"

Camera_OpenGL::Camera_OpenGL()
{
	Pitch = glm::radians(0.0f);
	Yaw = glm::radians(180.0f);
	Roll = glm::radians(0.0f);

	Position = glm::vec3(0.0f, 0.0f, 5.0f);
}

Camera_OpenGL::~Camera_OpenGL()
{
}
