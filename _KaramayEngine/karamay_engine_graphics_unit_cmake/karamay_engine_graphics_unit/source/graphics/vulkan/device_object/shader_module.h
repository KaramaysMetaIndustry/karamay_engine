#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H
#include "device_object.h"

class shader_module final : public device_object<VkShaderModule>
{
public:

	bool allocate(uint64 size, uint32* code);

	void deallocate();

};


#endif