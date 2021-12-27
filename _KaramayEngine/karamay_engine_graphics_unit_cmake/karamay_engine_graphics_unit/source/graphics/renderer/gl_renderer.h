#ifndef H_RENDERER
#define H_RENDERER

#include "pipeline/gl_graphics_pipeline.h"
#include "pipeline/gl_compute_pipeline.h"


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

protected:

    class gl_renderer_builder final
    {
    public:
        gl_renderer_builder() = default;

        gl_renderer_builder(const gl_renderer_builder&) = delete;
        gl_renderer_builder& operator=(const gl_renderer_builder&) = delete;

        ~gl_renderer_builder()
        {
            for (auto _buffer : _buffers) { delete _buffer; }
            for (auto _tex_1d : _texture_1ds) { delete _tex_1d; }
            for (auto _tex_1d_arr : _texture_1d_arrays) { delete _tex_1d_arr; }
            for (auto _tex_2d : _texture_2ds) { delete _tex_2d; }
            for (auto _tex_2d_arr : _texture_2d_arrays) { delete _tex_2d_arr; }
            for (auto _tex_2d_ms : _texture_2d_multisamples) { delete _tex_2d_ms; }
            for (auto _tex_2d_ms_arr : _texture_2d_multisample_arrays) { delete _tex_2d_ms_arr; }
            for (auto _tex_rect : _texture_rectangles) { delete _tex_rect; }
            for (auto _tex_cube : _texture_cubes) { delete _tex_cube; }
            for (auto _tex_cube_arr : _texture_cube_arrays) { delete _tex_cube_arr; }
            for (auto _tex_3d : _texture_3ds) { delete _tex_3d; }
            for (auto _tex_buffer : _texture_buffers) { delete _tex_buffer; }
            for (auto _renderbuffer : _renderbuffers) { delete _renderbuffer; }
            for (auto _renderbuffer_ms : _renderbuffer_multisamples) { delete _renderbuffer_ms; }
            for (auto _framebuffer : _framebuffers) { delete _framebuffer; }
        }

    public:

        // GL_MAX_ARRAY_TEXTURE_LAYERS
        // GL_MAX_3D_TEXTURE_SIZE 
        // GL_MAX_TEXTURE_SIZE
        gl_buffer* build_buffer(gl_buffer_storage_options options, int64 bytes_num, const void* initial_data = nullptr)
        {
            auto _buffer = new gl_buffer(options, bytes_num, initial_data);
            _buffers.push_back(_buffer);
            return _buffer;
        }

        gl_uniform_buffer* build_uniform_buffer()
        {
            return nullptr;
        }
        gl_shader_storage_buffer* build_shader_storage_buffer()
        {
            return nullptr;
        }

        gl_texture_1d* build_texture_1d(gl_texture_internal_format format, uint32 width, uint32 mipmaps_num)
        {
            auto _texture_1d = new gl_texture_1d(static_cast<int32>(mipmaps_num), format, static_cast<int32>(width));
            _texture_1ds.push_back(_texture_1d);
            return _texture_1d;
        }
        gl_texture_1d_array* build_texture_1d_array(gl_texture_internal_format format, uint32 width, uint32 mipmaps_num, uint32 elements_num)
        {
            auto _texture_1d_array = new gl_texture_1d_array(
                static_cast<int32>(elements_num),
                static_cast<int32>(mipmaps_num),
                static_cast<int32>(width),
                format);
            _texture_1d_arrays.push_back(_texture_1d_array);
            return _texture_1d_array;
        }

        gl_texture_2d* 
            build_texture_2d(gl_texture_internal_format format, uint32 width, uint32 height, uint32 mipmaps_num)
        {
            if (width > 1024 || height > 1024 || mipmaps_num > 100)
            {
                std::cerr << "width, heigth, mipmaps_num :: format error" << std::endl;
                return nullptr;
            }
            auto _texture_2d = new gl_texture_2d(mipmaps_num, format, width, height);
            _texture_2ds.push_back(_texture_2d);
            return _texture_2d;
        }
        gl_texture_2d_array* 
            build_texture_2d_array(gl_texture_internal_format format, uint32 width, uint32 height, uint32 mipmaps_num, uint32 elements_num)
        {
            auto _texture_2d_array = new gl_texture_2d_array(elements_num, mipmaps_num, width, height, format);
            _texture_2d_arrays.push_back(_texture_2d_array);
            return _texture_2d_array;
        }
        gl_texture_rectangle* 
            build_texture_rectangle(gl_texture_internal_format format, uint32 width, uint32 height)
        {
            auto _tex_rect = new gl_texture_rectangle(width, height, format);
            _texture_rectangles.push_back(_tex_rect);
            return _tex_rect;
        }
        gl_texture_cube* 
            build_texture_cube(gl_texture_internal_format format, uint32 width, uint32 height, uint32 mipmaps_num)
        {
            auto _tex_cube = new gl_texture_cube(mipmaps_num, format, width, height);
            _texture_cubes.push_back(_tex_cube);
            return _tex_cube;
        }
        gl_texture_cube_array* 
            build_texture_cube_array(gl_texture_internal_format format, uint32 width, uint32 height, uint32 mipmaps_num, uint32 elements_num)
        {
            auto _tex_cube_arr = new gl_texture_cube_array(elements_num, mipmaps_num, format, width, height);
            _texture_cube_arrays.push_back(_tex_cube_arr);
            return _tex_cube_arr;
        }
        gl_texture_2d_multisample* 
            build_texture_2d_multisample(gl_texture_internal_format format, uint32 samples_num, bool fixed_sample, uint32 width, uint32 height)
        {
            auto _tex_2d_ms = new gl_texture_2d_multisample(format, samples_num, fixed_sample, width, height);
            _texture_2d_multisamples.push_back(_tex_2d_ms);
            return _tex_2d_ms;
        }
        gl_texture_2d_multisample_array* 
            build_texture_2d_multisample_array(gl_texture_internal_format format, uint32 samples_num, bool fixed_sample, uint32 width, uint32 height, uint32 elements_num)
        {
            auto _tex_2d_ms_arr = new gl_texture_2d_multisample_array(format, samples_num, fixed_sample, width, height, elements_num);
            _texture_2d_multisample_arrays.push_back(_tex_2d_ms_arr);
            return _tex_2d_ms_arr;
        }
        gl_texture_3d* 
            build_texture_3d(gl_texture_internal_format format, uint32 width, uint32 height, uint32 depth, uint32 mipmaps_num)
        {
            auto _tex_3d = new gl_texture_3d(format, width, height, depth, mipmaps_num);
            _texture_3ds.push_back(_tex_3d);
            return _tex_3d;
        }
        gl_texture_buffer* 
            build_texture_buffer(gl_texture_internal_format format, gl_buffer* buffer)
        {
            auto _tex_buffer = new gl_texture_buffer(buffer, format);
            _texture_buffers.push_back(_tex_buffer);
            return _tex_buffer;
        }

        gl_renderbuffer* 
            build_renderbuffer(gl_renderbuffer_internal_format format, uint32 width, uint32 height)
        {
            auto _renderbuffer = new gl_renderbuffer(width, height, format);
            _renderbuffers.push_back(_renderbuffer);
            return _renderbuffer;
        }
        gl_renderbuffer_multisample* 
            build_renderbuffer_multisample(gl_renderbuffer_internal_format format, uint32 samples_num, uint32 width, uint32 height)
        {
            auto _renderbuffer_ms = new gl_renderbuffer_multisample(samples_num, width, height, format);
            _renderbuffer_multisamples.push_back(_renderbuffer_ms);
            return _renderbuffer_ms;
        }

        gl_framebuffer* 
            build_framebuffer(uint32 width, uint32 height)
        {
            auto _framebuffer = new gl_framebuffer(width, height);
            _framebuffers.push_back(_framebuffer);
            return _framebuffer;
        }

        gl_graphics_pipeline* 
            build_graphics_pipeline(glsl_vertex_shader* vs, glsl_fragment_shader* fs)
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, fs);
            _graphics_pipelines.push_back(_graphics_pipeline);
            return _graphics_pipeline;
        }
        gl_graphics_pipeline* 
            build_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_fragment_shader* fs)
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, ts, fs);
            _graphics_pipelines.push_back(_graphics_pipeline);
            return _graphics_pipeline;
        }
        gl_graphics_pipeline* 
            build_graphics_pipeline(glsl_vertex_shader* vs, glsl_geometry_shader* gs, glsl_fragment_shader* fs)
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, gs, fs);
            _graphics_pipelines.push_back(_graphics_pipeline);
            return _graphics_pipeline;
        }
        gl_graphics_pipeline* 
            build_graphics_pipeline(glsl_vertex_shader* vs, glsl_tessellation_shader* ts, glsl_geometry_shader* gs, glsl_fragment_shader* fs)
        {
            auto _graphics_pipeline = new gl_graphics_pipeline(vs, ts, gs, fs);
            _graphics_pipelines.push_back(_graphics_pipeline);
            return _graphics_pipeline;
        }
        gl_compute_pipeline* 
            build_compute_pipeline(glsl_compute_shader* cs)
        {
            auto _compute_pipeline = new gl_compute_pipeline(cs);
            _compute_pipelines.push_back(_compute_pipeline);
            return _compute_pipeline;
        }

    private:

        std::vector<gl_buffer*> _buffers;
        std::vector<gl_texture_1d*> _texture_1ds;
        std::vector<gl_texture_1d_array*> _texture_1d_arrays;
        std::vector<gl_texture_rectangle*> _texture_rectangles;
        std::vector<gl_texture_2d*> _texture_2ds;
        std::vector<gl_texture_2d_array*> _texture_2d_arrays;
        std::vector<gl_texture_cube*> _texture_cubes;
        std::vector<gl_texture_cube_array*> _texture_cube_arrays;
        std::vector<gl_texture_2d_multisample*> _texture_2d_multisamples;
        std::vector<gl_texture_2d_multisample_array*> _texture_2d_multisample_arrays;
        std::vector<gl_texture_3d*> _texture_3ds;
        std::vector<gl_texture_buffer*> _texture_buffers;
        std::vector<gl_renderbuffer*> _renderbuffers;
        std::vector<gl_renderbuffer_multisample*> _renderbuffer_multisamples;
        std::vector<gl_framebuffer*> _framebuffers;
        std::vector<gl_graphics_pipeline*> _graphics_pipelines;
        std::vector<gl_compute_pipeline*> _compute_pipelines;

    }_renderer_builder;
    
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

