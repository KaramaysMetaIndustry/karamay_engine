#ifndef _DEFERRED_OPERATION_H_
#define _DEFERRED_OPERATION_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDeferredOperation : public FDeviceObject<VkDeferredOperationKHR>
{

	bool Allocate();

public:

	FDeferredOperation(FDevice& Device);

	virtual ~FDeferredOperation();

};

_KANAS_CORE_END

#endif