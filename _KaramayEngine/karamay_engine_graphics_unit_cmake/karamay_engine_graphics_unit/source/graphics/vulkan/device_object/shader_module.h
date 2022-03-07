#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H
#include "device_object.h"

class shader_module final : public device_object<VkShaderModule>
{
public:

	shader_module(device& dev);

	shader_module(const shader_module&) = delete;
	shader_module& operator=(const shader_module&) = delete;

	~shader_module() override;

public:

	bool allocate(uint64 size, uint32* code) noexcept;

	void deallocate() noexcept;

};


#endif