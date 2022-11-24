#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class subpass;
class subpass_dependency;
class framebuffer;
class command_buffer;
class primary_command_buffer;

struct attachment_view
{
	std::shared_ptr<image_view> img;

};

struct framebuffer_info
{
	std::uint32_t width, height, layers;

	std::vector<std::shared_ptr<attachment_view>> attachment_views;

};

struct default_subpass_info
{

};

class subpass_linker
{
public:

	subpass_linker(std::shared_ptr<subpass> root);

	void plus(std::shared_ptr<subpass> next);

	void clear();

	void get_subpasses(std::vector<std::shared_ptr<subpass>>& out_subpasses);

	void get_denpendencies(std::vector<std::shared_ptr<subpass_dependency>>& out_dependencies);
};

class render_pass final : public device_object<VkRenderPass>
{
	friend class deivce;
public:
	using subpass_extension = std::function<bool(subpass_linker&)>;

	bool allocate(
		const framebuffer_info& render_target_info,
		const default_subpass_info& default_subpass,
		const subpass_extension& extension = {}
	);



	render_pass(device& owner);
	render_pass(const render_pass&) = delete;

	virtual ~render_pass() override;

	void cmd_execute(primary_command_buffer& recorder);

	const subpass_linker& get_subpass_linker() const 
	{ 
		return _linker;
	}

	const std::unique_ptr<framebuffer>& get_framebuffer() const
	{
		return _render_target;
	}

	bool is_dirty() const 
	{ 
		return _is_dirty; 
	}

	void clean();
	
	void set_render_area(const VkRect2D& val);
	
	void set_clear_values(const std::vector<VkClearValue>& vals);

private:

	std::vector<VkClearValue> _clear_values;

	VkRect2D _render_area;

	subpass_linker _linker;

	std::unique_ptr<framebuffer> _render_target;

	bool _is_dirty{ false };

	std::vector<std::shared_ptr<class FColorAttachment>> _color_attachments;

	std::shared_ptr<class FDepthStencilAttachment> _depth_stencil_attachment;

};

_KANAS_CORE_END

#endif