#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class PhysicalDevice;

class DeviceMemory;
class Buffer;
class Image;
class CommandPool;
class DescriptorPool;
class DescriptorSetLayout;
class Event;
class Fence;
class Framebuffer;
class PipelineCache;
class PipelineLayout;
class Queue;
class RenderPass;
class Sampler;
class Semaphore;
class ShaderModule;

class Device final : public VulkanObject<VkDevice>
{
public:
	Device() = default;

	virtual ~Device() {}

	Queue* GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex);
	DeviceMemory* CreateDeviceMemory(VkDeviceSize InAllocSize, uint32 InMemTypeIndex);
	Buffer* CreateBuffer();
	Image* CreateImage();
	CommandPool* CreateCommandPool();
	DescriptorPool* CreateDescriptorPool();
	Fence* CreateFence(bool IsDefaultSignaled = false);
	Semaphore* CreateSemaphore();
	Event* CreateEvent();
	Framebuffer* CreateFramebuffer();
	PipelineCache* CreatePipelineCache();
	PipelineLayout* CreatePipelineLayout();
	RenderPass* CreateRenderPass();
	Sampler* CreateSampler();
	
	ShaderModule* CreateShaderModule();

	PhysicalDevice& GetPhysicalDevice() const { return GPU; }

private:

	PhysicalDevice& GPU;

	std::vector<Queue*> TransferQueues;
	std::vector<Queue*> GraphicsQueues;
	std::vector<Queue*> ComputeQueues;
	
	void Test();

};

_KANAS_CORE_END


#endif
