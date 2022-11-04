#ifndef _SHADER_MODULE_H_
#define _SHADER_MODULE_H_

#include "DeviceObject.h"


_KANAS_CORE_BEGIN

class ShaderModule final : public DeviceObject<VkShaderModule>
{
public:

	ShaderModule();

	virtual ~ShaderModule();

};

_KANAS_CORE_END

#endif