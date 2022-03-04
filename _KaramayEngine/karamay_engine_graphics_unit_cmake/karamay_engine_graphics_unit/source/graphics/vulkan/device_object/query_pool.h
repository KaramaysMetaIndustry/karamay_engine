#ifndef QUERY_POOL_H
#define QUERY_POOL_H
#include "device_object.h"

class command_buffer;

class query_pool final : public device_object<VkQueryPool>
{
public:

	query_pool(device& dev);

	query_pool(const query_pool&) = delete;
	query_pool& operator=(const query_pool&) = delete;

	~query_pool() override;

public:

	bool allocate(VkQueryType type, uint32 count, VkQueryPipelineStatisticFlags flags);

	void deallocate();

public:

	void reset(command_buffer* recorder, uint32 first_query, uint32 query_count);

	void copy_results(command_buffer* recorder, uint32 first_query, uint32 query_count, buffer* dst, uint64 offset, uint64 stride, VkQueryResultFlags flags);

	void begin(command_buffer* recorder, uint32 index, VkQueryControlFlags flags);

	void end(command_buffer* recorder, uint32 index);

};

#endif