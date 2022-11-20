#include "pipeline.h"
#include "device.h"
#include "pipeline_cache.h"
#include "command_buffer.h"
#include "descriptor_set.h"
#include "descriptor_set_layout.h"
#include "pipeline_layout.h"

kanas::core::pipeline::pipeline(device& owner, VkPipelineBindPoint InBindPoint) :
    device_object(owner),
    BindPoint(InBindPoint)
{
}

kanas::core::pipeline::~pipeline()
{
    if (IsValid())
    {
        vkDestroyPipeline(get_device().get_handle(), get_handle(), nullptr);
        
        reset_handle();
    }
}

void kanas::core::pipeline::CmdBind(command_buffer& InRecorder)
{
    vkCmdBindPipeline(InRecorder.get_handle(), BindPoint, get_handle());
}

void kanas::core::pipeline::CmdPushConstants(command_buffer& InRecorder)
{
    if (Constants)
    {
        vkCmdPushConstants(InRecorder.get_handle(), GetLayout()->get_handle(), 0, 0, Constants->GetSize(), Constants->GetData());
    }
}

void kanas::core::pipeline::CmdBindDescriptorSets(command_buffer& InRecorder)
{
    if (!Layout)
    {
        return;
    }
    
    std::vector<VkDescriptorSet> DescriptorSetHandles;
    Collectdevice_objectHandles(Layout->GetDescriptorSetLayouts(), DescriptorSetHandles);

    vkCmdBindDescriptorSets(InRecorder.get_handle(), BindPoint, Layout->get_handle(), 
        0, DescriptorSetHandles.size(), DescriptorSetHandles.data(), 
        0, nullptr
    );
}

std::shared_ptr<kanas::core::pipeline_layout> kanas::core::pipeline::GetLayout() const
{
    return Layout;
}
