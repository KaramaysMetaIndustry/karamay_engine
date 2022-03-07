#include "engine/karamay_engine.h"
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/device_memory.h"

int main()
{
    instance _inst;
    _inst.allocate();

    std::vector<physical_device*> _physical_devices;
    _inst.enumerate_physical_devices(_physical_devices);

    device _dev;
    _dev.allocate(_physical_devices.at(0));

    auto _buf = _dev.create<buffer>();
    _buf->allocate(
        1073741824u,
        VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
        VkSharingMode::VK_SHARING_MODE_EXCLUSIVE
    );

    _buf->memory->execute_handler(0, 4, VkMemoryMapFlags(), 
        [](uint64 size, void* data) 
        {
            float _v = 2.0f;
            std::memcpy(data, &_v, 4);
        });


    karamay_engine::set_engine_root(
        "C:\\PrivateRepos\\karamay_engine\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\"
    );
    
    karamay_engine _ke;
    if (!_ke.initialize())
    {
        return 1;
    } 
    _ke.run();
    return 0;
}
