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

	std::vector<std::shared_ptr<subpass>> _subpasses;

	std::vector<std::shared_ptr<subpass_dependency>> _dependencies;

public:

	subpass_linker(std::shared_ptr<subpass> default_subpass);

	void plus(std::shared_ptr<subpass> next);

	void clear();

	std::vector<std::shared_ptr<subpass>>& get_subpasses()
	{
		return _subpasses;
	}

	void get_dependencies(std::vector<std::shared_ptr<subpass_dependency>>& out_dependencies);
};

struct render_pass_description
{
	

};


class render_pass : public device_object<VkRenderPass>
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

	render_pass(render_pass& other);

	virtual ~render_pass() override;

	virtual void cmd_execute(primary_command_buffer& recorder) = 0;

	[[nodiscard]] bool is_dirty() const
	{
		return _is_dirty; 
	}

	void clean_state();
	
	void set_render_area(const VkRect2D& val);
	
	void set_clear_values(const std::vector<VkClearValue>& vals);

	[[nodiscard]] const std::string& name() const { return _name; }

	[[nodiscard]] const std::unique_ptr<framebuffer>& render_target() const
	{
		return _render_target;
	}

protected:

	std::string _name{ "null" };

	std::unique_ptr<framebuffer> _render_target;

	std::vector<VkClearValue> _clear_values;

	VkRect2D _render_area;

	bool _is_dirty{ false };

};


class mobile_render_pass final : public render_pass
{
public:

    explicit mobile_render_pass(device& dev);

    ~mobile_render_pass() override = default;

    void cmd_execute(primary_command_buffer& pcd) override;

    [[nodiscard]] const std::unique_ptr<subpass>& fixed() const { return _fixed_subpass; }

    [[nodiscard]] const std::vector<std::unique_ptr<subpass>>& extension() const { return _extended_subpasses; }

private:

    std::unique_ptr<subpass> _fixed_subpass;

    std::vector<std::unique_ptr<subpass>> _extended_subpasses;

};

_KANAS_CORE_END

#endif