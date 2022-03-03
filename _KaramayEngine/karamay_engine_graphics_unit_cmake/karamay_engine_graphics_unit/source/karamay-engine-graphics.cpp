#include "engine/karamay_engine.h"
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"

int main()
{
    /*instance _inst;
    std::vector<physical_device*> _physical_devices;
    _inst.enumerate_physical_devices(_physical_devices);
    auto _main_physical_device = _physical_devices[0];
    auto _main_device = _main_physical_device->create_device();*/

    std::cout << "size: " << sizeof(std::string) << std::endl;
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
