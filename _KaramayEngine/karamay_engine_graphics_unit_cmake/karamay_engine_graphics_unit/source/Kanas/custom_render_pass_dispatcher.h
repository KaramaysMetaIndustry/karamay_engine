#ifndef _CUSTOM_RENDER_PASS_DISPATCHER_H_
#define _CUSTOM_RENDER_PASS_DISPATCHER_H_

#include "kanas_macros.h"
#include "Core/render_pass.h"
#include "Core/command_buffer.h"
#include "Core/queue.h"
#include "Core/device.h"
#include "Core/framebuffer.h"

_KANAS_BEGIN


class custom_render_pass_dispatcher
{
	kanas::core::device& device;

public:

	custom_render_pass_dispatcher();

	virtual ~custom_render_pass_dispatcher();

	std::vector<std::shared_ptr<kanas::core::render_pass>> passes;

	void tick(float delta_time)
	{
		std::shared_ptr<kanas::core::primary_command_buffer> primary_cmd_buffer;

		for (const auto& pass : passes)
		{
			if (pass->is_dirty())
			{
				primary_cmd_buffer->reset();
				primary_cmd_buffer->record(pass);
			}
		}

	}

	void insert()
	{
		const auto new_pass = device.create_render_pass();

		if (!new_pass)
		{
			return;
		}
	}

};


_KANAS_END

#endif