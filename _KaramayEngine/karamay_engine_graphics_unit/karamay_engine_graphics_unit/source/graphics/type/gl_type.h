#pragma once
#include "public/opengl.h"



class gl_basic_type
{
};

class gl_transparent_type : public gl_basic_type
{

};



class gl_scalar_base : public gl_transparent_type
{

};

class gl_bool : public gl_scalar_base
{};

class gl_int : public gl_scalar_base
{};

class gl_uint : public gl_scalar_base
{};

class gl_float : public gl_scalar_base
{};

class gl_double : public gl_scalar_base
{};

class gl_vector_base : public gl_transparent_type
{};

class gl_bvec2 : public gl_vector_base
{};

class gl_bvec3 : public gl_vector_base
{};

class gl_bvec4 : public gl_vector_base
{};

class gl_ivec2 : public gl_vector_base
{};

class gl_ivec3 : public gl_vector_base
{};

class gl_ivec4 : public gl_vector_base
{};

class gl_vec2 : public gl_vector_base
{};

class gl_vec3 : public gl_vector_base
{};

class gl_vec4 : public gl_vector_base
{};

class gl_dvec2 : public gl_vector_base
{};

class gl_dvec3 : public gl_vector_base
{};

class gl_dvec4 : public gl_vector_base
{};




class gl_matrix_base : public gl_transparent_type
{};




class gl_opaque_type : public gl_basic_type
{};

class gl_sampler_base : public gl_opaque_type
{

};

class gl_image_base : public gl_opaque_type
{

};

class gl_atomic_counter : public gl_opaque_type
{

};





class gl_struct
{

};