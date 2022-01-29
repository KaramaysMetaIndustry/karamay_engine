#include "graphics/renderer/pipeline/base/resource/vertex_array/gl_vertex_array.h"
#include "graphics/renderer/pipeline/base/resource/program/gl_program.h"
#include "graphics/renderer/pipeline/base/resource/buffers/raw_buffer/gl_buffer.h"
#include "window/window.h"
#include "embedded/lua/lvm.h"
#include "embedded/lua/lvm_graphics_class.h"
#include "renderers/gl_static_mesh_renderer.h"
#include "public/json.h"

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
    SEVERITY_HIGH = GL_DEBUG_SEVERITY_HIGH, // 高级
    SEVERITY_LOW = GL_DEBUG_SEVERITY_LOW, // 低级
    SEVERITY_MEDIUM = GL_DEBUG_SEVERITY_MEDIUM, // 中级
    SEVERITY_NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION, // 通知
};

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
//    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
//             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
//             type, severity, message );

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

    std::cerr<<"["<<std::endl;
    std::cerr<<"  DEBUG SOURCE: "<< _source_str << std::endl;
    std::cerr<<"  DEBUG TYPE: "<< _type_str << std::endl;
    std::cerr<<"  DEBUG ID: "<< id << std::endl;
    std::cerr<<"  DEBUG SEVERITY: "<< _severity_str << std::endl;
    std::cerr<<"  DEBUG MESSAGE: "<< _message_str << std::endl;
    std::cerr<<"]"<<std::endl;

}

void load_templates(const std::string& include_token)
{
    static std::string _templates_path = "G:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/templates";
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
        include_token.size(), include_token.c_str(),
        content.size(), content.c_str());
}

int main()
{
    /*  lua_api::lua_vm _lvm;
  _lvm.start();
  _lvm.do_file("C:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\lua\\Test.lua");*/

    auto* window = new glfw_window();
    window->load_context();
    std::cout << "VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "RENDERER: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "SHADING_LANGUAGE_VERSION: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    //std::cout << "GL_EXTENSIONS: " << glGetString(GL_EXTENSIONS) << std::endl;
    glewInit();
    glViewport(0, 0, window->get_framebuffer_width(), window->get_framebuffer_height());

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif 

    //auto _file = gltf_loader::load("");

    load_templates("/common.glsl");
    load_templates("/common.frag.glsl");

    gl_static_mesh_renderer* _static_mesh_renderer = new gl_static_mesh_renderer();

    std::vector<gl_renderer*> _renderers;
    _renderers.push_back(_static_mesh_renderer);

    std::vector<gl_renderer*> _standby_renderers;
    for (auto _renderer : _renderers)
    {
        if (_renderer->initialize())
        {
            _standby_renderers.push_back(_renderer);
        }
    }

    uint32 _frame_count = 0;
    float _frame_delta_time = 0.0f;
    while (_standby_renderers.size())
    {
        _frame_delta_time = 0.0f;
        auto _frame_start = std::chrono::steady_clock::now();
        window->tick(0.0f);
        for (auto _standby_renderer : _standby_renderers) _standby_renderer->render(_frame_delta_time);
        auto _frame_end = std::chrono::steady_clock::now();
        _frame_delta_time = std::chrono::duration_cast<std::chrono::seconds>(_frame_end - _frame_start).count();
        ++_frame_count;

        if (_frame_count == 500) break;
    }
}