#include "ParticleBase.h"

ParticleBase::ParticleBase()
{
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	Color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	Size = 1.0f;
	Lifetime = 10;
}

ParticleBase::~ParticleBase()
{
}
