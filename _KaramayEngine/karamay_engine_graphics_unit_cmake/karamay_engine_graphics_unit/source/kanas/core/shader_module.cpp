#include "shader_module.h"
#include "device.h"

kanas::core::shader_module::shader_module(device& owner) :
	deviceObject(owner)
{
}

kanas::core::shader_module::~shader_module()
{
	if (IsValid())
	{
		vkDestroyShaderModule(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::shader_module::alllocate(const std::vector<std::uint32_t>& CodeBytes)
{
	VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
	ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderModuleCreateInfo.pNext = nullptr;
	ShaderModuleCreateInfo.flags = {};
	ShaderModuleCreateInfo.codeSize = static_cast<std::uint32_t>(CodeBytes.size());
	ShaderModuleCreateInfo.pCode = CodeBytes.data();

	const VkResult Result = vkCreateShaderModule(get_device().get_handle(), &ShaderModuleCreateInfo, nullptr, &handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		Code = CodeBytes;
		return true;
	}

	return false;
}
