#ifndef _SUBPASS_H_
#define _SUBPASS_H_

#include "KanasCoreMacros.h"
#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

class render_pass;
class pipeline;
class secondary_command_buffer;

class subpass
{
public:

	using record_subpass_cmds = std::function<void(secondary_command_buffer&)>;

	bool allocate(,
		std::uint32_t new_index,
		const std::vector<std::uint32_t>& new_attachment_indices,
		std::shared_ptr<pipeline> new_pipe,
		const record_subpass_cmds& cmds,
		VkSubpassContents new_contents);

	subpass(render_pass& owner);
	subpass(const subpass&) = delete;

	virtual ~subpass();

	void cmd_execute(secondary_command_buffer& recorder);

	std::shared_ptr<render_pass> get_render_pass() const
	{
		return owner.lock();
	}

	std::uint32_t get_index() const
	{
		return index;
	}

	std::shared_ptr<subpass> get_next() const
	{
		return next;
	}

	const record_subpass_cmds& get_cmd_delegate() const 
	{ 
		return record_functor; 
	}

	VkSubpassContents get_contents() const 
	{ 
		return contents; 
	}

private:

	render_pass& owner;

	std::uint32_t index;

	std::shared_ptr<pipeline> pipe;

	std::shared_ptr<subpass> next;

	record_subpass_cmds record_functor;

	VkSubpassContents contents;

};

struct subpassDependency
{
	pipeline_stage_flags PreStageMask{};

	pipeline_stage_flags StageMask{};

	access_flags PreAccessMask{};

	access_flags AccessMask{};

	dependency_flags Dependency{};

};

_KANAS_CORE_END

#endif

