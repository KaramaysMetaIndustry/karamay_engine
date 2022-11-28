#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class device_memory;
class command_buffer;
class image;

class buffer : public device_object<VkBuffer>
{
	friend class device;

	bool alllocate(std::uint64_t Size, buffer_usage_flags UsageFlags, std::shared_ptr<FConcurrentGuide> InConcurrentGuide = nullptr);

public:

	buffer(device& owner);

	buffer(const buffer& Other) = delete;
	buffer(buffer&& Other) noexcept;

	buffer& operator=(const buffer& Other) = delete;

	virtual ~buffer() override;

public:

	void CmdCopy(command_buffer& InRecorder, buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions);

	void CmdCopyToImage(command_buffer& InRecorder, image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions);

	void CmdFill(command_buffer& InRecorder, std::uint64_t InOffset, std::uint64_t InSize, std::uint32_t InData);

	void CmdUpdate(command_buffer& InRecorder, std::uint64_t InOffset, std::uint64_t InSize, void* InData);

private:

	std::unique_ptr<device_memory> Mem;

};



class FIndexBuffer : public buffer
{
public:

	FIndexBuffer();

	VkIndexType GetIndexType() const;
};


class FVertexBuffer : public buffer
{
public:

	FVertexBuffer();


};

_KANAS_CORE_END

#endif