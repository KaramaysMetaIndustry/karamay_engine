#ifndef _KANAS_CORE_TYPES_H_
#define _KANAS_CORE_TYPES_H_

#include "public/stl.h"
#include "public/vulkan_core.h"

#include "KanasCoreMacros.h"

_KANAS_CORE_BEGIN

template<typename T>
using TUniquePtr = std::unique_ptr<T>;

template<typename T>
using TSharedPtr = std::shared_ptr<T>;

template<typename T>
using TWeakPtr = std::weak_ptr<T>;

template<typename T, size_t Num>
using TArray = std::array<T, Num>;

template<typename T>
using TVector = std::vector<T>;

template<typename K, typename V>
using TMap = std::map<K, V>;

template<typename K, typename V>
using TUnorderedMap = std::unordered_map<K, V>;

template<typename T>
using TSet = std::set<T>;

template<typename T>
using TUnorderedSet = std::unordered_set<T>;

template<typename K, typename V>
using TMultimap = std::multimap<K, V>;

template<typename K, typename V>
using TUnorderedMultimap = std::unordered_multimap<K, V>;


template <class _Ty, class... _Types>
TSharedPtr<_Ty> MakeShared(_Types&&... _Args) {
	return std::make_shared<_Ty, _Types>;
}

template <class _Ty, class... _Types>
TUniquePtr<_Ty> MakeUnique(_Types&&... _Args)
{
	std::make_unique<_Ty>(_Args);
}

template<typename T>
std::remove_reference_t<T>&& MoveTemp(T&& _Arg)
{
	return std::move(_Arg);
}

template<typename FLAF_T>
struct FVulkanFlags
{
	VkFlags GetFlags() const
	{
		return Flags;
	}

	void Reset()
	{
		Flags = 0;
	}

	void Clone(FLAF_T InFlags)
	{
		Flags = InFlags;
	}

protected:

	VkFlags Flags{ 0 };
};

#define DECAL_FLAG(FUNCTION_NAME, VK_BIT)\
auto& FUNCTION_NAME##(bool bActive = true)\
{\
	Flags |= bActive ? VK_BIT : 0;\
	return *this;\
}\
bool Is##FUNCTION_NAME##Active() const\
{\
	return Flags & VK_BIT;\
}

struct FMemoryProperty : public FVulkanFlags<FMemoryProperty>
{
	DECAL_FLAG(DeviceLocal,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	DECAL_FLAG(HostVisible,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
	DECAL_FLAG(HostCoherent,VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	DECAL_FLAG(HostCached,VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
	DECAL_FLAG(LazilyAllocated,VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
	DECAL_FLAG(Protected,VK_MEMORY_PROPERTY_PROTECTED_BIT)
};

struct FImageUsage : public FVulkanFlags<FImageUsage>
{
	DECAL_FLAG(TransferSrc, VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(TransferDst, VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(Sampled, VK_IMAGE_USAGE_SAMPLED_BIT)
	DECAL_FLAG(Storage, VK_IMAGE_USAGE_STORAGE_BIT)
	DECAL_FLAG(ColorAttachment, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
	DECAL_FLAG(DepthStencilAttachment, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
	DECAL_FLAG(TransientAttachment, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
	DECAL_FLAG(InputAttachment, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
};

struct FBufferUsage : public FVulkanFlags<FBufferUsage>
{
	DECAL_FLAG(TransferSrc, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(TransferDst, VK_BUFFER_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(UniformTexelBuffer, VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
	DECAL_FLAG(UniformTexelBuffer, VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
	DECAL_FLAG(StorageTexelBuffer, VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT)
	DECAL_FLAG(UniformBuffer, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
	DECAL_FLAG(StorageBuffer, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
	DECAL_FLAG(IndexBuffer, VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
	DECAL_FLAG(VertexBuffer, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
	DECAL_FLAG(IndirectBuffer, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT)
	DECAL_FLAG(ShaderDeviceAddress, VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
};

struct FConcurrentGuide
{
	void GetConcurrentFamilyIndices(TVector<uint32>& OutFamilyIndices) const
	{

	}

	bool DoesSupportConcurrency() const
	{
		return false;
	}

	FConcurrentGuide(const TVector<TSharedPtr<class FQueue>>& InQueues) :
		ConcurrentQueues(InQueues)
	{
	}

private:

	TVector<TSharedPtr<class FQueue>> ConcurrentQueues;

	static const FConcurrentGuide& StaticConstRef;

};

const FConcurrentGuide& FConcurrentGuide::StaticConstRef = FConcurrentGuide({});

_KANAS_CORE_END

#endif