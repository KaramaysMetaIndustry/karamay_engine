#include "physical_device.h"
#include "device.h"

device* physical_device::create_device()
{
    VkDeviceCreateInfo _create_info;
    VkDevice _new_device_handle;
    vkCreateDevice(_handle, &_create_info, nullptr, &_new_device_handle);
    return new device(_new_device_handle);
}
