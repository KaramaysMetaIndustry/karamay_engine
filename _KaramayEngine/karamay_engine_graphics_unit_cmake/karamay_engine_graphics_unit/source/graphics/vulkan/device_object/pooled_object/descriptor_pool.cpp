#include "descriptor_pool.h"
#include "descriptor_pool.h"
#include "descriptor_pool.h"
#include "descriptor_set_layout.h"
#include "pooled_object/descriptor_set.h"

void vk_descriptor_pool::_deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyDescriptorPool(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

bool vk_descriptor_pool::allocate(const vk_descriptor_pool_parameters& parameters)
{
	_deallocate();

	if (vkCreateDescriptorPool(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}
	return false;
}

void vk_descriptor_pool::reset(VkDescriptorPoolResetFlags flags) noexcept
{
	if (_handle)
	{
		vkResetDescriptorPool(_dev.handle(), _handle, flags);
	}
}

std::shared_ptr<vk_descriptor_set> vk_descriptor_pool::create_descriptor_set(const vk_descriptor_set_layout& layout) noexcept
{
	auto _obj = std::make_shared<vk_descriptor_set>(_dev, *this);
	if (_obj && _obj->allocate(layout))
	{
		_descriptor_sets.push_back(_obj);
		return _obj;
	}
	return nullptr;
}
