#ifndef GL_SHADER_TOY_RENDERER_H
#define GL_SHADER_TOY_RENDERER_H
#include "graphics/renderer/gl_renderer.h"

class gl_shader_toy_renderer final : public gl_renderer
{
private:

	static gl_shader_toy_renderer* _instance;

	gl_shader_toy_renderer() = default;
	gl_shader_toy_renderer(const gl_shader_toy_renderer&) = delete;
	gl_shader_toy_renderer& operator=(const gl_shader_toy_renderer&) = delete;

public:

	static gl_shader_toy_renderer* invoke() noexcept
	{
		if (!_instance)
		{
			_instance = new gl_shader_toy_renderer();
		}
		return _instance;
	}

	~gl_shader_toy_renderer() = default;

private:

	std::unique_ptr<gl_graphics_pipeline> _shader_toy_gpp = {};

	float _acc_time = 0.0f;

public:

	bool attach() noexcept override;

	void render(float delta_time) noexcept override;

	bool detach() noexcept override;

public:

	void add_template(const std::string& name) noexcept {}

	void switch_template(const std::string& name) noexcept {}

};

class gl_shader_toy_template
{
	gl_shader_toy_template()
	{

	}

public:

	void load_all(std::vector<gl_shader_toy_renderer*>& invoked_renderers) noexcept
	{
	}

	gl_shader_toy_renderer* load(const std::string& path) noexcept;

};


#endif