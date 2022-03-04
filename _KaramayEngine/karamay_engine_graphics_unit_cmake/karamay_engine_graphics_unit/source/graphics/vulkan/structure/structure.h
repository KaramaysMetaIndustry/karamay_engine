#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "public/vulkan_core.h"
#include "public/stl.h"

class semaphore;
class command_buffer;

struct submit_info
{
	std::vector<semaphore*> wait_semaphores;
	std::vector<semaphore*> signal_semaphores;
	std::vector<command_buffer*> command_buffers;
	VkPipelineStageFlags wait_dst_stage;
};


#endif