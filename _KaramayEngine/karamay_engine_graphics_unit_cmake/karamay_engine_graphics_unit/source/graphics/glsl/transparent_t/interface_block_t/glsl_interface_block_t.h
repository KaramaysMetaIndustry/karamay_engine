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
enum class glsl_shader_storage_block_memory_qualifier
{

};

/*
 * layout(std140/shared/packed) uniform {
 *      AcModel acModel;
 *      AcModel acModels[2];
 *      AsModel asModel;
 * };
 * */
class glsl_uniform_block_t : public glsl_interface_block_t{
public:
    glsl_uniform_block_t();

public:
    std::uint8_t* data;
    std::int32_t data_size;

};

/*
 * layout(std140/std430) buffer {
 *      AcModel acModel;
 *      AcModel acModels[2];
 *      AsModel asModel;
 * };
 * */
class glsl_shader_storage_block_t : public glsl_interface_block_t{
public:
    glsl_shader_storage_block_t();
public:

    std::uint8_t* data();
    std::int32_t size();


};


class glsl_shader_storage_block_t0 : public glsl_shader_storage_block_t{
public:
    struct AsModel{};
    struct AcModel{};

    AcModel model[2];
    AcModel make[2];
    AcModel ms[2][1];
    AsModel wait[2];
    //...


};



#endif
