#pragma once
#include "public/stl.h"
namespace karamay
{
	namespace graphics
	{

		class vertex_set
		{

		};

		class uniform
		{

		};

		class texture_2d
		{

		};

		class framebuffer
		{
			std::float_t _width, _height;

		};



		class pipeline
		{
		public:
			
			void set_vertex_set(std::shared_ptr<vertex_set> set);

			void set_framebuffer(std::shared_ptr<framebuffer> target);


		private:

			std::shared_ptr<vertex_set> _vertex_set;

			std::shared_ptr<framebuffer> _framebuffer;


		};

	}
}


