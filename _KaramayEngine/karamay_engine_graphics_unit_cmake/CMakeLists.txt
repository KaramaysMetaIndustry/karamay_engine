cmake_minimum_required(VERSION 3.14)
project(karamay_engine_graphics_unit)

set(CMAKE_CXX_STANDARD 17)
set(BUILD_ARCH "-m64") 



link_libraries(opengl32.lib)
#
link_libraries(glew32s.lib)
#link_directories(karamay_engine_graphics_unit/dependencies/glew-2.1.0/lib/Release/Win32/)
link_directories(karamay_engine_graphics_unit/dependencies/glew-2.1.0/lib/Release/x64/)

link_libraries(glfw3.lib)
#link_directories(karamay_engine_graphics_unit/dependencies/glfw-3.3.bin.WIN32/lib-vc2019/)
link_directories(karamay_engine_graphics_unit/dependencies/glfw-3.3.4.bin.WIN64/lib-vc2019/)

include_directories(karamay_engine_graphics_unit/dependencies)
include_directories(karamay_engine_graphics_unit/dependencies/glm_pack/include)
include_directories(karamay_engine_graphics_unit/source)

add_executable(karamay_engine_graphics_unit
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_features.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_fixes.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_noise.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_swizzle.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_swizzle_func.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/_vectorize.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/compute_common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/compute_vector_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_common_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_exponential.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_exponential_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_geometric.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_geometric_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_integer.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_integer_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_matrix.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_matrix_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_packing.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_packing_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_trigonometric.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_trigonometric_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_vector_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/func_vector_relational_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/glm.cpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/qualifier.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/setup.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_float.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_half.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_half.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x2.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x3.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat2x4.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x2.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x3.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat3x4.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x2.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x3.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x4.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_mat4x4_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_quat.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_quat.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_quat_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec1.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec2.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec3.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec4.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/detail/type_vec4_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_clip_space.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_clip_space.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double2x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double3x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_double4x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float2x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float3x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_float4x4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_projection.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_projection.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_transform.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/matrix_transform.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_common_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_double.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_double_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_exponential.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_exponential.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_float.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_float_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_geometric.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_geometric.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_transform.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_transform.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_trigonometric.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/quaternion_trigonometric.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_constants.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_constants.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_int_sized.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_uint_sized.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_ulp.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/scalar_ulp.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool1_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_bool4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double1_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_double4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float1_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_float4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int1_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_int4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint1_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint2_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint3_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_uint4_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_ulp.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext/vector_ulp.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/bitfield.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/bitfield.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/color_space.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/color_space.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/constants.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/constants.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/epsilon.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/epsilon.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/integer.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/integer.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_access.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_access.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_integer.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_inverse.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_inverse.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_transform.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/matrix_transform.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/noise.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/noise.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/packing.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/packing.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/quaternion.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/quaternion.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/quaternion_simd.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/random.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/random.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/reciprocal.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/reciprocal.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/round.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/round.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/type_aligned.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/type_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/type_precision.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/type_ptr.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/type_ptr.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/ulp.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/ulp.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtc/vec1.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/associated_min_max.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/associated_min_max.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/bit.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/bit.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/closest_point.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/closest_point.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_encoding.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_encoding.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_space.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_space.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_space_YCoCg.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/color_space_YCoCg.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/common.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/compatibility.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/compatibility.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/component_wise.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/component_wise.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/dual_quaternion.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/dual_quaternion.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/easing.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/easing.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/euler_angles.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/euler_angles.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/extend.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/extend.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/extended_min_max.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/extended_min_max.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/exterior_product.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/exterior_product.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_exponential.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_exponential.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_square_root.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_square_root.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_trigonometry.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/fast_trigonometry.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/float_notmalize.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/functions.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/functions.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/gradient_paint.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/gradient_paint.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/handed_coordinate_space.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/handed_coordinate_space.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/hash.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/hash.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/integer.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/integer.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/intersect.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/intersect.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/io.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/io.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/log_base.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/log_base.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_cross_product.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_cross_product.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_decompose.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_decompose.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_factorisation.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_factorisation.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_interpolation.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_interpolation.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_major_storage.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_major_storage.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_operation.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_operation.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_query.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_query.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_transform_2d.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/matrix_transform_2d.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/mixed_product.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/mixed_product.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/norm.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/norm.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/normal.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/normal.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/normalize_dot.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/normalize_dot.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/number_precision.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/number_precision.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/optimum_pow.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/optimum_pow.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/orthonormalize.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/orthonormalize.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/perpendicular.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/perpendicular.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/polar_coordinates.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/polar_coordinates.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/projection.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/projection.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/quaternion.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/quaternion.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/range.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/raw_data.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/raw_data.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/rotate_normalized_axis.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/rotate_normalized_axis.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/rotate_vector.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/rotate_vector.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/scalar_multiplication.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/scalar_relational.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/scalar_relational.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/spline.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/spline.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/std_based_type.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/std_based_type.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/string_cast.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/string_cast.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/texture.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/texture.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/transform.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/transform.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/transform2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/transform2.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/type_aligned.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/type_aligned.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/type_trait.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/type_trait.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/vec_swizzle.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/vector_angle.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/vector_angle.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/vector_query.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/vector_query.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/wrap.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/gtx/wrap.inl
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/common.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/exponential.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/geometric.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/integer.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/matrix.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/packing.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/platform.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/trigonometric.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/simd/vector_relational.h
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/common.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/exponential.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/ext.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/fwd.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/geometric.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/glm.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/integer.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat2x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat2x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat2x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat3x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat3x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat3x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat4x2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat4x3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/mat4x4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/matrix.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/packing.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/trigonometric.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/vec2.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/vec3.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/vec4.hpp
        karamay_engine_graphics_unit/dependencies/glm_pack/include/glm/vector_relational.hpp
        karamay_engine_graphics_unit/dependencies/nlohmann/json.hpp
#        karamay_engine_graphics_unit/dependencies/stb/deprecated/rrsprintf.h
#        karamay_engine_graphics_unit/dependencies/stb/deprecated/stb_image.c
#        karamay_engine_graphics_unit/dependencies/stb/deprecated/stretch_test.c
#        karamay_engine_graphics_unit/dependencies/stb/deprecated/stretchy_buffer.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/cave_main.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/cave_mesher.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/cave_parse.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/cave_parse.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/cave_render.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/caveview.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/glext.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/glext_list.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/main.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/stb_gl.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/caveview/stb_glprog.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/oversample/main.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/oversample/stb_wingraph.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/pg_test/pg_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/prerelease/stb_lib.h
#        karamay_engine_graphics_unit/dependencies/stb/tests/sdf/sdf_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/vorbseek/vorbseek.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/c_lexer_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/fuzz_main.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/grid_reachability.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/herringbone_generator.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/herringbone_map.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/image_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/image_write_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/resample_test.cpp
#        karamay_engine_graphics_unit/dependencies/stb/tests/resample_test_c.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/stb.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/stb_c_lexer_fuzzer.cpp
#        karamay_engine_graphics_unit/dependencies/stb/tests/stb_cpp.cpp
#        karamay_engine_graphics_unit/dependencies/stb/tests/stb_static.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/stbi_read_fuzzer.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/stblib_test.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/stblib_test_companion.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_c_compilation.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_c_lexer.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_cpp_compilation.cpp
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_ds.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_ds_cpp.cpp
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_dxt.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_easyfont.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_image.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_image_write.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_perlin.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_siphash.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_sprintf.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_truetype.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_vorbis.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/test_voxel.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/textedit_sample.c
#        karamay_engine_graphics_unit/dependencies/stb/tests/tilemap_editor_integration_example.c
#        karamay_engine_graphics_unit/dependencies/stb/tools/build_matrix.c
#        karamay_engine_graphics_unit/dependencies/stb/tools/easy_font_maker.c
#        karamay_engine_graphics_unit/dependencies/stb/tools/make_readme.c
#        karamay_engine_graphics_unit/dependencies/stb/tools/trailing_whitespace.c
#        karamay_engine_graphics_unit/dependencies/stb/tools/unicode.c
#        karamay_engine_graphics_unit/dependencies/stb/stb.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_c_lexer.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_connected_components.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_divide.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_ds.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_dxt.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_easy_font.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_herringbone_wang_tile.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_hexwave.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_image.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_image_resize.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_image_write.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_include.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_leakcheck.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_perlin.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_rect_pack.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_sprintf.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_textedit.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_tilemap_editor.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_truetype.h
#        karamay_engine_graphics_unit/dependencies/stb/stb_vorbis.c
#        karamay_engine_graphics_unit/dependencies/stb/stb_voxel_render.h
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_atomic_counter_buffer.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_atomic_counter_buffer.h
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_element_array_buffer.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_element_array_buffer.h
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_shader_storage_buffer.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_shader_storage_buffer.h
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_uniform_buffer.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/specialization/gl_uniform_buffer.h
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_buffered_uniform_block.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_buffered_uniform_block.h
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_interface_block.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_interface_block.h
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_shader_storage_block.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_shader_storage_block.h
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_uniform_block.cpp
        karamay_engine_graphics_unit/source/graphics/buffers/interface_block/gl_uniform_block.h
        karamay_engine_graphics_unit/source/graphics/camera/gl_camera.cpp
        karamay_engine_graphics_unit/source/graphics/camera/gl_camera.h
        karamay_engine_graphics_unit/source/graphics/commands/gl_commands.cpp
        karamay_engine_graphics_unit/source/graphics/commands/gl_commands.h
        karamay_engine_graphics_unit/source/graphics/framebuffer/gl_default_framebuffer.cpp
        karamay_engine_graphics_unit/source/graphics/framebuffer/gl_default_framebuffer.h
        karamay_engine_graphics_unit/source/graphics/framebuffer/gl_framebuffer.cpp
        karamay_engine_graphics_unit/source/graphics/framebuffer/gl_framebuffer.h
        karamay_engine_graphics_unit/source/graphics/glo/gl_object.cpp
        karamay_engine_graphics_unit/source/graphics/glo/gl_object.h
        karamay_engine_graphics_unit/source/graphics/mesh/material/gl_material.cpp
        karamay_engine_graphics_unit/source/graphics/mesh/material/gl_material.h
        karamay_engine_graphics_unit/source/graphics/mesh/gl_mesh.cpp
        karamay_engine_graphics_unit/source/graphics/mesh/gl_mesh.h
        karamay_engine_graphics_unit/source/graphics/pipeline/gl_compute_pipeline.cpp
        karamay_engine_graphics_unit/source/graphics/pipeline/gl_compute_pipeline.h
        karamay_engine_graphics_unit/source/graphics/pipeline/gl_graphics_pipeline.cpp
        karamay_engine_graphics_unit/source/graphics/pipeline/gl_graphics_pipeline.h
        karamay_engine_graphics_unit/source/graphics/program/gl_program.cpp
        karamay_engine_graphics_unit/source/graphics/program/gl_program.h
        karamay_engine_graphics_unit/source/graphics/program_pipeline/gl_program_pipeline.cpp
        karamay_engine_graphics_unit/source/graphics/program_pipeline/gl_program_pipeline.h
        karamay_engine_graphics_unit/source/graphics/renderbuffer/gl_renderbuffer.cpp
        karamay_engine_graphics_unit/source/graphics/renderbuffer/gl_renderbuffer.h
        karamay_engine_graphics_unit/source/graphics/renderer/gl_renderer.cpp
        karamay_engine_graphics_unit/source/graphics/renderer/gl_renderer.h
        karamay_engine_graphics_unit/source/graphics/sampler/gl_sampler.cpp
        karamay_engine_graphics_unit/source/graphics/sampler/gl_sampler.h
        karamay_engine_graphics_unit/source/graphics/shader/gl_shader.cpp
        karamay_engine_graphics_unit/source/graphics/shader/gl_shader.h
        karamay_engine_graphics_unit/source/graphics/texture/base/gl_texture_base.cpp
        karamay_engine_graphics_unit/source/graphics/texture/base/gl_texture_base.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_1d/gl_texture_1d.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_1d/gl_texture_1d.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_1d/gl_texture_1d_array.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_1d/gl_texture_1d_array.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_array.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_array.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_array_multisample.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_array_multisample.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_multisample.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_2d_multisample.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_rectangle.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_2d/gl_texture_rectangle.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_3d/gl_texture_3d.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_3d/gl_texture_3d.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_buffer/gl_texture_buffer.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_buffer/gl_texture_buffer.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_cube/gl_texture_cube.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_cube/gl_texture_cube.h
        karamay_engine_graphics_unit/source/graphics/texture/texture_cube/gl_texture_cube_array.cpp
        karamay_engine_graphics_unit/source/graphics/texture/texture_cube/gl_texture_cube_array.h
        karamay_engine_graphics_unit/source/graphics/texture/gl_texture.h
        karamay_engine_graphics_unit/source/graphics/transform_feedback/gl_transform_feedback.cpp
        karamay_engine_graphics_unit/source/graphics/transform_feedback/gl_transform_feedback.h
        karamay_engine_graphics_unit/source/graphics/variable/gl_variable.cpp
        karamay_engine_graphics_unit/source/graphics/variable/gl_variable.h
        karamay_engine_graphics_unit/source/graphics/variable/glu_types.h
        karamay_engine_graphics_unit/source/graphics/variable/glv_types.h
        karamay_engine_graphics_unit/source/graphics/vertex_array/gl_vertex_array.cpp
        karamay_engine_graphics_unit/source/graphics/vertex_array/gl_vertex_array.h
        karamay_engine_graphics_unit/source/public/_glfw.h
        karamay_engine_graphics_unit/source/public/nlohmann_json.h
        karamay_engine_graphics_unit/source/public/_glew.h
        karamay_engine_graphics_unit/source/public/stb.h
        karamay_engine_graphics_unit/source/public/stl.h
        karamay_engine_graphics_unit/source/public/winsocket.h
        karamay_engine_graphics_unit/source/window/window.cpp
        karamay_engine_graphics_unit/source/window/window.h
        karamay_engine_graphics_unit/source/karamay-engine-graphics.cpp
        karamay_engine_graphics_unit/source/public/glm.h karamay_engine_graphics_unit/source/graphics/buffers/buffer/gl_buffer.cpp karamay_engine_graphics_unit/source/graphics/buffers/buffer/gl_buffer.h karamay_engine_graphics_unit/source/graphics/type/glsl_types.h karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/static_mesh_renderer/gl_static_mesh_renderer.cpp karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/static_mesh_renderer/gl_static_mesh_renderer.h karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/particle_system_renderer/gl_particle_system_renderer.cpp karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/particle_system_renderer/gl_particle_system_renderer.h karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/static_mesh_renderer/gl_instanced_static_mesh_renderer.cpp karamay_engine_graphics_unit/source/renderers/gl_template_renderer_family/static_mesh_renderer/gl_instanced_static_mesh_renderer.h karamay_engine_graphics_unit/source/dispatcher/gl_renderer_dispatcher.cpp karamay_engine_graphics_unit/source/dispatcher/gl_renderer_dispatcher.h karamay_engine_graphics_unit/source/graphics/buffers/buffer/gl_buffer_tools.h karamay_engine_graphics_unit/source/graphics/buffers/gl_buffers.h karamay_engine_graphics_unit/source/graphics/type/glsl_class/glsl_transparent_class/glsl_transparent_class.h karamay_engine_graphics_unit/source/graphics/type/glsl_class/glsl_class.h karamay_engine_graphics_unit/source/graphics/type/glsl_class/glsl_opaque_class/glsl_opaque_class.h karamay_engine_graphics_unit/source/graphics/type/glsl_class/glsl_transparent_class/glsl_transparent_class.cpp karamay_engine_graphics_unit/source/graphics/type/glsl.h "karamay_engine_graphics_unit/source/graphics/shader/gl_vertex_shader.h" "karamay_engine_graphics_unit/source/graphics/shader/gl_geometry_shader.h" "karamay_engine_graphics_unit/source/graphics/shader/gl_tessellation_control_shader.h" "karamay_engine_graphics_unit/source/graphics/shader/gl_tessellation_evaluation_shader.h" "karamay_engine_graphics_unit/source/graphics/shader/gl_fragment_shader.h" "karamay_engine_graphics_unit/source/graphics/shader/gl_fragment_shader.cpp" "karamay_engine_graphics_unit/source/graphics/pipeline/gl_ray_tracing_pipeline.h" "karamay_engine_graphics_unit/source/graphics/pipeline/gl_data_transfer_pipeline.h")

target_link_libraries(karamay_engine_graphics_unit glew32s.lib glfw3.lib)



file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/karamay_engine_graphics_unit/assets
#       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)