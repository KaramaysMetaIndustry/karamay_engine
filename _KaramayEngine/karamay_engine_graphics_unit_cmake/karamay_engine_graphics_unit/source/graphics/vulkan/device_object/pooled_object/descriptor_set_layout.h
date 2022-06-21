#ifndef DESCRIPTOR_SET_LAYOUT_H
#define DESCRIPTOR_SET_LAYOUT_H
#include "device_object.h"

class vk_sampler;

class vk_descriptor_set_layout final : public device_object<VkDescriptorSetLayout>
{

	std::vector<VkDescriptorSetLayoutBinding> _bindings;

public:

	vk_descriptor_set_layout(vk_device& dev);

	vk_descriptor_set_layout(const vk_descriptor_set_layout&) = delete;
	vk_descriptor_set_layout& operator=(const vk_descriptor_set_layout&) = delete;

	~vk_descriptor_set_layout() override;

public:

	bool allocate(const std::vector<VkDescriptorSetLayoutBinding>& bindings) noexcept;

	void deallocate() noexcept;

	const std::vector<VkDescriptorSetLayoutBinding>& bindings() const noexcept { return _bindings; }

public:

	void s()
	{
		vkCmdBindDescriptorSets;
		vkCmdPushDescriptorSetKHR;
		vkCmdPushDescriptorSetWithTemplateKHR;
	}

};

#endif