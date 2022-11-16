#ifndef _DESCRIPTOR_SET_H_
#define _DESCRIPTOR_SET_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDescriptorPool;
class FDescriptorSetLayout;
class FDescriptorUpdateTemplate;
class FPipeline;

class FDescriptorSet final : public FDeviceObject<VkDescriptorSet>
{
	bool Allocate(TSharedPtr<FDescriptorSetLayout> InLayout);

public:

	FDescriptorSet(FDevice& InDevice, FDescriptorPool& InPool);

	virtual ~FDescriptorSet();

	TSharedPtr<FDescriptorSetLayout> GetLayout() const;

	void Update();

	void UpdateImage();

	void UpdateImageView();

	void UpdateBuffer();

	void UpdateBufferView();

	void Update(TSharedPtr<FDescriptorUpdateTemplate> InTemplate);

	
	void CmdBind(FCommandBuffer& InRecorder, TSharedPtr<FPipeline> InPipeline);
	void CmdPushDescriptorSet(FCommandBuffer& InRecorder);
	void CmdPushDescriptorSetWithTemplate(FCommandBuffer& InRecorder);

private:

	FDescriptorPool& Pool;

	TSharedPtr<FDescriptorSetLayout> Layout;

};

_KANAS_CORE_END


#endif