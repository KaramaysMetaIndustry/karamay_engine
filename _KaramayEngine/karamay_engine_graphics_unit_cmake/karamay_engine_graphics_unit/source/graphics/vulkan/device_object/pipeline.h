#ifndef PIPELINE_H
#define PIPELINE_H
#include "device_object.h"

class pipeline_cache;
class pipeline_layout;
class buffer;
class deferred_operation;
class command_buffer;

class pipeline : public device_object<VkPipeline>
{
public:
	pipeline(device& dev);

	pipeline(const pipeline&) = delete;
	pipeline& operator=(const pipeline&) = delete;

	~pipeline() override;

public:

	void deallocate();

protected:

	std::shared_ptr<pipeline_cache> _cache;

	std::shared_ptr<pipeline_layout> _layout;

public:

	void bind(command_buffer* recorder, VkPipelineBindPoint bind_point);

};

class graphics_pipeline final : public pipeline
{
public:

	graphics_pipeline(device& dev);

	graphics_pipeline(const graphics_pipeline&) = delete;
	graphics_pipeline& operator=(const graphics_pipeline&) = delete;

	~graphics_pipeline() override;

public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

	bool allocate(pipeline_cache*);

public:

	void draw(command_buffer* recorder, uint32 vertex_count, uint32 instance_count, uint32 first_vertex, uint32 first_instance);

	void draw_indirect(command_buffer* recorder, buffer* buf, uint64 size, uint32 draw_count, uint32 stride);

	void draw_indirect_count(command_buffer* recorder, buffer* buf, uint64 offset, buffer* count_buf, uint64 count_offset, uint32 max_draw_count, uint32 stride);

	void draw_indexed(command_buffer* recorder, uint32 index_count, uint32 instance_count, uint32 first_index, int32 vertex_offset, uint32 first_instance);

	void draw_indexed_indirect(command_buffer* recorder, buffer* buf, uint64 size, uint32 draw_count, uint32 stride);

	void draw_indexed_indirect_count(command_buffer* recorder, buffer* buf, uint64 offset, buffer* count_buf, uint64 count_offset, uint32 max_draw_count, uint32 stride);

};

class mesh_pipeline final : public pipeline
{
public:

	bool allocate(pipeline_cache* cache, pipeline_layout* layout);

public:

	void draw(command_buffer* recorder, uint32 task_count, uint32 first_task);

	void draw_indirect(command_buffer* recorder, buffer* buf, uint64 size, uint32 draw_count, uint32 stride);

	void draw_indirect_count(command_buffer* recorder);

};

class compute_pipeline final : public pipeline
{
public:

	compute_pipeline(device&  dev);

	compute_pipeline(const compute_pipeline&) = delete;
	compute_pipeline& operator=(const compute_pipeline&) = delete;

	~compute_pipeline() override;

public:

	bool allocate(
		pipeline_cache* cache, 
		pipeline_layout* layout, 
		shader_module* compute_shader_module
	);

public:

	/*
	* 
	*/
	void dispatch(
		command_buffer* recorder, 
		uint32 group_count_x, uint32 group_count_y, uint32 group_count_z
	);

	/*
	* 
	*/
	void dispatch_base(
		command_buffer* recorder, 
		uint32 base_group_x, uint32 base_group_y, uint32 base_group_z, 
		uint32 group_count_x, uint32 group_count_y, uint32 group_count_z
	);

	/*
	* 
	*/
	void dispatch_indirect(
		command_buffer* recorder, 
		buffer* buf, uint64 size
	);

};

class ray_tracing_pipeline final : public pipeline
{
public:

	ray_tracing_pipeline(device& dev);

	ray_tracing_pipeline(const ray_tracing_pipeline&) = delete;
	ray_tracing_pipeline& operator=(const ray_tracing_pipeline&) = delete;

	~ray_tracing_pipeline() override;

public:

	bool allocate(
		pipeline_cache* cache, 
		pipeline_layout* layout, 
		deferred_operation* deferred_op, uint32 max_ray_recursion_depth
	);

public:

	void trace_rays(
		command_buffer* recorder, 
		uint32 width, uint32 height, uint32 depth
	);

	void trace_rays_indirect(
		command_buffer* recorder
	);

};

#endif