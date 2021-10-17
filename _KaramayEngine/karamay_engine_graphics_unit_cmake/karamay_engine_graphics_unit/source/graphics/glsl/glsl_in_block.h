#ifndef GLSL_IN_BLOCK_H
#define GLSL_IN_BLOCK_H

#include "glsl_class.h"

/*
 * these blocks cannot control their value directly.
 * exp :
 *
 * vertex_shader:
 * in InVertexData{ ... } inData;
 * out OutVertexData{ ... } outData;
 *
 * tessellation evaluation shader:
 * in InVertexData{ ... } inData[];
 * out InVertexData{ ... } outData[];
 *
 * geometry shader:
 *
 *
 *
 * */
class glsl_in_block_t : public glsl_t{
public:

    std::string token()
    {
        std::string _token("in VertexData {};");

        return _token;
    }

};

#endif
