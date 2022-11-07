#ifndef _BUFFER_H_
#define _BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Image;
class CommandBuffer;
class DeviceMemory;

class Buffer final : public DeviceObject<VkBuffer>
{

public:

	Buffer(Device& InDevice);

	virtual ~Buffer();

private:

	std::unique_ptr<DeviceMemory> _Memory;

public:

	void CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions);

	void CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions);

	void CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData);

	void CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData);

};

_KANAS_CORE_END

#endif