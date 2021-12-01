#ifndef H_RENDERER
#define H_RENDERER

#include "public/stl.h"
#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/pipeline/compute/gl_compute_pipeline.h"
#include "graphics/resource/texture/gl_texture.h"

class gl_graphics_pipeline;
class gl_vertex_processing_pipeline;
class gl_compute_pipeline;

class gl_renderer_builder
{
public:
    gl_renderer_builder() = default;

    ~gl_renderer_builder()
    {
        for (auto _tex_1d : _texture_1ds) { delete _tex_1d;std::cout << "delete tex_1d" << std::endl; }
        for (auto _tex_2d : _texture_2ds) { delete _tex_2d; std::cout << "delete tex_2d" << std::endl; }
    }

public:

    gl_texture_1d* texture_1d(int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format)
    {
        auto _texture_1d = new gl_texture_1d(mipmaps_num, internal_format, width);
        _texture_1ds.push_back(_texture_1d);
        return _texture_1d;
    }
    gl_texture_1d_array* texture_1d_array(int32 elements_num, int32 mipmaps_num, int32 width, gl_texture_internal_format internal_format) 
    {
        auto _texture_1d_array = new gl_texture_1d_array(elements_num,mipmaps_num, width, internal_format);
        _texture_1d_arrays.push_back(_texture_1d_array);
        return _texture_1d_array;
    }
    gl_texture_2d* texture_2d(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height) 
    {
        auto _texture_2d = new gl_texture_2d(mipmaps_num, internal_format, width, height);
        _texture_2ds.push_back(_texture_2d);
        return _texture_2d;
    }
    gl_texture_2d_array* texture_2d_array(int32 elements_num, int32 mipmaps_num, int32 width, int32 height, gl_texture_internal_format internal_format) 
    {
        auto _texture_2d_array = new gl_texture_2d_array(elements_num, mipmaps_num, width, height, internal_format);
        _texture_2d_arrays.push_back(_texture_2d_array);
        return _texture_2d_array;
    }
    gl_texture_rectangle* texture_rectangle(int32 width, int32 height, gl_texture_internal_format internal_format)
    {
        auto _tex_rect = new gl_texture_rectangle(width, height, internal_format);
        _texture_rectangles.push_back(_tex_rect);
        return _tex_rect;
    }
    gl_texture_cube* texture_cube(int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
    {
        auto _tex_cube = new gl_texture_cube(mipmaps_num, internal_format, width, height);
        _texture_cubes.push_back(_tex_cube);
        return _tex_cube;
    }
    gl_texture_cube_array* texture_cube_array(int32 elements_num, int32 mipmaps_num, gl_texture_internal_format internal_format, int32 width, int32 height)
    {
        auto _tex_cube_arr = new gl_texture_cube_array(elements_num, mipmaps_num, internal_format, width, height);
        _texture_cube_arrays.push_back(_tex_cube_arr);
        return _tex_cube_arr;
    }
    gl_texture_2d_multisample* texture_2d_multisample(int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
    {
        auto _tex_2d_ms = new gl_texture_2d_multisample(samples_num, internal_format, width, height, fixed_sample_locations);
        _texture_2d_multisamples.push_back(_tex_2d_ms);
        return _tex_2d_ms;
    }
    gl_texture_2d_multisample_array* texture_2d_multisample_array(int32 elements_num, int32 samples_num, gl_texture_internal_format internal_format, int32 width, int32 height, bool fixed_sample_locations)
    {
        auto _tex_2d_ms_arr = new gl_texture_2d_multisample_array(elements_num, samples_num, internal_format, width, height, fixed_sample_locations);
        _texture_2d_multisample_arrays.push_back(_tex_2d_ms_arr);
        return _tex_2d_ms_arr;
    }
    gl_texture_3d* texture_3d(int32 mipmaps_num, int32 width, int32 height, int32 depth, gl_texture_internal_format internal_format) 
    {
        auto _tex_3d = new gl_texture_3d(mipmaps_num, width, height, depth, internal_format);
        _texture_3ds.push_back(_tex_3d);
        return _tex_3d;
    }
    gl_texture_buffer* texture_buffer(gl_buffer* buffer, gl_texture_internal_format internal_format) { return nullptr; }

private:

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

};

/*
* Every Renderer's resource refs must be dependent to each other.
* 
* 
*/
class gl_renderer
{
public:

    gl_renderer(){}

    ~gl_renderer() = default;

protected:

    gl_renderer_builder _renderer_builder;

#define builder _renderer_builder


};


#define DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\
public:\
    static std::shared_ptr<RENDERER_NAME> _instance;\
    RENDERER_NAME() = default;\
    RENDERER_NAME(const gl_static_mesh_renderer&) = delete;\
    RENDERER_NAME& operator=(const RENDERER_NAME&) = delete;\
    ~RENDERER_NAME() = default;\
public:\
    static std::shared_ptr<RENDERER_NAME> invoke()\
    {\
        if (!_instance)\
        {\
            _instance = std::make_shared<RENDERER_NAME>();\
        }\
        return _instance;\
    }\


#define IMPLEMENTATION_FUNC_BUILD()\
protected:\
void _implementation_build(gl_renderer_builder& builder) override\

#define IMPLEMENTATION_FUNC_RENDER()\
protected:\
void _implementation_render(std::float_t delta_time) override\


#define DEFINE_RENDERER_BEGIN(RENDERER_NAME)\
class RENDERER_NAME final : protected gl_renderer{\
DEFINE_RENDERER_CONSTRUCTOR(RENDERER_NAME)\

#define DEFINE_RENDERER_END()\
};\










#endif

