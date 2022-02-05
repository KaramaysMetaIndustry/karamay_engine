#include "gl_renderer_dispatcher.h"
#include "engine/karamay_engine.h"

namespace opengl
{
    enum class gl_debug_type : GLenum
    {
        DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
        UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
        ERROR = GL_DEBUG_TYPE_ERROR,
        MARKER = GL_DEBUG_TYPE_MARKER,
        OTHER = GL_DEBUG_TYPE_OTHER,
        PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,
        POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,
        PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,
        PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP
    };

    enum class gl_debug_source : GLenum
    {
        API = GL_DEBUG_SOURCE_API,
        APPLICATION = GL_DEBUG_SOURCE_APPLICATION,
        OTHER = GL_DEBUG_SOURCE_OTHER,
        SHADER_COMPILER = GL_DEBUG_SOURCE_SHADER_COMPILER,
        THIRD_PARTY = GL_DEBUG_SOURCE_THIRD_PARTY,
        WINDOW_SYSTEM = GL_DEBUG_SOURCE_WINDOW_SYSTEM
    };

    enum class gl_debug_severity : GLenum
    {
        SEVERITY_HIGH = GL_DEBUG_SEVERITY_HIGH,
        SEVERITY_LOW = GL_DEBUG_SEVERITY_LOW,
        SEVERITY_MEDIUM = GL_DEBUG_SEVERITY_MEDIUM,
        SEVERITY_NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION,
    };

    void GLAPIENTRY message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
        auto _source = static_cast<gl_debug_source>(source);
        auto _type = static_cast<gl_debug_type>(type);
        auto _severity = static_cast<gl_debug_severity>(severity);

        std::string _source_str;
        std::string _type_str;
        std::string _severity_str;

        switch (_source) {

        case gl_debug_source::API: _source_str = "API";
            break;
        case gl_debug_source::APPLICATION: _source_str = "APPLICATION";
            break;
        case gl_debug_source::OTHER: _source_str = "OTHER";
            break;
        case gl_debug_source::SHADER_COMPILER: _source_str = "SHADER_COMPILER";
            break;
        case gl_debug_source::THIRD_PARTY: _source_str = "THIRD_PARTY";
            break;
        case gl_debug_source::WINDOW_SYSTEM: _source_str = "WINDOW_SYSTEM";
            break;
        }

        switch (_type) {
        case gl_debug_type::DEPRECATED_BEHAVIOR: _type_str = "DEPRECATED_BEHAVIOR";
            break;
        case gl_debug_type::UNDEFINED_BEHAVIOR: _type_str = "UNDEFINED_BEHAVIOR";
            break;
        case gl_debug_type::ERROR: _type_str = "ERROR";
            break;
        case gl_debug_type::MARKER: _type_str = "MARKER";
            break;
        case gl_debug_type::OTHER: _type_str = "OTHER";
            break;
        case gl_debug_type::PERFORMANCE: _type_str = "PERFORMANCE";
            break;
        case gl_debug_type::POP_GROUP: _type_str = "POP_GROUP";
            break;
        case gl_debug_type::PORTABILITY: _type_str = "PORTABILITY";
            break;
        case gl_debug_type::PUSH_GROUP: _type_str = "PUSH_GROUP";
            break;
        }

        switch (_severity) {
        case gl_debug_severity::SEVERITY_HIGH: _severity_str = "SEVERITY_HIGH";
            break;
        case gl_debug_severity::SEVERITY_LOW: _severity_str = "SEVERITY_LOW";
            break;
        case gl_debug_severity::SEVERITY_MEDIUM: _severity_str = "SEVERITY_MEDIUM";
            break;
        case gl_debug_severity::SEVERITY_NOTIFICATION: _severity_str = "SEVERITY_NOTIFICATION";
            break;
        }

        std::string _message_str(message, length);

        std::cerr << "[" << std::endl;
        std::cerr << "  DEBUG SOURCE: " << _source_str << std::endl;
        std::cerr << "  DEBUG TYPE: " << _type_str << std::endl;
        std::cerr << "  DEBUG ID: " << id << std::endl;
        std::cerr << "  DEBUG SEVERITY: " << _severity_str << std::endl;
        std::cerr << "  DEBUG MESSAGE: " << _message_str << std::endl;
        std::cerr << "]" << std::endl;

    }
}

bool gl_renderer_dispatcher::initialize() noexcept
{
    std::cout << "renderer dispatcher start to initialize." << std::endl;
    

    std::cout << "renderer dispatcher has initialized." << std::endl;
    return true;
}

void gl_renderer_dispatcher::run() noexcept
{
    // opengl context must be at the same thread space

    _window = new glfw_window();
    _window->load_context();

    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    //std::cout << "GL_EXTENSIONS: " << glGetString(GL_EXTENSIONS) << std::endl;

    glewInit();
    glViewport(0, 0, _window->get_framebuffer_width(), _window->get_framebuffer_height());

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(opengl::message_callback, 0);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif 

    load_templates("/common.glsl");
    load_templates("/common.frag.glsl");

    gl_static_mesh_renderer* _static_mesh_renderer = new gl_static_mesh_renderer();
    _renderers.push_back(_static_mesh_renderer);

    std::cout << "renderer dispatcher is running" << std::endl;
    std::vector<gl_renderer*> _standby_renderers;
    for (auto _renderer : _renderers)
    {
        if (_renderer->initialize())
        {
            _standby_renderers.push_back(_renderer);
        }
    }

    float _frame_delta_time = 0.0f;
    while (!_should_exit)
    {
        //std::cout << "renderer dispatcher tick" << std::endl;
        auto _frame_start = std::chrono::steady_clock::now();
        _window->tick(_frame_delta_time);
        for (auto _standby_renderer : _standby_renderers)
        {
            _standby_renderer->render(_frame_delta_time);
        }
        auto _frame_end = std::chrono::steady_clock::now();
        _frame_delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(_frame_end - _frame_start).count();
    }

    std::cout << "renderer dispatcher has exited." << std::endl;
}

void gl_renderer_dispatcher::notify_to_exit()
{
    _should_exit = true;
}

void gl_renderer_dispatcher::load_templates(const std::string& include_token)
{
    static std::string _templates_path = karamay_engine::get_engine_root() +  "shaders\\templates";
    std::string _path = _templates_path + include_token;
    std::ifstream file;
    std::string content;
    file.exceptions(std::fstream::failbit | std::fstream::badbit);
    try {
        file.open(_path);
        std::stringstream sstream;
        sstream << file.rdbuf();
        file.close();
        content = sstream.str();
    }
    catch (const std::exception& e) {
        std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
    }
    
    glNamedStringARB(GL_SHADER_INCLUDE_ARB, 
        include_token.size(), include_token.c_str(), content.size(), content.c_str());
}
