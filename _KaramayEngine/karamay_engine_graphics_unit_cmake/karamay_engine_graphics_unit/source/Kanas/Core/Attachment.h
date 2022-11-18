#ifndef _ATTACHMENT_H_
#define _ATTACHMENT_H_

#include "KanasCoreMacros.h"
#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

class FImageView;

struct FAttachmentView
{
	TSharedPtr<FImageView> ImageView;

	VkSampleCountFlagBits SampleCount;

	VkAttachmentLoadOp LoadOp;
	VkAttachmentStoreOp StoreOp;
	VkAttachmentLoadOp StencilLoadOp;
	VkAttachmentStoreOp StencilStoreOp;

};

_KANAS_CORE_END



#endif