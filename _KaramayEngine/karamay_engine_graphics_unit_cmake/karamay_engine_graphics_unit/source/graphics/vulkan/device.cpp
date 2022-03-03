#include "device.h"
#include "device_object/buffer.h"
#include "device_object/buffer_view.h"
#include "device_object/image.h"
#include "device_object/image_view.h"
#include "device_object/command_pool.h"
#include "device_object/descriptor_set.h"
#include "device_object/descriptor_set_layout.h"
#include "device_object/acceleration_structure.h"
#include "device_object/device_memory.h"
#include "device_object/framebuffer.h"
#include "device_object/pipeline.h"
#include "device_object/pipeline_cache.h"
#include "device_object/pipeline_layout.h"
#include "device_object/render_pass.h"
#include "device_object/sampler.h"
#include "device_object/shader_module.h"

std::shared_ptr<buffer> device::create_buffer()
{
	return std::make_shared<buffer>(*this);
}

std::shared_ptr<command_pool> device::create_command_pool()
{
	return std::make_shared<command_pool>(*this);
}

