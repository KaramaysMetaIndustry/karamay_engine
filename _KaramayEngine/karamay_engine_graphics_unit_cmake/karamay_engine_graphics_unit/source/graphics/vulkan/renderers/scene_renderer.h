#ifndef SCENE_RENDERER_H
#define SCENE_RENDERER_H
#include "renderer.h"

class scene_renderer final : public vk_renderer
{



public:

	void render(float delta_time) noexcept override
	{
		vk_buffer_parameters _parameters;
		auto _global_dynamic_index_buffer = _device.create_buffer(_parameters);

		auto _index_buffer = _device.create_buffer(_parameters);
		auto _vertex_buffer = _device.create_buffer(_parameters);

		auto command_pool = _device.create_command_pool({});
		auto cmd_buf = command_pool->create_command_buffer({});
	
	
		_global_dynamic_index_buffer->fill(*cmd_buf, 0, 100, 8);
		_global_dynamic_index_buffer->update(*cmd_buf, 0, 100, nullptr);
		_global_dynamic_index_buffer->copy_to(*cmd_buf, *_index_buffer, {});

	
	}
};

#endif