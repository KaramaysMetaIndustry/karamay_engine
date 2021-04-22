#include "DirectionalLightBase.h"

void DirectionalLightBase::Install()
{
}

void DirectionalLightBase::Submit(PipelineBase* AssociatedPipeline)
{
}

void DirectionalLightBase::Uninstall()
{
}

DirectionalLightBase::DirectionalLightBase()
{
	Angle = glm::vec3(glm::radians(45.0f), 0, 0);
	Color = glm::vec3(1.0f, 1.0f, 1.0f);

	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angle.z);
	Direction = glm::rotateX(Direction, Angle.x);
	Direction = glm::rotateY(Direction, Angle.y);
	Direction *= -1.0f;
}

DirectionalLightBase::~DirectionalLightBase()
{
}
