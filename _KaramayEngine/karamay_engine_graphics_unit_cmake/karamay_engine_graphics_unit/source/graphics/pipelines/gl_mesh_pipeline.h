#ifndef GL_MESH_PIPELINE_H
#define GL_MESH_PIPELINE_H
#include "graphics/pipelines/gl_pipeline.h"
#include "graphics/glsl/program/glsl_mesh_program.h"

class gl_mesh_launcher
{
public:
    gl_mesh_launcher() = default;

};

/*
* advanced rasterization pipeline, which is only supported by NV Turing GPU
* 
* task shader + mesh shader [+ fragment shader]
* mesh shader [+ fragment shader]
* 
*/
class gl_mesh_pipeline final : public gl_pipeline
{
public:
    gl_mesh_pipeline() = default;
    gl_mesh_pipeline(glsl_mesh_pipeline_program* program)
    {
        _mesh_pipeline_program.reset(program);
    }

    gl_mesh_pipeline(const gl_mesh_pipeline&) = delete;
    gl_mesh_pipeline& operator=(const gl_mesh_pipeline&) = delete;

    ~gl_mesh_pipeline() = default;

public:

    bool load(const std::string& pipeline_dir) noexcept override;

    void enable() noexcept override;

    void disable() noexcept override;

public:

    glsl_mesh_pipeline_program& program() { return *_mesh_pipeline_program; }

    gl_mesh_launcher& mesh_launcher() { return *_mesh_launcher; }

public:

    std::shared_ptr<gl_fence> syncable_draw_mesh_task(uint32 first, uint32 count)
    {
        unsyncable_draw_mesh_task(first, count);
        return std::make_shared<gl_fence>();
    }

    std::shared_ptr<gl_fence>  syncable_draw_mesh_task()
    {
        unsyncable_draw_mesh_task();
        return std::make_shared<gl_fence>();
    }

    void unsyncable_draw_mesh_task(uint32 first, uint32 count)
    {
        glDrawMeshTasksNV(first, count);
    }

    void unsyncable_draw_mesh_task()
    {
        glDrawMeshTasksIndirectNV(0);
    }

private:

    std::unique_ptr<glsl_mesh_pipeline_program> _mesh_pipeline_program = {};

    std::unique_ptr<gl_mesh_launcher> _mesh_launcher = {};

};

#endif