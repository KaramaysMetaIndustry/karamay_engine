#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class command_pool;
class render_pass;
class subpass;

enum class ECommandBufferState : std::uint8_t
{
	Initial,
	Recording,
	Executable,
	Pending,
	Invalid
};

enum class command_buffer_level
{
	primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
};

class command_buffer : public device_object<VkCommandBuffer>
{
	friend class command_pool;

	bool alllocate(command_buffer_level level);

public:

	command_buffer(device& owner, command_pool& pool);

	virtual ~command_buffer() override;

	command_pool& get_pool()
	{
		return _pool;
	}

	bool reset(command_buffer_reset_flags flags = {});

	void cmd_barrier();

private:

	command_pool& _pool;

};

class primary_command_buffer : public command_buffer
{
public:

	primary_command_buffer();

	virtual ~primary_command_buffer();

	bool record(std::shared_ptr<render_pass> pass);

	void get_secondary_command_buffers(std::uint32_t num, std::vector<std::shared_ptr<secondary_command_buffer>>& OutSecondaryCmdBuffers);

private:

	std::vector<std::shared_ptr<secondary_command_buffer>> SubCmdBuffers;

};

class secondary_command_buffer : public command_buffer
{
public:

	secondary_command_buffer();

	virtual ~secondary_command_buffer();

	bool record(std::shared_ptr<subpass> pass);

};


_KANAS_CORE_END


#endif