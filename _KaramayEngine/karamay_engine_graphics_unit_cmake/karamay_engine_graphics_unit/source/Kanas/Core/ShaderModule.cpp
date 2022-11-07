#include "ShaderModule.h"
#include "Device.h"

Kanas::Core::ShaderModule::ShaderModule(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::ShaderModule::~ShaderModule()
{
	if (IsValid())
	{
		vkDestroyShaderModule(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::ShaderModule::Allocate()
{
	VkShaderModuleCreateInfo ShaderModuleCreateInfo;
	ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderModuleCreateInfo.pNext = nullptr;
	ShaderModuleCreateInfo.flags = {};
	ShaderModuleCreateInfo.codeSize;
	ShaderModuleCreateInfo.pCode;

	VkResult Result = vkCreateShaderModule(GetDevice().GetHandle(), &ShaderModuleCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}
