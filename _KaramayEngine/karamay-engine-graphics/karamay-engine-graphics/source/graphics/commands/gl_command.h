#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_command
{
	class draw
	{
	public:
		static void draw_arrays(){}
		static void draw_arrays_indirect() {}
		static void draw_arrays_instanced() {}
		static void draw_arrays_instanced_base_instance() {}

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

