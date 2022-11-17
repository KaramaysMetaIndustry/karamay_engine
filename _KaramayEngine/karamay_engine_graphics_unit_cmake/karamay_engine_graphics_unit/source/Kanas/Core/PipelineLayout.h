#ifndef _PIPELINE_LAYOUT_H_
#define _PIPELINE_LAYOUT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDescriptorSetLayout;

enum class EShaderVarType
{
	vec2,
	vec3,
	vec4,

	mat2,
	mat2x3,
	mat2x4,

	mat3x2,
	mat3,
	mat3x4,

	mat4x2,
	mat4x3,
	mat4,
	
};

class FPipelineLayout final : public FDeviceObject<VkPipelineLayout>
{
	friend class FDevice;

	bool Allocate(
		const TVector<TSharedPtr<FDescriptorSetLayout>>& InDescriptorSetLayouts, 
		const TVector<VkPushConstantRange>& InPushConstantRanges = {}
	);

public:

	FPipelineLayout(FDevice& InDevice);

	virtual ~FPipelineLayout() override;

	TSharedPtr<FDescriptorSetLayout> GetDescriptorSetLayout(uint32 SetIndex) const;

	const TVector<TSharedPtr<FDescriptorSetLayout>>& GetDescriptorSetLayouts() const;

private:

	TVector<TSharedPtr<FDescriptorSetLayout>> DescriptorSetLayouts;

};


_KANAS_CORE_END

#endif