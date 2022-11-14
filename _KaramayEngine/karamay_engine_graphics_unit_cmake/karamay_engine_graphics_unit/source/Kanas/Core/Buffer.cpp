#include "Buffer.h"
#include "Device.h"
#include "PhysicalDevice.h"
#include "CommandBuffer.h"
#include "Semaphore.h"
#include "Image.h"
#include "DeviceMemory.h"

bool Kanas::Core::Buffer::Allocate(uint64 Size, VkBufferUsageFlags UsageFlags, TSharedPtr<FConcurrentGuide> ConcurrentGuide)
{
	VkBufferUsageFlags BufferUsageFlags = 0;
	VK_BUFFER_USAGE_TRANSFER_SRC_BIT; // TransferSrc
	VK_BUFFER_USAGE_TRANSFER_DST_BIT, // TransferDst
		VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT, // UniformTexelBufer
		VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT, // StorageTexelBuffer
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, // UniformBuffer
		VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, // StorageBuffer
		VK_BUFFER_USAGE_INDEX_BUFFER_BIT, // IndexBuffer
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, // VertexBuffer
		VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT, // IndirectBuffer
		VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT; // ShaderDeviceAddress

	VkBufferCreateInfo BufferCreateInfo;
	BufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = {} ;
	BufferCreateInfo.size = Size;
	BufferCreateInfo.usage = UsageFlags;
	
	if (ConcurrentGuide && ConcurrentGuide->Queues.size())
	{
		TVector<uint32> QueueFamilyIndices;

		BufferCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		BufferCreateInfo.queueFamilyIndexCount = static_cast<uint32>(QueueFamilyIndices.size());
		BufferCreateInfo.pQueueFamilyIndices = QueueFamilyIndices.data();
	}
	else {
		BufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		BufferCreateInfo.queueFamilyIndexCount = 0;
		BufferCreateInfo.pQueueFamilyIndices = nullptr;
	}

	const VkResult CreateBufferResult = vkCreateBuffer(GetDevice().GetHandle(), &BufferCreateInfo, nullptr, &_Handle);
	
	if (CreateBufferResult == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemRequirements;
		vkGetBufferMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemRequirements);

		const uint64 MemAllocSize = MemRequirements.size;
		const uint32 MemTypeIndex = 0;

		TUniquePtr<DeviceMemory> NewMem = std::make_unique<DeviceMemory>(GetDevice());
		if (NewMem && NewMem->Allocate(MemAllocSize, MemTypeIndex))
		{
			const VkResult BindBufferResult = vkBindBufferMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), 0);

			if (BindBufferResult == VkResult::VK_SUCCESS)
			{
				Mem = std::move(NewMem);
				return true;
			}
		}
	}

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

Kanas::Core::Buffer::Buffer(Buffer&& Other) noexcept :
	DeviceObject(Other.GetDevice())
{
	_Handle = Other.GetHandle();
	Other.ResetHandle();
}

Kanas::Core::Buffer::~Buffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::Buffer::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const TVector<VkBufferCopy>& InRegions)
{
	vkCmdCopyBuffer(InRecorder.GetHandle(), GetHandle(), InDstBuffer.GetHandle(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::Buffer::CmdCopyToImage(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyBufferToImage(InRecorder.GetHandle(), GetHandle(), InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::Buffer::CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData)
{
	vkCmdFillBuffer(InRecorder.GetHandle(), GetHandle(), InOffset, InSize, InData);
}

void Kanas::Core::Buffer::CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData)
{
	vkCmdUpdateBuffer(InRecorder.GetHandle(), GetHandle(), InOffset, InSize, InData);
}
