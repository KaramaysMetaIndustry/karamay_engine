#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class command_buffer;
class buffer;

class image final :public device_object<VkImage>
{

	VkImageLayout _layout;

	std::unique_ptr<device_memory> _memory;

public:

	image(device& dev, VkFormat format, VkImageType type, uint32 layers, VkExtent3D extent, uint32 mipmaps,
		VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharing, VkSampleCountFlagBits samples, VkImageLayout layout,
		const std::vector<uint32>& queue_family_indices) noexcept
		: device_object(dev)
	{
		VkImageCreateInfo _create_info
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.imageType = type,
			.format = format,
			.extent = extent,
			.mipLevels = mipmaps,
			.arrayLayers = layers,
			.samples = samples,
			.tiling = tiling,
			.usage = usage,
			.sharingMode = sharing,
			.queueFamilyIndexCount = static_cast<uint32_t>(queue_family_indices.size()),
			.pQueueFamilyIndices = queue_family_indices.data(),
			.initialLayout = layout
		};

		auto _result = vkCreateImage(_dev.handle(), &_create_info, nullptr, &_handle);
		
		VkMemoryRequirements _requirements{};
		vkGetImageMemoryRequirements(_dev.handle(), _handle, &_requirements);
		_memory = std::make_unique<device_memory>(_dev, _requirements);

	}

	image(const image&) = delete;
	image& operator=(const image&) = delete;

	~image() override;

public:

	VkImageLayout layout() const noexcept { return _layout; }

	void clear(command_buffer& recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void clear(command_buffer& recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void copy_to(command_buffer& recorder, image& dst, const std::vector<VkImageCopy>& regions);

	void copy_to(command_buffer& recorder, buffer& dst, const std::vector<VkBufferImageCopy>& regions);

	void blit_to(command_buffer& recorder, image& dst, const std::vector<VkImageBlit>& regions, VkFilter filter);

	void resolve_to(command_buffer& recorder, image& dst, const std::vector<VkImageResolve>& regions);

};


class image_view final : public device_object<VkImageView>
{

	image& _target;

public:

	image_view(device& dev, image& img, VkImageViewType view_t, VkFormat format, VkComponentMapping components, VkImageSubresourceRange subresource_range) : device_object(dev), _target(img)
	{
		VkImageViewCreateInfo _create_info
		{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.image = img.handle(),
			.viewType = view_t,
			.format = format,
			.components = components,
			.subresourceRange = subresource_range
		};
		vkCreateImageView(_dev.handle(), &_create_info, nullptr, &_handle);
	}

	image_view(const image_view&) = delete;
	image_view& operator=(const image_view&) = delete;

	~image_view() noexcept override;

public:

	void _deallocate() noexcept;

};

#endif