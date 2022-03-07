#ifndef ACCELERATION_STRUCTURE_H
#define ACCELERATION_STRUCTURE_H
#include "device_object.h"

class acceleration_structure final : public device_object<VkAccelerationStructureKHR>
{
public:

	acceleration_structure(device& dev);

	acceleration_structure(const acceleration_structure&) = delete;
	acceleration_structure& operator=(const acceleration_structure&) = delete;

	~acceleration_structure() override;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

};


#endif