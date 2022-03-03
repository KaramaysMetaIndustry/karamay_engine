#ifndef PIPELINE_H
#define PIPELINE_H
#include "device_object.h"

class pipeline_cache;
class pipeline_layout;
class command_buffer;

class pipeline : public device_object<VkPipeline>
{

};

class graphics_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

	void deallocate();

public:

	void draw(command_buffer* recorder);

	void draw_indirect(command_buffer* recorder);

	void draw_indirect_count(command_buffer* recorder);

	void draw_indexed(command_buffer* recorder);

	void draw_indexed_indirect(command_buffer* recorder);

	void draw_indexed_indirect_count(command_buffer* recorder);

};

class mesh_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

	void deallocate();

public:

	void draw(command_buffer* recorder);

	void draw_indirect(command_buffer* recorder);

};

class compute_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

	void deallocate();

public:

	void dispatch(command_buffer* recorder)
	{

	}

	void dispatch_base(command_buffer* recorder)
	{

	}

	void dispatch_indirect(command_buffer* recorder)
	{

	}

};

class ray_tracing_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

	void deallocate();

public:

	void trace_rays(command_buffer* recorder);

	void trace_rays_indirect(command_buffer* recorder);

};

#endif