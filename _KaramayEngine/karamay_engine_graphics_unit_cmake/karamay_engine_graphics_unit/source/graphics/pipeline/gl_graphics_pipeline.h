#ifndef H_GRAPHICS_PIPELINE
#define H_GRAPHICS_PIPELINE

#include "graphics/program/gl_program.h"

class gl_graphics_pipeline
{
public:

    gl_graphics_pipeline()= default;

public:

    void attribute_stream() {}

public:

    void immutable_blocks() {}

    void mutable_blocks() {}

    void atomic_blocks() {}

    void textures() {}

public:

    void set_framebuffer() {}

private:

    std::shared_ptr<gl_program> _program;

};

#endif

