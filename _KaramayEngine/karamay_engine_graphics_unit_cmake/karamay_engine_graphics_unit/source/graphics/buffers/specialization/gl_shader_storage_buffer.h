#ifndef H_GL_SHADER_STORAGE_BUFFER
#define H_GL_SHADER_STORAGE_BUFFER

#include "public/stl.h"
class gl_program;
class gl_buffer;

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


public:

	auto get_memory_layout() const { return _memory_layout; }

	auto get_matrix_memory_layout() const { return _matrix_memory_layout; }

};


class gl_shader_storage_buffer final
{
public:


private:

	void _fill_std140() 
	{
		
	}

	void _fill_std430();

public:

	~gl_shader_storage_buffer();

};

#endif

