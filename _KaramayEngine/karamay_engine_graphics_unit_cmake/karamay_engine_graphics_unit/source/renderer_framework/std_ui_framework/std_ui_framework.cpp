#include "std_ui_framework.h"
#include "graphics/dispatcher/gl_renderer_dispatcher.h"
#include "renderers/templates/gl_shader_toy_renderer.h"

namespace std_ui_framework
{
    gl_renderer_template<gl_shader_toy_renderer> _shader_toy_renderer_template;
}

bool std_ui_framework::framework::initialize() noexcept
{
    std::vector<gl_shader_toy_renderer*> _invoked_st_renderers;
    _shader_toy_renderer_template.load_all(_invoked_st_renderers);
    for (auto _invoked_st_renderer : _invoked_st_renderers)
    {
        if (_invoked_st_renderer && _invoked_st_renderer->attach())
            _renderers.push_back(_invoked_st_renderer);
    }

    auto _st_renderer = gl_shader_toy_renderer::invoke();
    if(_st_renderer && _st_renderer->attach())
        _renderers.push_back(_st_renderer);
    return true;
}

void std_ui_framework::framework::tick(float delta_time) noexcept
{
    for (auto _renderer : _renderers)
    {
        if (_renderer)
        {
            _renderer->render(delta_time);
        }
    }
}

bool std_ui_framework::framework::set_state(bool active) noexcept
{
    return false;
}

bool std_ui_framework::framework::is_active() const noexcept
{
    return true;
}

struct std_ui_framework_helper
{
    static std_ui_framework_helper helper;
    std_ui_framework_helper()
    {
        auto _std_ui_fw = new std_ui_framework::framework();
        gl_renderer_dispatcher::register_framework("std_ui_framework", _std_ui_fw);
        std::cout << "std_ui_framework has been registered." << std::endl;
    }
};
std_ui_framework_helper std_ui_framework_helper::helper;

