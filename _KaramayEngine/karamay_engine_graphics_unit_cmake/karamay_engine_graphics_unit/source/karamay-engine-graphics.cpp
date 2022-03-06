#include "engine/karamay_engine.h"
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"

int main()
{
    instance _inst;
    _inst.allocate();

    std::vector<physical_device*> _physical_devices;
    _inst.enumerate_physical_devices(_physical_devices);

    device _dev;
    _dev.allocate(_physical_devices.at(0));

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
