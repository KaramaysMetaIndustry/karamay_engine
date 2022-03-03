#ifndef PIPELINE_H
#define PIPELINE_H
#include "device_object.h"

class command_buffer;
class pipeline_cache;
class pipeline_layout;


class pipeline : public device_object<VkPipeline>
{
public:
	pipeline(device& dev);

	void deallocate();

protected:

	std::shared_ptr<pipeline_cache> _cache;

	std::shared_ptr<pipeline_layout> _layout;

};

class graphics_pipeline final : public pipeline
{
public:

	graphics_pipeline(device& dev);

	~graphics_pipeline() override;

public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

public:

	void draw(command_buffer* recorder, uint32 vertex_count, uint32 instance_count, uint32 first_vertex, uint32 first_instance);

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

public:

	void draw(command_buffer* recorder);

	void draw_indirect(command_buffer* recorder);

};

class compute_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

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

	bool allocate(
		pipeline_cache* cache, pipeline_layout* layout, 
		uint32 max_ray_recursion_depth
	);

public:

	void trace_rays(command_buffer* recorder);

	void trace_rays_indirect(command_buffer* recorder);

};

#endif