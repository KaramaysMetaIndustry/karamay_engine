#include "Sampler.h"

Kanas::Core::Sampler::Sampler(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Sampler::~Sampler()
{
}

bool Kanas::Core::Sampler::Allocate()
{
	return false;
}
