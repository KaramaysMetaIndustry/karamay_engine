#ifndef _RAY_TRACING_PIPELINE_H_
#define _RAY_TRACING_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class ray_tracing_piepline final : public pipeline
{

	friend class device;

	bool alllocate();

public:

	ray_tracing_piepline(device& owner);

	virtual ~ray_tracing_piepline();

	void CmdTraceRays();

	void CmdTraceRaysIndirect();

};

_KANAS_CORE_END

#endif