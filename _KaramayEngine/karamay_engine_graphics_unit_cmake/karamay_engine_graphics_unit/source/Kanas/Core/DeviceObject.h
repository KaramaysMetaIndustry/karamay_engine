#ifndef _DEVICE_OBJECT_H_
#define _DEVICE_OBJECT_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class Device;

template<typename DeviceObjectT>
class DeviceRef
{

};

template<typename DeviceObjectT>
class DevicePoolRef
{

};



template<typename VkHandleT>
class DeviceObject : public VulkanObject<VkHandleT>
{

public:
	
	DeviceObject(Device& InDevice) :
		_Device(InDevice)
	{}

	virtual ~DeviceObject()
	{
	}

private:

	Device& _Device;

public:

	Device& GetDevice() { return _Device; }

	const Device& GetDevice() const { return _Device; }

};


enum class CommandBufferLevel : uint32
{
	Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
	MaxEnum = VK_COMMAND_BUFFER_LEVEL_MAX_ENUM
};

#define VulkanEnumCast(CppEnumVal)


_KANAS_CORE_END

#endif