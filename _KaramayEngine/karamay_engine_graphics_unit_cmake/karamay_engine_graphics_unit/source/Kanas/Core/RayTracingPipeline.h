#ifndef _RAY_TRACING_PIPELINE_H_
#define _RAY_TRACING_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class RayTracingPipeline final : public Pipeline
{
public:

	RayTracingPipeline(Device& InDevice);

	virtual ~RayTracingPipeline();

	virtual void CmdBind(CommandBuffer& InRecorder) override;

	void CmdTraceRays();

	void CmdTraceRaysIndirect();

};

_KANAS_CORE_END

#endif