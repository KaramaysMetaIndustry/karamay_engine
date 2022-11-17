#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDeviceMemory;
class FCommandBuffer;
class FImage;

class FBuffer : public FDeviceObject<VkBuffer>
{
	friend class FDevice;

	bool Allocate(uint64 Size, FBufferUsageFlags UsageFlags, TSharedPtr<FConcurrentGuide> InConcurrentGuide = nullptr);

public:

	FBuffer(FDevice& InDevice);

	FBuffer(const FBuffer& Other) = delete;
	FBuffer(FBuffer&& Other) noexcept;

	FBuffer& operator=(const FBuffer& Other) = delete;

	virtual ~FBuffer() override;

public:

	void CmdCopy(FCommandBuffer& InRecorder, FBuffer& InDstBuffer, const TVector<VkBufferCopy>& InRegions);

	void CmdCopyToImage(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkBufferImageCopy>& InRegions);

	void CmdFill(FCommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData);

	void CmdUpdate(FCommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData);

private:

	TUniquePtr<FDeviceMemory> Mem;

};



class FIndexBuffer : public FBuffer
{
public:

	FIndexBuffer();

	VkIndexType GetIndexType() const;
};


class FVertexBuffer : public FBuffer
{
public:

	FVertexBuffer();


};

_KANAS_CORE_END

#endif