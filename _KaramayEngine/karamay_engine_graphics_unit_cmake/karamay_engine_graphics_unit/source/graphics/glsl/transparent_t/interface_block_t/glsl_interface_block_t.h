#ifndef GLSL_INTERFACE_BLOCK_T_H
#define GLSL_INTERFACE_BLOCK_T_H

#include "graphics/glsl/transparent_t/glsl_transparent_t.h"

/*
 *
 * */
class glsl_interface_block_t{
public:
    glsl_interface_block_t() = default;
    ~glsl_interface_block_t() = default;

private:

    std::vector<std::pair<const glsl_transparent_t*, std::string>> _cached_items;

};

enum class glsl_uniform_block_memory_qualifier
{

};

class glsl_uniform_block_t : public glsl_interface_block_t{
public:

};

enum class glsl_buffer_block_memory_qualifier
{

};

class glsl_buffer_block_t : public glsl_interface_block_t{
public:

};



#endif
