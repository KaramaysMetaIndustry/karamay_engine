#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class FPhysicalDevice;

class FQueue;

class FDeviceMemory;

class FBuffer;
class FBufferView;
class FImage;
class FImageView;

class FFramebuffer;

class FDescriptorPool;
class FDescriptorSetLayout;

class FSampler;
class FShaderModule;
class FPipelineCache;
class FPipelineLayout;
class FRenderPass;

class FFence;
class FSemaphore;
class FEvent;

class FCommandPool;

class FDevice final : public VulkanObject<VkDevice>
{
	friend class FPhysicalDevice;

	bool Allocate();

public:

	FDevice(FPhysicalDevice& InPhysicalDevice);

	FDevice(const FDevice&) = delete;
	FDevice& operator=(const FDevice&) = delete;

	virtual ~FDevice() override;

	TSharedPtr<FQueue> GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex);
	
	
	TSharedPtr<FBuffer> CreateBuffer(uint64 Size, FBufferUsage Usage, TSharedPtr<FConcurrentGuide> ConcurrentGuide = nullptr);
	
	TSharedPtr<FBufferView> CreateBufferView(TSharedPtr<FBuffer> Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range);
	
	TSharedPtr<FImage> CreateImage();
	
	TSharedPtr<FImageView> CreateImageView(TSharedPtr<FImage> Image, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);


	TSharedPtr<FFramebuffer> CreateFramebuffer();


	FDescriptorPool* CreateDescriptorPool();

	TSharedPtr<FShaderModule> CreateShaderModule();
	
	TSharedPtr<FPipelineCache> CreatePipelineCache();
	
	TSharedPtr<FPipelineLayout> CreatePipelineLayout();
	
	TSharedPtr<FRenderPass> CreateRenderPass();


	FCommandPool* CreateCommandPool();


	TSharedPtr<FFence> CreateFence(bool IsDefaultSignaled = false);
	
	TSharedPtr<FSemaphore> CreateSemaphore();
	
	TSharedPtr<FEvent> CreateEvent();
	
	TSharedPtr<FSampler> CreateSampler();


	FPhysicalDevice& GetPhysicalDevice() const { return GPU; }

private:

	FPhysicalDevice& GPU;
	
	void Test();

};

_KANAS_CORE_END


#endif
