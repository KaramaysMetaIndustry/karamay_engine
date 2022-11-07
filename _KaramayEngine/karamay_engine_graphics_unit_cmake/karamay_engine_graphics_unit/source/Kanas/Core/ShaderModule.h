#ifndef _SHADER_MODULE_H_
#define _SHADER_MODULE_H_

#include "DeviceObject.h"


_KANAS_CORE_BEGIN

class ShaderModule final : public DeviceObject<VkShaderModule>
{
public:

	ShaderModule(Device& InDevice);

	virtual ~ShaderModule() override;

	bool Allocate();

};

_KANAS_CORE_END

#endif