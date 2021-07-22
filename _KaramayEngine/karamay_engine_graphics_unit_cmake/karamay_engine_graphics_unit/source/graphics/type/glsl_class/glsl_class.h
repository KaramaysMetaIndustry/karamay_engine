#ifndef H_GLSL_CLASS
#define H_GLSL_CLASS

#include "public/_glew.h"
#include "public/glm.h"
#include "public/stl.h"

class glsl_clazz
{

};

class glsl_class
{
public:

    virtual const std::uint8_t* stream() const { return nullptr; }
    virtual std::int64_t stream_size() const {return 0;}
};

#endif
