#ifndef GL_RENDERER_DISPATCHER_H
#define GL_RENDERER_DISPATCHER_H
#include "renderer/gl_renderer.h"
#include "window/window.h"

class gl_renderer_dispatcher
{
public:

    gl_renderer_dispatcher() = default;
    gl_renderer_dispatcher(const gl_renderer_dispatcher&) = delete;
    gl_renderer_dispatcher& operator=(const gl_renderer_dispatcher&) = delete;

    ~gl_renderer_dispatcher() = default;

public:

    bool initialize() noexcept;

    void run() noexcept;

    void notify_to_exit();

private:

    void load_templates(const std::string& include_token);

    std::atomic_bool _should_exit = false;

private:

	std::vector<gl_renderer*> _renderers;

    glfw_window* _window = nullptr;

};

#endif
