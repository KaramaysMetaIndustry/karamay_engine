#include "dispatcher.h"
#include "core/vulkan_instance.h"
#include "core/physical_device.h"
#include "core/device.h"
#include "core/queue.h"
#include "core/command_buffer.h"

kanas::dispatcher::dispatcher() {

}

kanas::dispatcher::~dispatcher() {

}

bool kanas::dispatcher::initialize()
{
    _app = std::make_unique<core::vulkan_instance>();

    check(_app);
    if(!_app->initialize())
    {
        return false;
    }

    for(const auto& _GPU : _app->GPUs())
    {
        if(_GPU)
        {
            if(const auto _dev = _GPU->derive())
            {
                _dev->get_queue(0, 0);

                _devices.push_back(_dev);
            }
        }
    }


    return true;
}

void kanas::dispatcher::tick(float delta_time)
{
    if(_devices.empty() || !_devices[0])
    {
        return;
    }

    core::device& _master_dev = *_devices[0];

    // multithreading
    for(const auto& _render_pass : _render_passes)
    {
        if(_render_pass)
        {
            // find command buffer
            std::shared_ptr<core::primary_command_buffer> pcb;
            if(pcb)
            {
                pcb->reset();
                pcb->record(*_render_pass);
            }
        }
    }

    // block to wait for all
    // ready for submission

    std::shared_ptr<core::queue> _queue = _master_dev.get_queue(0, 0);
    if(_queue)
    {

        core::submission_batch _batch;
        _batch.cmd_buffers;
        _batch.semaphore_to_wait_before_execution;
        _batch.semaphore_to_signal_after_execution;

        _queue->submit({_batch});
        _queue->present();

        _queue->wait_idle();
    }

}

void kanas::dispatcher::create_render_pass(const nlohmann::json& rpd)
{
    if (!rpd.is_object())
    {
        return;
    }

    auto _it = rpd.find("name");

    if (_it == rpd.cend())
    {
        return;
    }

    const std::string _render_pass_name = _it->value("name", "null");

    _it = rpd.find("subpasses");

    if (_it == rpd.cend())
    {
        return;
    }

}




