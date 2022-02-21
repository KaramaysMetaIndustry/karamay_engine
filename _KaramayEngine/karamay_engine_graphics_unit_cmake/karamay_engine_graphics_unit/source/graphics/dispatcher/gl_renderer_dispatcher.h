#ifndef GL_RENDERER_DISPATCHER_H
#define GL_RENDERER_DISPATCHER_H
#include "graphics/framework/gl_renderer_framework.h"
#include "window/window.h"

class gl_renderer_dispatcher final
{
public:

    gl_renderer_dispatcher() = default;
    gl_renderer_dispatcher(const gl_renderer_dispatcher&) = delete;
    gl_renderer_dispatcher& operator=(const gl_renderer_dispatcher&) = delete;

    ~gl_renderer_dispatcher() = default;

public:

    bool initialize() noexcept;

    void run() noexcept;

    void notify_to_exit() noexcept;

private:

    void load_templates(const std::string& include_token);

    std::atomic_bool _should_exit = false;

	std::vector<gl_renderer*> _renderers;

    glfw_window* _window = nullptr;

private:

    static struct static_block
    {
        std::unordered_map<std::string, gl_renderer_framework*> frameworks;

        static_block()
        {
            frameworks.emplace("1", nullptr);
            std::cout << "static_block initialized." << std::endl;
        }
    } _static_block;

public:

    static void register_framework(const std::string& framework_name, gl_renderer_framework* framework)
    {
        auto& _frameworks = _static_block.frameworks;
#ifdef _DEBUG
        if (_frameworks.find(framework_name) != _frameworks.cend()) throw std::exception("error : framework name exists.");
#endif
        _frameworks.emplace(framework_name, framework);
    }

    static bool set_framework_state(const std::string& framework_name, bool enable)
    {
        auto _it = _static_block.frameworks.find(framework_name);
        if (_it == _static_block.frameworks.cend())
        {
            std::cerr << framework_name << " does not exist" << std::endl;
            return false;
        }

        return _it->second->set_state(enable);
    }

};

#endif
