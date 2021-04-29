// karamay-engine-graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graphics/texture/gl_texture.h"
#include "graphics/buffer/gl_buffer.h"

int main()
{
    std::cout << "Hello World!\n";


    auto texture_1d = gl_texture_1d::construct();

	gl_texture_pixels_package pixels_package;
	pixels_package.pixels = nullptr;
	pixels_package.format = gl_texture_pixels_format::RGBA;
	pixels_package.type = gl_texture_pixels_type::UNSIGNED_BYTE;
	pixels_package.width = 100;
	pixels_package.max_mipmaps_num_supported = 6;
	
	if (texture_1d) {
        texture_1d->allocate(gl_texture_internal_format::RGBA, pixels_package.width, pixels_package.max_mipmaps_num_supported);
		texture_1d->fill_base_mipmap(pixels_package);
		texture_1d->fill_miniature_mipmaps_automatically();
    }

	if (texture_1d) {
		texture_1d->allocate(gl_texture_internal_format::RGBA, pixels_package.width * 2, 7);
		texture_1d->fill_base_sub_mipmap(pixels_package, 0);
		texture_1d->fill_base_sub_mipmap(pixels_package, pixels_package.width);
		texture_1d->fill_miniature_mipmaps_automatically();
	}


	if (texture_1d) {
		texture_1d->allocate(gl_texture_internal_format::RGB, 100, 6);
		


	}


	if (texture_1d) {
		texture_1d->clear_mipmap(0, 0, 100, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		
	}





	auto buffer = gl_buffer::construct();
	if (buffer) {
		auto data_pack = gl_buffer_data_pack::construct();
		
		
		buffer->allocate(gl_buffer_type::UNIFORM_BUFFER, 100, {});
		buffer->fill(std::make_shared<gl_buffer_data_pack>());
	
		buffer->bind();
		buffer->unbind();
		
	}

	



}
