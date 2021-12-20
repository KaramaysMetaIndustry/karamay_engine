#ifndef H_RENDERER
#define H_RENDERER

#include "pipeline/gl_graphics_pipeline.h"
#include "pipeline/gl_compute_pipeline.h"

class gl_renderer_builder final
{
public:
    gl_renderer_builder() = default;

    gl_renderer_builder(const gl_renderer_builder&) = delete;
    gl_renderer_builder& operator=(const gl_renderer_builder&) = delete;

    ~gl_renderer_builder()
    {
        for (auto _buffer : _buffers) { delete _buffer.second;  std::cout << "delete buffer " << _buffer.first<< std::endl;}
        for (auto _tex_1d : _texture_1ds) { delete _tex_1d.second; std::cout << "delete tex_1d " << _tex_1d.first << std::endl; }
        for (auto _tex_1d_arr : _texture_1d_arrays) { delete _tex_1d_arr.second; std::cout << "delete tex_1d_arr " << _tex_1d_arr.first << std::endl; }
        for (auto _tex_2d : _texture_2ds) { delete _tex_2d.second; std::cout << "delete tex_2d " << _tex_2d.first << std::endl; }
        for (auto _tex_2d_arr : _texture_2d_arrays) { delete _tex_2d_arr.second; std::cout << "delete tex_2d_arr " << _tex_2d_arr.first << std::endl; }
        for (auto _tex_2d_ms : _texture_2d_multisamples) { delete _tex_2d_ms.second; std::cout << "delete tex_2d_ms " << _tex_2d_ms.first << std::endl; }
        for (auto _tex_2d_ms_arr : _texture_2d_multisample_arrays) { delete _tex_2d_ms_arr.second; std::cout << "delete tex_2d_ms_arr " << _tex_2d_ms_arr.first << std::endl; }
        for (auto _tex_rect : _texture_rectangles) { delete _tex_rect.second; std::cout << "delete tex_rect " << _tex_rect.first << std::endl; }
        for (auto _tex_cube : _texture_cubes) { delete _tex_cube.second; std::cout << "delete tex_cube " << _tex_cube.first << std::endl; }
        for (auto _tex_cube_arr : _texture_cube_arrays) { delete _tex_cube_arr.second; std::cout << "delete tex_cube_arr " << _tex_cube_arr.first << std::endl; }
        for (auto _tex_3d : _texture_3ds) { delete _tex_3d.second; std::cout << "delete tex_3d " << _tex_3d.first << std::endl; }
        for (auto _tex_buffer : _texture_buffers) { delete _tex_buffer.second; std::cout << "delete tex_buffer " << _tex_buffer.first << std::endl; }
        for (auto _renderbuffer : _renderbuffers) { delete _renderbuffer.second; std::cout << "delete renderbuffer " << _renderbuffer.first << std::endl; }
        for (auto _renderbuffer_ms : _renderbuffer_multisamples) { delete _renderbuffer_ms.second; std::cout << "delete renderbuffer_ms " << _renderbuffer_ms.first << std::endl; }
        for (auto _framebuffer : _framebuffers) { delete _framebuffer.second; std::cout << "delete framebuffer " << _framebuffer.first << std::endl; }
    }

public:

    gl_buffer* create_buffer(const std::string& name, gl_buffer_storage_options options, int64 bytes_num, const void* initial_data = nullptr)
    {
        auto _it = _buffers.find(name);
        if (_it == _buffers.cend())
        {
            auto _buffer = new gl_buffer(options, bytes_num, initial_data);
            _buffers.emplace(name, _buffer);
            std::cout << "new buffer " << name << std::endl;
            return _buffer;
        }
        return nullptr;
    }

    gl_uniform_buffer* create_uniform_buffer(const std::string& name)
    {
        return nullptr;
    }
    gl_shader_storage_buffer* create_shader_storage_buffer(const std::string& name)
    {
        return nullptr;
    }

    gl_texture_1d* create_texture_1d(const std::string& name, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format)
    {
        auto _it = _buffers.find(name);
        if (_it == _buffers.cend())
        {
            auto _texture_1d = new gl_texture_1d(mipmaps_num, internal_format, width);
            _texture_1ds.emplace(name, _texture_1d);
            std::cout << "new texture_1d " << name << std::endl;
            return _texture_1d;
        }
        return nullptr;
    }
    gl_texture_1d_array* create_texture_1d_array(const std::string& name, int32 elements_num, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_1d_arrays.find(name);
        if (_it == _texture_1d_arrays.cend())
        {
            auto _texture_1d_array = new gl_texture_1d_array(elements_num, mipmaps_num, width, internal_format);
            _texture_1d_arrays.emplace(name, _texture_1d_array);
            std::cout << "new texture_1d_array " << name << std::endl;
            return _texture_1d_array;
        }
        return nullptr;
    }
    gl_texture_2d* create_texture_2d(const std::string& name, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_2ds.find(name);
        if (_it == _texture_2ds.cend())
        {
            auto _texture_2d = new gl_texture_2d(mipmaps_num, internal_format, width, height);
            _texture_2ds.emplace(name, _texture_2d);
            std::cout << "new texture_2d " << name << std::endl;
            return _texture_2d;
        }
        return nullptr;
    }
    gl_texture_2d_array* create_texture_2d_array(const std::string& name, int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_2d_arrays.find(name);
        if (_it == _texture_2d_arrays.cend())
        {
            auto _texture_2d_array = new gl_texture_2d_array(elements_num, mipmaps_num, width, height, internal_format);
            _texture_2d_arrays.emplace(name, _texture_2d_array);
            std::cout << "new texture_2d_array " << name << std::endl;
            return _texture_2d_array;
        }
        return nullptr;
    }
    gl_texture_rectangle* create_texture_rectangle(const std::string& name, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_rectangles.find(name);
        if (_it == _texture_rectangles.cend())
        {
            auto _tex_rect = new gl_texture_rectangle(width, height, internal_format);
            _texture_rectangles.emplace(name, _tex_rect);
            std::cout << "new texture_rectangle " << name << std::endl;
            return _tex_rect;
        }
        return nullptr;
    }
    gl_texture_cube* create_texture_cube(const std::string& name, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_cubes.find(name);
        if (_it == _texture_cubes.cend())
        {
            auto _tex_cube = new gl_texture_cube(mipmaps_num, internal_format, width, height);
            _texture_cubes.emplace(name, _tex_cube);
            std::cout << "new texture_cube " << name << std::endl;
            return _tex_cube;
        }
        return nullptr;
    }
    gl_texture_cube_array* create_texture_cube_array(const std::string& name, int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_cube_arrays.find(name);
        if (_it == _texture_cube_arrays.cend())
        {
            auto _tex_cube_arr = new gl_texture_cube_array(elements_num, mipmaps_num, internal_format, width, height);
            _texture_cube_arrays.emplace(name, _tex_cube_arr);
            std::cout << "new texture_cube_array " << name << std::endl;
            return _tex_cube_arr;
        }
        return nullptr;
    }
    gl_texture_2d_multisample* create_texture_2d_multisample(const std::string& name, int32 samples_num, int32 width, int32 height, gl_texture_internal_format internal_format, bool fixed_sample_locations)
    {
        auto _it = _texture_2d_multisamples.find(name);
        if (_it == _texture_2d_multisamples.cend())
        {
            auto _tex_2d_ms = new gl_texture_2d_multisample(samples_num, internal_format, width, height, fixed_sample_locations);
            _texture_2d_multisamples.emplace(name, _tex_2d_ms);
            std::cout << "new texture_2d_multisample " << name << std::endl;
            return _tex_2d_ms;
        }
        return nullptr;
    }
    gl_texture_2d_multisample_array* create_texture_2d_multisample_array(const std::string& name, int32 elements_num, int32 samples_num, int32 width, int32 height, gl_texture_internal_format internal_format, bool fixed_sample_locations)
    {
        auto _it = _texture_2d_multisample_arrays.find(name);
        if (_it == _texture_2d_multisample_arrays.cend())
        {
            auto _tex_2d_ms_arr = new gl_texture_2d_multisample_array(elements_num, samples_num, internal_format, width, height, fixed_sample_locations);
            _texture_2d_multisample_arrays.emplace(name, _tex_2d_ms_arr);
            std::cout << "new texture_2d_multisample_array " << name << std::endl;
            return _tex_2d_ms_arr;
        }
        return nullptr;
    }
    gl_texture_3d* create_texture_3d(const std::string& name, int32 mipmaps_num, int32 width, int32 height, int32 depth, gl_texture_internal_format internal_format)
    {
        auto _it = _texture_3ds.find(name);
        if (_it == _texture_3ds.cend())
        {
            auto _tex_3d = new gl_texture_3d(mipmaps_num, width, height, depth, internal_format);
            _texture_3ds.emplace(name, _tex_3d);
            std::cout << "new texture_3d " << name << std::endl;
            return _tex_3d;
        }
        return nullptr;
    }
    gl_texture_buffer* create_texture_buffer(const std::string& name, gl_buffer* buffer, gl_texture_internal_format internal_format) 
    {
        auto _it = _texture_buffers.find(name);
        if (_it == _texture_buffers.cend())
        {
            auto _tex_buffer = new gl_texture_buffer(buffer, internal_format);
            _texture_buffers.emplace(name, _tex_buffer);
            std::cout << "new texture_buffer " << name << std::endl;
            return _tex_buffer;
        }
        return nullptr; 
    }

    gl_renderbuffer* create_renderbuffer(const std::string& name, int32 width, int32 height, gl_renderbuffer_internal_format internal_format)
    {
        auto _it = _renderbuffers.find(name);
        if (_it == _renderbuffers.cend())
        {
            auto _renderbuffer = new gl_renderbuffer(width, height, internal_format);
            _renderbuffers.emplace(name, _renderbuffer);
            std::cout << "new renderbuffer " << name << std::endl;
            return _renderbuffer;
        }
        return nullptr;
    }
    gl_renderbuffer_multisample* create_renderbuffer_multisample(const std::string& name, int32 samples_num, int32 width, int32 height, gl_renderbuffer_internal_format internal_format)
    {
        auto _it = _renderbuffer_multisamples.find(name);
        if (_it == _renderbuffer_multisamples.cend())
        {
            auto _renderbuffer_ms = new gl_renderbuffer_multisample(samples_num, width, height, internal_format);
            _renderbuffer_multisamples.emplace(name, _renderbuffer_ms);
            std::cout << "new renderbuffer_multisample " << name << std::endl;
            return _renderbuffer_ms;
        }
        return nullptr;
    }

    gl_framebuffer* create_framebuffer(const std::string& name, int32 width, int32 height)
    {
        auto _it = _framebuffers.find(name);
        if (_it == _framebuffers.cend())
        {
            auto _framebuffer = new gl_framebuffer(width, height);
            _framebuffers.emplace(name, _framebuffer);
            std::cout << "new framebuffer " << name << std::endl;
            return _framebuffer;
        }
        return nullptr;
    }

    gl_graphics_pipeline* create_graphics_pipeline(const std::string& name, glsl_vertex_shader* vs, glsl_fragment_shader* fs)
    {
        auto _it = _graphics_pipelines.find(name);
        if (_it == _graphics_pipelines.cend())
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, fs);
            _graphics_pipelines.emplace(name, _graphics_pipeline);
            std::cout << "new grahics_pipeline " << name << std::endl;
            return _graphics_pipeline;
        }
        return nullptr;
    }
    gl_graphics_pipeline* create_graphics_pipeline(const std::string& name, glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs)
    {
        auto _it = _graphics_pipelines.find(name);
        if (_it == _graphics_pipelines.cend())
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, ts, fs);
            _graphics_pipelines.emplace(name, _graphics_pipeline);
            std::cout << "new grahics_pipeline " << name << std::endl;
            return _graphics_pipeline;
        }
        return nullptr;
    }
    gl_graphics_pipeline* create_graphics_pipeline(const std::string& name, glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs)
    {
        auto _it = _graphics_pipelines.find(name);
        if (_it == _graphics_pipelines.cend())
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, gs, fs);
            _graphics_pipelines.emplace(name, _graphics_pipeline);
            std::cout << "new grahics_pipeline " << name << std::endl;
            return _graphics_pipeline;
        }
        return nullptr;
    }
    gl_graphics_pipeline* create_graphics_pipeline(const std::string& name, glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs)
    {
        auto _it = _graphics_pipelines.find(name);
        if (_it == _graphics_pipelines.cend())
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, ts, gs, fs);
            _graphics_pipelines.emplace(name, _graphics_pipeline);
            std::cout << "new grahics_pipeline " << name << std::endl;
            return _graphics_pipeline;
        }
        return nullptr;
    }

    gl_compute_pipeline* create_compute_pipeline(const std::string& name, glsl_compute_shader* cs)
    {
        auto _it = _compute_pipelines.find(name);
        if (_it == _compute_pipelines.cend())
        {
            auto _compute_pipeline = new gl_compute_pipeline(cs);
            _compute_pipelines.emplace(name, _compute_pipeline);
            std::cout << "new compute_pipeline " << name << std::endl;
            return _compute_pipeline;
        }
        return nullptr;
    }

public:

    gl_graphics_pipeline* graphics_pipeline(const std::string& name)
    {
        auto _it = _graphics_pipelines.find(name);
        if (_it != _graphics_pipelines.cend()) return _it->second;
        return nullptr;
    }
    
    gl_compute_pipeline* compute_pipeline(const std::string& name)
    {
        auto _it = _compute_pipelines.find(name);
        if (_it != _compute_pipelines.cend()) return _it->second;
        return nullptr;
    }

private:

    std::unordered_map<std::string, gl_buffer*> _buffers;
    std::unordered_map<std::string, gl_texture_1d*> _texture_1ds;
    std::unordered_map<std::string, gl_texture_1d_array*> _texture_1d_arrays;
    std::unordered_map<std::string, gl_texture_rectangle*> _texture_rectangles;
    std::unordered_map<std::string, gl_texture_2d*> _texture_2ds;
    std::unordered_map<std::string, gl_texture_2d_array*> _texture_2d_arrays;
    std::unordered_map<std::string, gl_texture_cube*> _texture_cubes;
    std::unordered_map<std::string, gl_texture_cube_array*> _texture_cube_arrays;
    std::unordered_map<std::string, gl_texture_2d_multisample*> _texture_2d_multisamples;
    std::unordered_map<std::string, gl_texture_2d_multisample_array*> _texture_2d_multisample_arrays;
    std::unordered_map<std::string, gl_texture_3d*> _texture_3ds;
    std::unordered_map<std::string, gl_texture_buffer*> _texture_buffers;
    std::unordered_map<std::string, gl_renderbuffer*> _renderbuffers;
    std::unordered_map<std::string, gl_renderbuffer_multisample*> _renderbuffer_multisamples;
    std::unordered_map<std::string, gl_framebuffer*> _framebuffers;
    std::unordered_map<std::string, gl_graphics_pipeline*> _graphics_pipelines;
    std::unordered_map<std::string, gl_compute_pipeline*> _compute_pipelines;

};

enum class gl_renderer_state
{
    uninitialized,
    standby,
    running,
    paused,
    stopped
};

class gl_renderer
{
public:
    gl_renderer() :
        _state(gl_renderer_state::uninitialized),
        _exit(false)
    {

    }

    ~gl_renderer() = default;

public:

    void initialize()
    {
        if (_state == gl_renderer_state::uninitialized)
        {
            _implementation_build();
            _state = gl_renderer_state::standby;
        }
    }

    void render(float delta_time)
    {
        _implementation_render(delta_time);
    }

public:

    bool should_exit()
    {
        return _exit;
    }

    void set_exit(bool exit)
    {
        _exit = exit;
    }

    void switch_state(gl_renderer_state state)
    {
        switch (state)
        {
        case gl_renderer_state::uninitialized:
            break;
        case gl_renderer_state::standby:
            break;
        case gl_renderer_state::running:
            break;
        case gl_renderer_state::paused:
            break;
        case gl_renderer_state::stopped:
            break;
        default:
            break;
        }
    }

private:

    gl_renderer_state _state;

    bool _exit;

protected:
    virtual  void _implementation_build() = 0;
    virtual void _implementation_render(float delta_time) = 0;

    void _flush_commands() { glFlush(); }
    void _finish_commands() { glFinish(); }

    gl_renderer_builder _renderer_builder;

#define builder _renderer_builder
#define default_framebuffer gl_default_framebuffer::get_instance()

std::function<void(uint32, uint32)>  _on_window_size_changed;
std::function<void(void)> _on_renderer_detached;
std::function<void(void)> _on_renderer_attached;

#define on_window_size_changed _on_window_size_changed
#define on_renderer_detached _on_renderer_detached
#define on_renderer_attached _on_renderer_attached

};


#define DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\
public:\
    RENDERER_NAME() = default;\
    RENDERER_NAME(const RENDERER_NAME&) = delete;\
    RENDERER_NAME& operator=(const RENDERER_NAME&) = delete;\
    ~RENDERER_NAME() = default;\


#define IMPLEMENTATION_FUNC_BUILD()\
protected:\
void _implementation_build() override\

#define IMPLEMENTATION_FUNC_RENDER()\
protected:\
void _implementation_render(std::float_t delta_time) override\


#define DEFINE_RENDERER_BEGIN(RENDERER_NAME)\
class RENDERER_NAME final : public gl_renderer{\
DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\

#define DEFINE_RENDERER_END };










#endif

