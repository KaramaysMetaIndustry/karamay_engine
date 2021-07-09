#ifndef H_RENDERER
#define H_RENDERER

#include "public/stl.h"

class gl_program;

class gl_renderer
{
public:

    virtual void assembly() = 0;

    virtual void render(std::float_t delta_time) = 0;

};


#endif

