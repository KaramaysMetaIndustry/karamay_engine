#ifndef GL_TEXTURE_BASE_H
#define GL_TEXTURE_BASE_H

#include "graphics/glo/gl_object.h"
#include "graphics/sampler/gl_sampler.h"
#include "gl_pixels.h"

enum class parameter : GLenum
{
	DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
	TEXTURE_BASE_LEVEL = GL_TEXTURE_BASE_LEVEL,
	TEXTURE_MAX_LEVEL = GL_TEXTURE_MAX_LEVEL,
	TEXTURE_SWIZZLE_R = GL_TEXTURE_SWIZZLE_R,
	TEXTURE_SWIZZLE_G = GL_TEXTURE_SWIZZLE_G,
	TEXTURE_SWIZZLE_B = GL_TEXTURE_SWIZZLE_B,
	TEXTURE_SWIZZLE_A = GL_TEXTURE_SWIZZLE_A,
	TEXTURE_SWIZZLE_RGBA = GL_TEXTURE_SWIZZLE_RGBA
};

enum class texture_swizzle_component : GLenum
{
	RED = GL_RED,
	GREEN = GL_GREEN,
	BLUE = GL_BLUE,
	ALPHA = GL_ALPHA,
	ZERO = GL_ZERO,
	ONE = GL_ONE
};

enum class depth_stencil_texture_mode : GLenum
{
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT
};

enum class gl_cube_face_index : GLenum {
	POSITIVE_X = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	NEGATIVE_X = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	POSITIVE_Y = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	NEGATIVE_Y = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	POSITIVE_Z = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	NEGATIVE_Z = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

enum class gl_texture_type : GLenum
{
	TEXTURE_BUFFER = GL_TEXTURE_BUFFER,

	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,

	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
	TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
	TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
	TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,

	TEXTURE_3D = GL_TEXTURE_3D,

	TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
	TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY
};


#define check_mipmap_index()\
if (mipmap_index < 0 || mipmap_index > mipmaps_count - 1)\
{\
	std::cerr << "mipmap_index out of bound [0, mipmaps_count - 1]" << std::endl;\
	return;\
}\


struct gl_texture_descriptor
{
	struct gl_texture_base_parameters
	{
		gl_depth_stencil_texture_mode  depth_stencil_texture_mode;
		std::int32_t texture_base_level;
		std::int32_t texture_max_level;
		gl_texture_swizzle_component texture_swizzle_r;
		gl_texture_swizzle_component texture_swizzle_g;
		gl_texture_swizzle_component texture_swizzle_b;
		gl_texture_swizzle_component texture_swizzle_a;
		std::float_t texture_lod_bias;

		gl_texture_base_parameters() :
			depth_stencil_texture_mode(),
			texture_base_level(0),
			texture_max_level(1000),
			texture_swizzle_r(gl_texture_swizzle_component::RED),
			texture_swizzle_g(gl_texture_swizzle_component::GREEN),
			texture_swizzle_b(gl_texture_swizzle_component::BLUE),
			texture_swizzle_a(gl_texture_swizzle_component::ALPHA),
			texture_lod_bias(0.0f)
		{}
	} base_parameters;
	

	//explicit gl_texture_descriptor(
	//	gl_depth_stencil_texture_mode _depth_stencil_texture_mode, 
	//	std::int32_t _texture_base_level, 
	//	std::int32_t _texture_max_level, 
	//	gl_texture_swizzle_component _texture_swizzle_r,
	//	gl_texture_swizzle_component _texture_swizzle_g,
	//	gl_texture_swizzle_component _texture_swizzle_b,
	//	gl_texture_swizzle_component _texture_swizzle_a,
	//	std::float_t _texture_lod_bias
	//) :
	//	depth_stencil_texture_mode(_depth_stencil_texture_mode),
	//	texture_base_level(_texture_base_level),
	//	texture_max_level(_texture_max_level),
	//	texture_swizzle_r(_texture_swizzle_r),
	//	texture_swizzle_g(_texture_swizzle_g),
	//	texture_swizzle_b(_texture_swizzle_b),
	//	texture_swizzle_a(_texture_swizzle_a),
	//	texture_lod_bias(_texture_lod_bias)
	//{}

};

class gl_texture_mipmappable
{
	virtual void generate_mipmaps() = 0;
};

class gl_texture_base : public gl_object
{
protected:

	gl_texture_base() = delete;
	gl_texture_base(gl_texture_type type):
		_type(type)
	{
		glCreateTextures(static_cast<GLenum>(_type), 1, &_handle);

	}
	
	~gl_texture_base() override
	{
		glDeleteTextures(1, &_handle);
	}

public:

	void bind()
	{
		std::uint32_t unit = 0;
		glBindTextureUnit(GL_TEXTURE0 + unit, _handle);
		_unit = unit;
	}

	void unbind() 
	{
		glBindTextureUnit(GL_TEXTURE0 + _unit, 0);
	}

protected:

	gl_texture_type _type;

	std::uint32_t _unit;

protected:

	static std::unordered_map<gl_texture_type, std::queue<std::uint32_t>> _texture_units;

};

/*
* normalized coordinates, mipmapping
* Images in this texture all are 1-dimensional. They have width, but no height or depth.
*/

class gl_texture_1d_base : public gl_texture_base
{
public:

	gl_texture_1d_base() :
		gl_texture_base(gl_texture_type::TEXTURE_1D)
	{}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_1D, _handle);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
	}

};

template<
	gl_image_format format, 
	std::int32_t width, 
	std::int32_t mipmaps_count
>
class gl_texture_1d : 
	public gl_texture_1d_base
{
public:
	
	using texture_t = gl_texture_1d<format, width, mipmaps_count>;
	using pixels_t = gl_pixels<format>;

	gl_texture_1d() :
		gl_texture_1d_base()
	{
		glTextureStorage1D(
			_handle,
			mipmaps_count,
			static_cast<GLenum>(format),
			width
		);

		_mipmaps_width[0] = width;
		for (std::int32_t _index = 1; _index < mipmaps_count; ++_index)
		{
			_mipmaps_width[_index] = _mipmaps_width[_index - 1] / 2;
		}
	}

	gl_texture_1d(const gl_texture_1d&) = default;
	
	~gl_texture_1d() = default;

public:

	void fill(std::int32_t mipmap_index, const pixels_t& pixels)
	{
		// check mipmap_index
		check_mipmap_index()
		// check pixels rangle
		if (mipmap_width(mipmap_index) != pixels.count())
		{
			std::cerr << "pixels count != fill size" << std::endl;
		}

		glTextureSubImage1D(_handle,
			mipmap_index, // level
			0, // offset 
			pixels.count(), // pixels count
			static_cast<GLenum>(pixels.pixel_format()), // pixels format 
			static_cast<GLenum>(pixels.pixel_type()), // pixels type
			pixels.data() // pixels data
		);
	}

	void fill(std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels)
	{
		check_mipmap_index()
		std::int32_t _mipmap_width = mipmap_width(mipmap_index);
		if (offset < 0 || offset + pixels.count() > _mipmap_width)
		{
			std::cerr << "pixels count != fill size" << std::endl;
			return;
		}

		glTextureSubImage1D(_handle,
			mipmap_index,
			offset, 
			pixels.count(),
			static_cast<GLenum>(pixels.format()), static_cast<GLenum>(pixels.type()), 
			pixels.data()
		);
	}

	void fill_mask(std::int32_t mipmap_index, const pixels_t& pixels_mask)
	{
		check_mipmap_index();

		if (mipmap_width(mipmap_index) % pixels_mask.count() != 0)
		{
			std::cerr << "" << std::endl;
			return;
		}

		glClearTexImage(_handle, // tex
			mipmap_index, // level
			static_cast<GLenum>(pixels_mask.pixel_format()), static_cast<GLenum>(pixels_mask.pixel_type()), 
			pixels_mask.data()
		);
	}

	void fill_mask(std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels_mask)
	{
		check_mipmap_index();

		if (offset < 0 || (mipmap_width(mipmap_index) - offset) % pixels_mask.count() != 0)
		{
			std::cerr << "" << std::endl;
			return;
		}
		
		glClearTexSubImage(_handle, // tex
			mipmap_index, // level
			offset, 0, 0, // x/y/z_offset
			pixels_mask.count(), 1, 1, // w/h/d
			static_cast<GLenum>(pixels_mask.pixel_format()), static_cast<GLenum>(pixels_mask.pixel_type()), 
			pixels_mask.data()
		);
	}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index)
	{
		auto _out_pixels = std::make_shared<pixels_t>();

		glGetTextureImage(_handle,
			mipmap_index, 
			_out_pixels.pixel_format(), _out_pixels.pixel_type(), 
			_out_pixels.pixel_size() * _out_pixels.count(), 
			_out_pixels.data()
		);

		return _out_pixels;
	}
	
	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index, std::int32_t offset, std::int32_t length)
	{
		auto _out_pixels = std::make_shared<pixels_t>();
		//_out_pixels->resize()
		glGetTextureSubImage(_handle,
			mipmap_index,
			offset, 0, 0,
			length, 1, 1,
			_out_pixels.pixel_format(), _out_pixels.pixel_type(), 
			_out_pixels.pixel_size() * _out_pixels.count(),
			_out_pixels.data()
		);
	}
	
	void invalidate(std::int32_t mipmap_index);
	
	void invalidate(std::int32_t mipmap_index, std::int32_t offset, std::int32_t length)
	{
		glInvalidateTexSubImage(
			_handle, 
			mipmap_index, 
			offset, 0, 0, 
			length, 1, 1
		);
	}

public:

	std::int32_t mipmap_size(std::int32_t mipmap_index)
	{
		if (mipmap_index < 0 || mipmap_index >= mipmaps_count) return -1;
		return _mipmaps_width[mipmap_index];
	}

private:

	std::array<std::int32_t, mipmaps_count> _mipmaps_width;

};

/*
* normalized coordinates, mipmapping, array
*
*/
class gl_texture_1d_array_base : 
	public gl_texture_base
{
public:
	gl_texture_1d_array_base() :
		gl_texture_base(gl_texture_type::TEXTURE_1D_ARRAY)
	{}

public:

	void generate_mipmaps(std::uint32_t target)
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
		glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	}

};

template<
	gl_image_format format, 
	std::int32_t length,
	std::int32_t mipmaps_count,
	std::int32_t elements_count 
>
class gl_texture_1d_array final : 
	public gl_texture_1d_array_base
{
public:
	using texture_t = gl_texture_1d_array<format, length, mipmaps_count, elements_count>;
	using pixels_t = gl_pixels<format>;

	gl_texture_1d_array()
	{
		glTextureStorage2D(
			_handle,
			mipmaps_count, static_cast<GLenum>(format),
			length,
			elements_count
		);
	}

	gl_texture_1d_array(const gl_texture_1d_array&) = default;
	gl_texture_1d_array& operator=(const gl_texture_1d_array&) = default;
	
	~gl_texture_1d_array() = default;

public:
	/* 
	* element_index [0, elements_count-1]	
	* mipmap_index [0, mipmaps_count-1]
	* 
	*/
	void fill(std::int32_t element_index, std::int32_t mipmap_index, const pixels_t& pixels) 
	{
		std::int32_t _mipmap_length = 0;
		if (element_index < 0 || element_index > elements_count - 1 || 
			mipmap_index < 0 || mipmap_index > _mipmaps_count -1 || _mipmap_length != pixels.count()
			) return;
		
		glTextureSubImage2D(_handle,
			mipmap_index,
			0, element_index, // x_offset, y_offset
			pixels.count(), 1, // width, height
			static_cast<GLenum>(pixels.pixel_format()), static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}

	/*
	* element_index [0, elements_count - 1]
	* mipmap_index [0, mipmaps_count - 1]
	* offset [0, elements_count - 1]
	* offset + pixels_count [0, elements_count]
	*/
	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels)
	{
		if (element_index < 0 || element_index >= elements_count ||
			mipmap_index < 0 || mipmap_index >= mipmaps_count ||
			offset < 0 || offset >= length
			) return;

		glTextureSubImage2D(_handle,
			mipmap_index, 
			offset, element_index, // x_offset, y_offset
			pixels.count(), 1, // width, height
			static_cast<GLenum>(pixels.pixel_format()), static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}
	/*
	* size % pixels_mask.count() == 0
	* 
	*/
	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index, const pixels_t& pixels_mask) noexcept
	{
		if (element_index < 0 || element_index > elements_count - 1)
		{
			std::cerr << "element_index out of bounds[0, elements_count - 1]" << std::endl;
			return;
		}

		if (mipmap_index < 0 || mipmap_index > mipmaps_count - 1)
		{
			std::cerr << "mipmap_index out of bounds[0, mipmaps_count - 1]" << std::endl;
			return;
		}

		if (pixels_mask.count() != mipmap_length(mipmap_index))
		{
			std::cerr << "pixels count does not fit" << std::endl;
			return;
		}

	}
	
	/*
	* (size - offset) % pixels_mask.count() == 0
	*  
	*/
	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const pixels_t pixels_mask) noexcept
	{

	}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index) {}
	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, std::int32_t length) {}
	void invalidate(std::int32_t element_index, std::int32_t mipmap_index) {}
	void invalidate(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, std::int32_t length) {}
	
private:

	std::int32_t mipmap_length(std::int32_t mipmap_index)
	{
		return 0;
	}
};

////////////////////////////////////////////////////////

/*
*  Images in this texture all are 2-dimensional. They have width and height, but no depth.
*/
class gl_texture_2d_base : public gl_texture_base
{};

template<
	gl_image_format format, 
	std::int32_t width, 
	std::int32_t height, 
	std::int32_t mipmaps_count
>
class gl_texture_2d final : 
	public gl_texture_2d_base
{
public:
	//static_assert()
	using texture_t = gl_texture_2d<format, width, height, mipmaps_count>;
	using pixels_t = gl_pixels<format>;

	gl_texture_2d()
	{
		glTextureStorage2D(_handle,
			mipmaps_count,
			static_cast<std::uint32_t>(format),
			width, height
		);
	}

	~gl_texture_2d() = default;

public:

	void fill(std::int32_t mipmap_index, const pixels_t& pixels)
	{
		if (!pixels) return;
		glTextureSubImage2D(_handle, 0,
			0, 0, descriptor.width, descriptor.height, 
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()), 
			pixels->data()
		);
	}

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{
		if (!pixels ||
			mipmap_index < 0 || mipmap_index >= mipmaps_count ||
			x_offset < 0 || x_offset >=  width ||
			y_offset < 0 || y_offset >=  height
			)return;

		glTextureSubImage2D(_handle,
			mipmap_index, x_offset, y_offset,
			0, 0, static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill_mask(std::int32_t mipmap_index, const pixels_t pixels_mask) {}

	void fill_mask(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels_mask)
	{}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index) {}

	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t pixels_count){}

	void invalidate(std::int32_t mipmap_index) {}

	void invalidate(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t pixels_count) {}

};

class gl_texture_2d_array_base : public gl_texture_base
{};

template<
	gl_image_format format, 
	std::int32_t width, 
	std::int32_t height, 
	std::int32_t mipmaps_count, 
	std::int32_t elements_count
>
class gl_texture_2d_array final : 
	public gl_texture_2d_array_base
{
public:

	gl_texture_2d_array()
	{
		glTextureStorage3D(_handle,
			mipmaps_count, static_cast<GLenum>(format),
			width, _descriptor.height,
			elements_count
		);
	}
	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array() override = default;

public:

	void fill(std::int32_t element_index, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0, 0, 0,
			element_index, descriptor.width, descriptor.height, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			0, x_offset, y_offset, element_index, 
			pixels->count(), pixels->count(), 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()), pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::shared_ptr<gl_pixels> pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			mipmap_index, x_offset, y_offset,
			element_index, 2, 2, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill_mask(std::int32_t element_index)
	{}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

};

struct gl_texture_rectangle_descriptor
{
	gl_image_format format;
	std::int32_t width, height;

	gl_texture_rectangle_descriptor(gl_image_format _format, std::int32_t _width, std::int32_t _height) :
		format(_format),
		width(_width), height(_height)
	{}

	gl_texture_rectangle_descriptor() = delete;
	gl_texture_rectangle_descriptor(const gl_texture_rectangle_descriptor&) = default;
	gl_texture_rectangle_descriptor& operator=(const gl_texture_rectangle_descriptor&) = default;

	~gl_texture_rectangle_descriptor() = default;
};

class gl_texture_rectangle_base : public gl_texture_base
{};

template<
	gl_image_format format, 
	std::int32_t width,
	std::int32_t height
>
class gl_texture_rectangle final : 
	public gl_texture_rectangle_base
{
public:
	
	gl_texture_rectangle()
	{
		glTextureStorage2D(_handle,
			1,
			static_cast<GLenum>(format),
			width,
			height
		);
	}
	gl_texture_rectangle(const gl_texture_rectangle_descriptor&) = delete;
	gl_texture_rectangle& operator=(const gl_texture_rectangle&) = delete;
	~gl_texture_rectangle() override = default;

	const gl_texture_rectangle_descriptor descriptor;

public:

	void fill(std::int32_t width, std::int32_t height, std::int32_t x_offset, std::int32_t y_offset, GLenum format, GLenum type, const void* pixels)
	{
		// GL_TEXTURE_RECTANGLE
		glTextureSubImage2D(_handle, 0, x_offset, y_offset, width, height, format, type, pixels);
	}

	void fill_mask() {}

};

struct gl_texture_cube_descriptor
{
	gl_image_format format;
	std::int32_t width;
	std::int32_t mipmaps_count;

	gl_texture_cube_descriptor(std::int32_t _width, gl_image_format _format, std::int32_t _mipmaps_count) :
		width(_width),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_descriptor(std::int32_t _width, gl_image_format _format) :
		width(_width),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_descriptor() = delete;
	gl_texture_cube_descriptor(const gl_texture_cube_descriptor&) = default;
	gl_texture_cube_descriptor& operator=(const gl_texture_cube_descriptor&) = default;

	~gl_texture_cube_descriptor() = default;
};

class gl_texture_cube final : 
	public gl_texture
{
public:

	gl_texture_cube() = delete;
	explicit gl_texture_cube(const gl_texture_cube_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_CUBE_MAP),
		descriptor(_descriptor)
	{
		glTextureStorage3D(_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.width,
			6
		);
	}

	gl_texture_cube(const gl_texture_cube&) = delete;
	gl_texture_cube& operator=(const gl_texture_cube&) = delete;

	~gl_texture_cube() override = default;

	const gl_texture_cube_descriptor descriptor;

public:

	void fill(
		gl_cube_face_index face_index,
		std::int32_t mipmap_index,
		std::int32_t x_offset, std::int32_t y_offset,
		const void* data, std::int32_t width, std::int32_t height
	)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, format, type, data);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void set() {

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
};

struct gl_texture_cube_array_descriptor
{
	gl_image_format format;
	std::int32_t width;
	std::int32_t mipmaps_count;
	std::int32_t elements_count;

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_image_format _format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		width(_width),
		format(_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_image_format _format) :
		elements_count(_elements_count),
		width(_width),
		format(_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_array_descriptor() = delete;
	gl_texture_cube_array_descriptor(const gl_texture_cube_array_descriptor&) = default;
	gl_texture_cube_array_descriptor& operator=(const gl_texture_cube_array_descriptor&) = default;

	~gl_texture_cube_array_descriptor() = default;
};

class gl_texture_cube_array final : 
	public gl_texture
{
public:

	explicit gl_texture_cube_array(const gl_texture_cube_array_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_CUBE_MAP_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage3D(
			_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.width,
			descriptor.elements_count * 6
		);
	}

	gl_texture_cube_array() = delete;
	gl_texture_cube_array(const gl_texture_cube_array&) = delete;
	gl_texture_cube_array& operator=(const gl_texture_cube_array&) = delete;

	~gl_texture_cube_array() override = default;

	const gl_texture_cube_array_descriptor descriptor;

public:

	void fill(
		std::int32_t element_index,
		gl_cube_face_index face_index,
		std::int32_t mipmap_index,
		std::int32_t x_offset, std::int32_t y_offset,
		const void* data, std::int32_t width, std::int32_t height
	)
	{
		glTexSubImage3D(
			static_cast<GLenum>(face_index),
			mipmap_index, x_offset, y_offset, 0,
			width, height, (element_index + 1) * 6 - 1, 
			static_cast<GLenum>(descriptor.format), type, data
		);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP_ARRAY);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
	}

};
 
struct gl_texture_3d_descriptor
{
	gl_image_format format;
	std::int32_t width, height, depth;
	std::int32_t mipmaps_count;

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_image_format  _format, std::int32_t _mipmaps_count) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(_mipmaps_count),
		format(_format)
	{}

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_image_format _format) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(1),
		format(_format)
	{}

	gl_texture_3d_descriptor() = delete;
	gl_texture_3d_descriptor(const gl_texture_3d_descriptor&) = default;
	gl_texture_3d_descriptor& operator=(const gl_texture_3d_descriptor&) = default;

	~gl_texture_3d_descriptor() = default;
};

class gl_texture_3d final : 
	public gl_texture
{
public:

	explicit gl_texture_3d(const gl_texture_3d_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_3D),
		descriptor(_descriptor)
	{
		glTextureStorage3D(
			_handle,
			descriptor.mipmaps_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height, descriptor.depth
		);
	}

	~gl_texture_3d() override = default;

	const gl_texture_3d_descriptor descriptor;

public:

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const void* data)
	{
		glTextureSubImage3D(
			_handle,
			mipmap_index, x_offset, y_offset, z_offset,
			descriptor.width, descriptor.height, descriptor.depth,
			static_cast<std::uint32_t>(descriptor.format), descriptor.type,
			data
		);
	}

};

struct gl_texture_2d_multisample_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t samples_count;
	bool fixed_sample_location;

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_image_format _format, bool _fixed_sample_location) :
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_image_format _format) :
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_multisample_descriptor() = delete;
	gl_texture_2d_multisample_descriptor(const gl_texture_2d_multisample_descriptor&) = default;
	gl_texture_2d_multisample_descriptor& operator=(const gl_texture_2d_multisample_descriptor&) = default;

	~gl_texture_2d_multisample_descriptor() = default;
};

/*
* The image in this texture (only one image. No mipmapping) is 2-dimensional. 
* Each pixel in these images contains multiple samples instead of just one value.
* You can not transfer pixel from client to server, you can noly download pixels from server to client
*/
class gl_texture_2d_multisample : 
	public gl_texture
{
public:
	explicit gl_texture_2d_multisample(const gl_texture_2d_multisample_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D_MULTISAMPLE),
		descriptor(_descriptor)
	{
		glTextureStorage2DMultisample(_handle,
			descriptor.samples_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height,
			descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_multisample() = delete;
	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	~gl_texture_2d_multisample() override = default;

	const gl_texture_2d_multisample_descriptor descriptor;

};

struct gl_texture_2d_array_multisample_descriptor
{
	gl_image_format format;
	std::int32_t width, height;
	std::int32_t samples_count;
	bool fixed_sample_location;
	std::int32_t elements_count;

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count,
		std::int32_t _samples_count,
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format,
		bool _fixed_sample_location
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count,
		std::int32_t _samples_count,
		std::int32_t _width, std::int32_t _height,
		gl_image_format _format
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		format(_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_array_multisample_descriptor() = delete;
	gl_texture_2d_array_multisample_descriptor(const gl_texture_2d_array_multisample_descriptor&) = default;
	gl_texture_2d_array_multisample_descriptor& operator=(const gl_texture_2d_array_multisample_descriptor&) = default;

	~gl_texture_2d_array_multisample_descriptor() = default;
};

/*
* Combines 2D array and 2D multisample types. No mipmapping.
* 
*/
class gl_texture_2d_multisample_array final : 
	public gl_texture
{
public:

	explicit gl_texture_2d_multisample_array(const gl_texture_2d_array_multisample_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D_MULTISAMPLE_ARRAY),
		descriptor(_descriptor)
	{
		glTextureStorage3DMultisample(_handle,
			descriptor.samples_count,
			static_cast<GLenum>(descriptor.format),
			descriptor.width, descriptor.height,
			descriptor.elements_count,
			descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_multisample_array() = delete;
	gl_texture_2d_multisample_array(const gl_texture_2d_multisample_array&) = delete;
	gl_texture_2d_multisample_array& operator=(const gl_texture_2d_multisample_array&) = delete;

	~gl_texture_2d_multisample_array() override = default;

	const gl_texture_2d_array_multisample_descriptor descriptor;

};

struct gl_texture_buffer_descriptor
{
	gl_image_format format;
	std::int32_t offset, length;
	std::shared_ptr<gl_buffer> buffer;

	gl_texture_buffer_descriptor(gl_image_format _format, std::int32_t _offset, std::int32_t _length, std::shared_ptr<gl_buffer> _buffer) :
		format(_format),
		offset(_offset), length(_length),
		buffer(_buffer)
	{}

	gl_texture_buffer_descriptor() = delete;
	gl_texture_buffer_descriptor(const gl_texture_buffer_descriptor&) = default;
	gl_texture_buffer_descriptor& operator=(const gl_texture_buffer_descriptor&) = default;

	~gl_texture_buffer_descriptor() = default;
};

/*
*
* No mipmapping
*/
class gl_texture_buffer : 
	public gl_texture
{
public:

	gl_texture_buffer() = delete;
	gl_texture_buffer(const gl_texture_buffer_descriptor& _descriptor) :
		gl_texture(gl_texture_type::TEXTURE_BUFFER),
		descriptor(_descriptor)
	{
		glTextureBufferRange(_handle,
			static_cast<GLenum>(descriptor.format),
			descriptor.buffer->get_handle(),
			descriptor.offset, descriptor.length
		);
	}

	gl_texture_buffer(const gl_texture_buffer&) = default;
	gl_texture_buffer& operator=(const gl_texture_buffer&) = default;

	~gl_texture_buffer() override = default;

	const gl_texture_buffer_descriptor descriptor;

};

#endif