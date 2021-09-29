#ifndef H_GL_SHADER_STORAGE_BUFFER
#define H_GL_SHADER_STORAGE_BUFFER

#include "public/stl.h"
#include "graphics/buffers/specialization/gl_shader_storage_buffer.h"
#include "graphics/buffers/specialization/gl_uniform_buffer.h"

namespace gl_shader_storage_buffer_enum
{
	enum class layout
	{
		std140,
		std430
	};

	enum class matrix_layout
	{
		row_major,
		column_major
	};
}

class gl_shader_storage_buffer_descriptor final
{
public:

	gl_shader_storage_buffer_descriptor();

public:

private:
	
	gl_shader_storage_buffer_enum::layout _memory_layout;
	
	gl_shader_storage_buffer_enum::matrix_layout _matrix_memory_layout;

};


class gl_shader_storage_buffer final{
public:
    gl_shader_storage_buffer() = default;

private:
    std::vector<std::shared_ptr<glsl_shader_storage_block_t>> blocks;

};

#endif

