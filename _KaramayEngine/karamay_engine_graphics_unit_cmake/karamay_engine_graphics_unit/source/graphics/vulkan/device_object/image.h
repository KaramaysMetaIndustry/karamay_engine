#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class command_buffer;
class buffer;

class image final :public device_object<VkImage>
{
public:

	image(device& dev);

	image(const image&) = delete;
	image& operator=(const image&) = delete;

	~image() override;

private:

	VkImageLayout _layout;

public:

	std::shared_ptr<device_memory> memory;

	VkImageLayout layout() const noexcept { return _layout; }

public:

	bool allocate(
		VkFormat format, VkImageType type, uint32 layers, VkExtent3D extent, uint32 mipmaps,
		VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharing, VkSampleCountFlagBits samples, VkImageLayout layout, 
		const std::vector<uint32>& queue_family_indices
	);

	void deallocate();

public:

	void clear(command_buffer* recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void clear(command_buffer* recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void copy_to(command_buffer* recorder, image* dst, const std::vector<VkImageCopy>& regions);

	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferImageCopy>& regions);

	void blit_to(command_buffer* recorder, image* dst, const std::vector<VkImageBlit>& regions, VkFilter filter);

	void resolve_to(command_buffer* recorder, image* dst, const std::vector<VkImageResolve>& regions);

};

#endif