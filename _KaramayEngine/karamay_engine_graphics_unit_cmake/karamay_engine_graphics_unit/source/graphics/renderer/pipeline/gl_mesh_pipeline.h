#ifndef GL_MESH_PIPELINE_H
#define GL_MESH_PIPELINE_H

#include "base/gl_pipeline.h"

class gl_mesh_launcher
{
public:
    gl_mesh_launcher() = default;

};

class gl_mesh_pipeline final : public gl_pipeline
{
public:
    gl_mesh_pipeline(glsl_mesh_pipeline_program* mesh_pipeline_program)
    {
        _mesh_pipeline_program.reset(mesh_pipeline_program);
    }

    gl_mesh_pipeline(const gl_mesh_pipeline&) = delete;
    gl_mesh_pipeline& operator=(const gl_mesh_pipeline&) = delete;

    ~gl_mesh_pipeline() = default;

public:

    bool load(const std::string& pipeline_dir) noexcept override
    {
        if(!_mesh_pipeline_program || !_mesh_pipeline_program->load(pipeline_dir)) return false;
        std::cout << "pipeline : " << long long(this) << " load succuessfully." << std::endl;
        return true;
    }

    void enable() noexcept override
    {
        _mesh_pipeline_program->enable();
    }

    void disable() noexcept override
    {
        _mesh_pipeline_program->disable();
    }

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