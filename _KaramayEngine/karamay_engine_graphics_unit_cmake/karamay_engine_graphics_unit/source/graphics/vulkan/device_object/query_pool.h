#ifndef QUERY_POOL_H
#define QUERY_POOL_H
#include "device_object.h"

class vk_command_buffer;

class vk_query_pool final : public device_object<VkQueryPool>
{
	void _deallocate();

public:

	vk_query_pool(vk_device& dev) :
		device_object(dev)
	{}

	vk_query_pool(const vk_query_pool&) = delete;
	vk_query_pool& operator=(const vk_query_pool&) = delete;

	~vk_query_pool() override
	{
		_deallocate();
	}

	bool allocate(const vk_query_pool_parameters& parameters);

	void reset(vk_command_buffer* recorder, uint32 first_query, uint32 query_count);

	void copy_results(vk_command_buffer* recorder, uint32 first_query, uint32 query_count, vk_buffer* dst, uint64 offset, uint64 stride, VkQueryResultFlags flags);

	void begin(vk_command_buffer* recorder, uint32 index, VkQueryControlFlags flags);

	void end(vk_command_buffer* recorder, uint32 index);

};

#endif