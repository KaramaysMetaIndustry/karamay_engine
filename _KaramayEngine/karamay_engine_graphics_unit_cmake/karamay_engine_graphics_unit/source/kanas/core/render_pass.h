#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class subpass;
class framebuffer;
class command_buffer;
class primary_command_buffer;
class image_view;
class pipeline;

struct attachment
{
    VkFormat format{};
    sample_count samples{};
    attachment_load_op load_op{};
    attachment_store_op store_op{};
    attachment_load_op stencil_load_op{};
    attachment_store_op stencil_store_op{};
    image_layout initial_layout{};
    image_layout final_layout{};

    attachment() = default;

};

struct attachment_ref
{
    std::uint32_t index{ UINT32_MAX };
    image_layout layout{ image_layout::t::undefined };

    attachment_ref() = default;

};

struct subpass
{
    std::vector<attachment_ref> input_attachment_refs;

    std::vector<attachment_ref> color_attachment_refs;
    std::vector<attachment_ref> resolve_attachment_refs;

    attachment_ref depth_stencil_attachment_ref;

    std::vector<attachment_ref> preserve_attachment_refs;

    std::shared_ptr<pipeline> pipe;

};

struct subpass_dependency
{

};

class subpass_list
{
    std::vector<subpass> _subpasses;

    std::vector<subpass_dependency> _dependencies;

public:

    subpass_list(const subpass& default_subpass){}

    void plus(const subpass_dependency& dependency_to_prev, const subpass& next_subpass);

    const std::vector<subpass>& subpasses() const {return _subpasses;}

    const std::vector<subpass_dependency>& dependencies() const {return _dependencies;}

};

struct render_pass_obj_model
{
    std::string name;

    std::vector<attachment> attachments;

    subpass default_subpass;

    std::vector<std::pair<subpass_dependency, subpass>> next_subpasses;

};

class render_pass : public device_object<VkRenderPass>
{
	friend class deivce;

public:

	bool allocate(
            const std::vector<attachment>& attachments,
            const subpass_list& subpasses
	);

    bool allocate(const render_pass_obj_model& obj_model);

	render_pass(device& owner);
	render_pass(const render_pass&) = delete;

	render_pass(render_pass& other);

	virtual ~render_pass() override;

	virtual void cmd_execute(primary_command_buffer& pcb) const;

	void set_render_area(const VkRect2D& val);
	
	void set_clear_values(const std::vector<VkClearValue>& vals);

	[[nodiscard]] const std::string& name() const { return _name; }

	[[nodiscard]] const std::vector<std::shared_ptr<framebuffer>>& render_targets() const
	{
		return _render_targets;
	}

    [[nodiscard]] const std::unique_ptr<subpass>& fixed() const
    {
        return _fixed_subpass;
    }

    [[nodiscard]] const std::vector<std::unique_ptr<subpass>>& extension() const
    {
        return _extended_subpasses;
    }

private:

	std::string _name{ "null" };

    std::unique_ptr<subpass> _fixed_subpass;

    std::vector<std::unique_ptr<subpass>> _extended_subpasses;

	std::vector<VkClearValue> _clear_values;

	VkRect2D _render_area;

    std::vector<std::shared_ptr<framebuffer>> _render_targets;

    std::shared_ptr<framebuffer> _current_render_target;

};






_KANAS_CORE_END

#endif