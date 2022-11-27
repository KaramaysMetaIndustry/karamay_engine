#ifndef _RAY_TRACING_PIPELINE_H_
#define _RAY_TRACING_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class ray_tracing_pipeline final : public pipeline
{

	friend class device;

	bool allocate();

public:

	ray_tracing_pipeline(device& owner);

	virtual ~ray_tracing_pipeline();

	void CmdTraceRays();

	void CmdTraceRaysIndirect();

};

_KANAS_CORE_END

#endif