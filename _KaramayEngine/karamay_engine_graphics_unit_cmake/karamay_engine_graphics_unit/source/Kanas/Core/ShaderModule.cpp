#include "ShaderModule.h"
#include "Device.h"

Kanas::Core::FShaderModule::FShaderModule(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FShaderModule::~FShaderModule()
{
	if (IsValid())
	{
		vkDestroyShaderModule(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::FShaderModule::Allocate(const TVector<uint32>& CodeBytes)
{
	VkShaderModuleCreateInfo ShaderModuleCreateInfo{};
	ShaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	ShaderModuleCreateInfo.pNext = nullptr;
	ShaderModuleCreateInfo.flags = {};
	ShaderModuleCreateInfo.codeSize = static_cast<uint32>(CodeBytes.size());
	ShaderModuleCreateInfo.pCode = CodeBytes.data();

	const VkResult Result = vkCreateShaderModule(GetDevice().GetHandle(), &ShaderModuleCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		Code = CodeBytes;
		return true;
	}

	return false;
}
