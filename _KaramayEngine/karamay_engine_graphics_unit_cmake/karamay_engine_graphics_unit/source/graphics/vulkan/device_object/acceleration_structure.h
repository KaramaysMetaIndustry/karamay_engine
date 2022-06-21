#ifndef ACCELERATION_STRUCTURE_H
#define ACCELERATION_STRUCTURE_H
#include "device_object.h"

class vk_acceleration_structure final : public device_object<VkAccelerationStructureKHR>
{
public:

	vk_acceleration_structure(vk_device& dev);

	vk_acceleration_structure(const vk_acceleration_structure&) = delete;
	vk_acceleration_structure& operator=(const vk_acceleration_structure&) = delete;

	~vk_acceleration_structure() override;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

};


#endif