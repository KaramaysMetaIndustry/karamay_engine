#ifndef H_GL_CAMERA
#define H_GL_CAMERA

#include "public/_glew.h"
#include "public/glm.h"
#include "public/stl.h"

class gl_camera
{
public:
	gl_camera() :
		_pitch(glm::radians(0.0f)),
		_yaw(glm::radians(180.0f)),
		_roll(glm::radians(0.0f)),
		_position(glm::vec3(0.0f, 0.0f, 5.0f))
	{

	}

	gl_camera(std::float_t pitch, std::float_t yaw, std::float_t roll, glm::vec3 position)
	{
		_pitch = glm::radians(pitch);
		_yaw = glm::radians(yaw);
		_roll = glm::radians(roll);
		_position = position;
	}

	virtual ~gl_camera()
	{

	}


public:

	void tick(float delta_time)
	{

	}

	glm::mat4 get_view_matrix()
	{
		glm::vec3 _camera_direction(glm::cos(_pitch) * glm::sin(_yaw), glm::sin(_pitch), glm::cos(_pitch) * glm::cos(_yaw));

		glm::vec3 _camera_right = glm::normalize(glm::cross(_camera_direction, glm::vec3(0.0f, 1.0f, 0.0f)));
		glm::vec3 _camera_up = glm::normalize(glm::cross(_camera_direction, _camera_right));
		return glm::lookAt(_position, _position + _camera_direction, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 get_position()
	{
		return _position;
	}


private:

	std::float_t _pitch, _yaw, _roll;

	glm::vec3 _position;

};

#endif

