#include "Buffer.h"
#include "Device.h"
#include "PhysicalDevice.h"
#include "CommandBuffer.h"
#include "Semaphore.h"
#include "Image.h"
#include "DeviceMemory.h"

bool Kanas::Core::Buffer::Allocate(VkDeviceSize InSize, VkBufferUsageFlags InUsageFlags, VkSharingMode InSharingMode)
{

	VkBufferUsageFlags BufferUsageFlags = 0;
	VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	VkBufferUsageFlagBits::VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	VkBufferUsageFlagBits::VK_BUFFER_USAGE_TRANSFER_SRC_BIT;

	VkSharingMode::VK_SHARING_MODE_CONCURRENT; // concurrent
	VkSharingMode::VK_SHARING_MODE_EXCLUSIVE; // exclusive

	VkBufferCreateInfo BufferCreateInfo;
	BufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = {} ;
	BufferCreateInfo.size = InSize;
	BufferCreateInfo.usage = InUsageFlags;
	BufferCreateInfo.sharingMode = InSharingMode;
	BufferCreateInfo.queueFamilyIndexCount = 0;
	BufferCreateInfo.pQueueFamilyIndices = nullptr;

	const VkResult CreateBufferResult = vkCreateBuffer(GetDevice().GetHandle(), &BufferCreateInfo, nullptr, &_Handle);
	
	if (CreateBufferResult == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemRequirements;
		vkGetBufferMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemRequirements);

		const uint64 MemAllocSize = MemRequirements.size;
		const uint32 MemTypeIndex = 0;

		Mem = GetDevice().CreateDeviceMemory(MemAllocSize, MemTypeIndex);

		if (Mem)
		{
			const VkResult BindBufferResult = vkBindBufferMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), 0);

			if (BindBufferResult == VkResult::VK_SUCCESS)
			{
				return true;
			}
		}
	}

	Mem = nullptr;

	return false;
}

struct MemoryHeapDescription
{
	bool IsDeviceLocal;
	bool IsHostVisible;
	bool IsHostCoherent;
	bool IsHostCached;
	bool IsLazilyAllocated;
	bool IsProtected;
};

struct MemoryHeap
{
	VkDeviceSize Size;

	bool IsDeviceLocal;
	bool IsMultiInstance;

	std::vector<MemoryHeapDescription> Descriptions;
};

Kanas::Core::Buffer::Buffer(Device& InDevice) :
	DeviceObject(InDevice)
{
	VkPhysicalDeviceMemoryProperties MemProperties;
	GetDevice().GetPhysicalDevice().GetMemoryProperties(MemProperties);

	VkPhysicalDeviceFeatures Features;
	GetDevice().GetPhysicalDevice().GetFeatures(Features);


	MemProperties.memoryTypes[0].heapIndex;
	MemProperties.memoryTypes[0].propertyFlags;

	VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT; // DeviceLocal
	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT; // HostVisible
	VK_MEMORY_PROPERTY_HOST_COHERENT_BIT; // HostCoherent
	VK_MEMORY_PROPERTY_HOST_CACHED_BIT; // HostCached
	VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT; // LazilyAllocated
	VK_MEMORY_PROPERTY_PROTECTED_BIT; // Protected
	//VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD;
	//VkMemoryPropertyFlagBits::VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD;


	MemProperties.memoryHeaps[0].size;
	MemProperties.memoryHeaps[0].flags;

	VkMemoryHeapFlagBits::VK_MEMORY_HEAP_DEVICE_LOCAL_BIT; // DeviceLocal
	VkMemoryHeapFlagBits::VK_MEMORY_HEAP_MULTI_INSTANCE_BIT; // MultiInstance


}

Kanas::Core::Buffer::~Buffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::Buffer::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions)
{
	vkCmdCopyBuffer(InRecorder.GetHandle(), GetHandle(), InDstBuffer.GetHandle(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::Buffer::CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyBufferToImage(InRecorder.GetHandle(), GetHandle(), InDstImage.GetHandle(), VkImageLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::Buffer::CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData)
{
}

void Kanas::Core::Buffer::CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData)
{
}
