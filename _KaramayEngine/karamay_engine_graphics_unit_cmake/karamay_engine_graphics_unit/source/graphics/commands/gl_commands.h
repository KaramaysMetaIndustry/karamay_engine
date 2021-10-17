#ifndef H_GL_COMMANDS
#define H_GL_COMMANDS

#include "graphics/resource/glo/gl_object.h"

namespace gl_commands
{
	enum class primitive_mode : GLenum
	{
		POINTS = GL_POINTS,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		LINES = GL_LINES,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		PATCHES = GL_PATCHES
	};


	class draw
	{
	public:
		/**
		 * @mode: primitive mode
		 * @firt: start index
		 * @count: number of vertices
		 */
		static void draw_arrays(gl_commands::primitive_mode mode, GLint first, GLsizei count)
		{
			glDrawArrays(static_cast<GLenum>(mode), first, count);
		}
		
		/**
		 * 
		 */
		static void draw_arrays_instanced(gl_commands::primitive_mode mode, GLint first, GLsizei count, GLsizei instance_count)
		{
			glDrawArraysInstanced(static_cast<GLenum>(mode), first, count, instance_count);
		}
		
		static void draw_arrays_instanced_base_instance()
		{
			//glDrawArraysInstanced(static_)
		}
		static void draw_arrays_indirect() {}


		static void draw_elements() {}
		static void draw_elements_base_vertex() {}
		static void draw_elements_indirect() {}
		static void draw_elements_instanced() {}
		static void draw_elements_instanced_base_instance() {}
		static void draw_elements_instanced_base_vertex() {}
		static void draw_elements_instanced_base_vertex_base_instance() {}

		static void draw_range_elements() {}
		static void draw_range_elements_base_vertex() {}
		
		static void draw_transform_feedback() {}
		static void draw_transform_feedback_instanced() {}
		static void draw_transform_feedback_stream() {}
		static void draw_transform_feedback_stream_instanced() {}

	};

	class compute
	{

	};


	class framebuffer
	{
	public:
		static void set_color_template(GLclampf r, GLclampf g, GLclampf b, GLclampf a)
		{
			glClearColor(r, g, b, a);
		}

		static void set_depth_template(GLdouble depth)
		{
			glClearDepth(depth);
		}

		static void set_stencil_template(GLint s)
		{
			glClearStencil(s);
		}

		static void clear()
		{
			//glClear();
		}
	};
}

#endif

