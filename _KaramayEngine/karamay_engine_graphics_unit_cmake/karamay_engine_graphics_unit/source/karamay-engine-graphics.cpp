#include "engine/karamay_engine.h"

#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/render_pass.h"
#include "graphics/vulkan/device_object/command_pool.h"
#include "graphics/vulkan/device_object/pooled_object/command_buffer.h"
#include "graphics/vulkan/device_object/framebuffer.h"

int main()
{
    /*instance _inst;
    std::vector<physical_device*> _physical_devices;
    _inst.enumerate_physical_devices(_physical_devices);
    auto _main_physical_device = _physical_devices[0];
    auto _main_device = _main_physical_device->create_device();*/

    render_pass* _pass;

    command_pool* _cmd_pool;
    _cmd_pool->allocate(0);

    command_buffer* _cmd_buf;
    _cmd_buf->allocate(VkCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY);

    VkCommandBufferBeginInfo _begin_info;
    vkBeginCommandBuffer(_cmd_buf->handle(), &_begin_info);

    _pass->allocate({}, {}, {});
    _pass->set(
        [](framebuffer* rt, command_buffer* recorder)
        {

        }
    );

    VkSubmitInfo _submit;
    _submit.sType;
    _submit.commandBufferCount;
    _submit.pCommandBuffers;
    _submit.signalSemaphoreCount;
    _submit.pSignalSemaphores;
    _submit.waitSemaphoreCount;
    _submit.pWaitSemaphores;
    _submit.pWaitDstStageMask;

    

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
