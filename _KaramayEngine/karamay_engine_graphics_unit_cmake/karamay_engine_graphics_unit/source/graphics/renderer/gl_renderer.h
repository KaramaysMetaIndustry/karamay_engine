#ifndef H_RENDERER
#define H_RENDERER

#include <utility>

#include "public/stl.h"

class gl_program;

class gl_renderer
{
public:

    explicit gl_renderer(std::string name) :
        _name(std::move(name))
    {}

protected:

    std::string _name;

public:

    virtual void assembly() = 0;

    virtual void render(std::float_t delta_time) = 0;

public:

    const std::string& name() { return _name; }

};

#endif

