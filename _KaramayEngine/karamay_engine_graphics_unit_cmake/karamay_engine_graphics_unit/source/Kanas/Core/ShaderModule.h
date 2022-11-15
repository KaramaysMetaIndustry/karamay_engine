#ifndef _SHADER_MODULE_H_
#define _SHADER_MODULE_H_

#include "DeviceObject.h"


_KANAS_CORE_BEGIN

class FShaderModule final : public FDeviceObject<VkShaderModule>
{

	friend class FDevice;

	bool Allocate(const TVector<uint32>& CodeBytes);

public:

	FShaderModule(FDevice& InDevice);

	virtual ~FShaderModule() override;

private:

	TVector<uint32> Code;

};

_KANAS_CORE_END

#endif