#ifndef DESCRIPTOR_SET_LAYOUT_H
#define DESCRIPTOR_SET_LAYOUT_H
#include "../device_object.h"

class vk_sampler;

class vk_descriptor_set_layout final : public device_object<VkDescriptorSetLayout>
{
	std::vector<VkDescriptorSetLayoutBinding> _bindings;

	void _deallocate() noexcept;

public:

	vk_descriptor_set_layout(vk_device& dev) :
		device_object(dev)
	{}

	vk_descriptor_set_layout(const vk_descriptor_set_layout&) = delete;
	vk_descriptor_set_layout& operator=(const vk_descriptor_set_layout&) = delete;

	~vk_descriptor_set_layout() override
	{
		_deallocate();
	}

	bool allocate(const vk_descriptor_set_layout_parameters& parameters) noexcept;

	void s()
	{
		vkCmdBindDescriptorSets;
		vkCmdPushDescriptorSetKHR;
		vkCmdPushDescriptorSetWithTemplateKHR;
	}

};

#endif