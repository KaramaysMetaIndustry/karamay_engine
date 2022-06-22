#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class vk_command_buffer;
class vk_buffer;

class vk_image final :public device_object<VkImage>
{
	VkImageLayout _layout;

	std::shared_ptr<vk_device_memory> _memory;

public:

	vk_image(vk_device& dev) noexcept
		: device_object(dev)
	{}

	vk_image(const vk_image&) = delete;
	vk_image& operator=(const vk_image&) = delete;

	~vk_image() override;

public:

	bool allocate(const vk_image_parameters& parameters);

	std::shared_ptr<vk_image_view> create_view(const vk_image_view_parameters& parameters) noexcept;

	VkImageLayout layout() const noexcept { return _layout; }

public:

	void clear(vk_command_buffer& recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void clear(vk_command_buffer& recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges);

	void copy_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageCopy>& regions);

	void copy_to(vk_command_buffer& recorder, vk_buffer& dst, const std::vector<VkBufferImageCopy>& regions);

	void blit_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageBlit>& regions, VkFilter filter);

	void resolve_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageResolve>& regions);

private:

	void _deallocate() noexcept;

};

class vk_image_view final : public device_object<VkImageView>
{
	vk_image& _target;

public:

	vk_image_view(vk_device& dev, vk_image& image) 
		: device_object(dev), _target(image)
	{
	}

	vk_image_view(const vk_image_view&) = delete;
	vk_image_view& operator=(const vk_image_view&) = delete;

	~vk_image_view() noexcept override;

public:

	bool allocate(const vk_image_view_parameters& parameters);

private:

	void _deallocate() noexcept;

};

#endif