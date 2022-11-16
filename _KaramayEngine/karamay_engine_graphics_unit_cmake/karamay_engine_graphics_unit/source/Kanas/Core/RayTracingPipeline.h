#ifndef _RAY_TRACING_PIPELINE_H_
#define _RAY_TRACING_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class FRayTracingPipeline final : public FPipeline
{

	friend class FDevice;

	bool Allocate();

public:

	FRayTracingPipeline(FDevice& InDevice);

	virtual ~FRayTracingPipeline();

	virtual void CmdBind(FCommandBuffer& InRecorder) override;

	void CmdTraceRays();

	void CmdTraceRaysIndirect();

};

_KANAS_CORE_END

#endif