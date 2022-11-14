#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Image;
class CommandBuffer;
class DeviceMemory;

struct FConcurrentGuide
{
	TVector<TSharedPtr<Queue>> Queues;
};


class Buffer : public DeviceObject<VkBuffer>
{
	friend class Device;

	bool Allocate(uint64 Size, VkBufferUsageFlags UsageFlags, TSharedPtr<FConcurrentGuide> ConcurrentGuide = nullptr);

public:

	Buffer(Device& InDevice);

	Buffer(const Buffer& Other) = delete;
	Buffer(Buffer&& Other) noexcept;

	Buffer& operator=(const Buffer& Other) = delete;

	virtual ~Buffer() override;

public:

	void CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const TVector<VkBufferCopy>& InRegions);

	void CmdCopyToImage(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkBufferImageCopy>& InRegions);

	void CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData);

	void CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData);

private:

	TUniquePtr<DeviceMemory> Mem;

};


class VertexBuffer : public Buffer {};
class IndexBuffer : public Buffer {};
class UniformBuffer : public Buffer {};
class StorageBuffer : public Buffer {};
class UniformTexelBuffer : public Buffer {};
class StorageTexelBuffer : public Buffer {};
class IndirectBuffer : public Buffer {};
class ShaderDeviceAddress : public Buffer {};

_KANAS_CORE_END

#endif