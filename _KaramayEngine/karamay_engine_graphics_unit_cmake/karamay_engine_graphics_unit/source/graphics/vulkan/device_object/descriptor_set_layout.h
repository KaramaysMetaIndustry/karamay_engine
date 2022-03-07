#ifndef DESCRIPTOR_SET_LAYOUT_H
#define DESCRIPTOR_SET_LAYOUT_H
#include "device_object.h"

class sampler;

class descriptor_set_layout final : public device_object<VkDescriptorSetLayout>
{
public:

	descriptor_set_layout(device& dev);

	descriptor_set_layout(const descriptor_set_layout&) = delete;
	descriptor_set_layout& operator=(const descriptor_set_layout&) = delete;

	~descriptor_set_layout() override;

private:

	std::vector<VkDescriptorSetLayoutBinding> _bindings;

public:

	const std::vector<VkDescriptorSetLayoutBinding>& bindings() const noexcept { return _bindings; }

public:

	bool allocate(const std::vector<VkDescriptorSetLayoutBinding>& bindings) noexcept;

	void deallocate() noexcept;

public:

	void s()
	{
		vkCmdBindDescriptorSets;
		vkCmdPushDescriptorSetKHR;
		vkCmdPushDescriptorSetWithTemplateKHR;
	}

};

#endif