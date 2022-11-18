#ifndef _DESCRIPTOR_SET_H_
#define _DESCRIPTOR_SET_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDescriptorPool;
class FDescriptorSetLayout;
class FDescriptorUpdateTemplate;
class FPipeline;


struct FDescriptorImageInfo
{
	TSharedPtr<FImageView> ImageView;
	TSharedPtr<FSampler> Sampler;
};

struct FDescriptorBufferInfo
{
	TSharedPtr<FBuffer> Buffer;
};

class FDescriptorSet final : public FDeviceObject<VkDescriptorSet>
{
	bool Allocate(TSharedPtr<FDescriptorSetLayout> InLayout);

public:

	FDescriptorSet(FDevice& InDevice, FDescriptorPool& InPool);

	FDescriptorSet(const FDescriptorSet&) = delete;
	FDescriptorSet(FDescriptorSet&& Other);

	virtual ~FDescriptorSet() override;

	void Write(uint32 BindingIndex, uint32 ArrayIndex, const TVector<FDescriptorImageInfo>& DescriptorImageInfos);

	void Copy(uint32 SrcBindingIndex, uint32 SrcArrayIndex, TSharedPtr<FDescriptorSet> DstDescriptorSet, uint32 DstBindingIndex, uint32 DstArrayIndex, uint32 CopyNum);

	void Update(TSharedPtr<FDescriptorUpdateTemplate> InTemplate);
	
	void CmdPushDescriptorSet(FCommandBuffer& InRecorder);

	void CmdPushDescriptorSetWithTemplate(FCommandBuffer& InRecorder);
	
	TSharedPtr<FDescriptorSetLayout> GetLayout() const;

private:

	FDescriptorPool& Pool;

	TSharedPtr<FDescriptorSetLayout> Layout;

};

_KANAS_CORE_END


#endif