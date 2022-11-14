#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class FPhysicalDevice;

class FDeviceMemory;
class FBuffer;
class FImage;
class FCommandPool;
class FDescriptorPool;
class FDescriptorSetLayout;
class FEvent;
class FFence;
class FFramebuffer;
class FPipelineCache;
class FPipelineLayout;
class FQueue;
class FRenderPass;
class FSampler;
class FSemaphore;
class FShaderModule;

class FDevice final : public VulkanObject<VkDevice>
{
	friend class FPhysicalDevice;

	bool Allocate();

public:
	FDevice(FPhysicalDevice& InPhysicalDevice);

	virtual ~FDevice() override;

	TSharedPtr<FQueue> GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex);
	TSharedPtr<FBuffer> CreateBuffer(uint64 InSize, FBufferUsage Usage, TSharedPtr<FConcurrentGuide> ConcurrentGuide = nullptr);
	TSharedPtr<FImage> CreateImage();
	FCommandPool* CreateCommandPool();
	FDescriptorPool* CreateDescriptorPool();
	TSharedPtr<FFence> CreateFence(bool IsDefaultSignaled = false);
	TSharedPtr<FSemaphore> CreateSemaphore();
	TSharedPtr<FEvent> CreateEvent();
	TSharedPtr<FFramebuffer> CreateFramebuffer();
	FPipelineCache* CreatePipelineCache();
	FPipelineLayout* CreatePipelineLayout();
	TSharedPtr<FRenderPass> CreateRenderPass();
	TSharedPtr<FSampler> CreateSampler();
	
	TSharedPtr<FShaderModule> CreateShaderModule();

	FPhysicalDevice& GetPhysicalDevice() const { return GPU; }

private:

	FPhysicalDevice& GPU;
	
	void Test();

};

_KANAS_CORE_END


#endif
