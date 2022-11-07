#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Buffer;
class ShaderModule;
class PipelineLayout;
class PipelineCache;

class Pipeline : public DeviceObject<VkPipeline>
{
public:

	Pipeline(Device& InDevice);

	virtual ~Pipeline();

	virtual void CmdBind(CommandBuffer& InRecorder);

};

_KANAS_CORE_END

#endif