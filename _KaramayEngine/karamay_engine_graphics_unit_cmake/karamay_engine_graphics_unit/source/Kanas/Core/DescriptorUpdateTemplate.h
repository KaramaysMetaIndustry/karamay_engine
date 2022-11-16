#ifndef _DESCRIPTOR_UPDATE_TEMPLATE_H_
#define _DESCRIPTOR_UPDATE_TEMPLATE_H_


#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDescriptorUpdateTemplate : public FDeviceObject<VkDescriptorUpdateTemplate>
{
public:

	FDescriptorUpdateTemplate();

	virtual ~FDescriptorUpdateTemplate() override;

};


_KANAS_CORE_END

#endif