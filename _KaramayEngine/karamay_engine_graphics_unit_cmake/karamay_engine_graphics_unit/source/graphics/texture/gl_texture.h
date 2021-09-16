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

	inline void bind()
	{
		std::uint32_t unit = 0;
		glBindTextureUnit(GL_TEXTURE0 + unit, _handle);
		_unit = unit;
	}

	inline void unbind()
	{
		glBindTextureUnit(GL_TEXTURE0 + _unit, 0);
	}

protected:

	gl_texture_type _type;

	std::uint32_t _unit;

	static std::unordered_map<gl_texture_type, std::queue<std::uint32_t>> _texture_units;

};

/*
* normalized coordinates, mipmap
* Images in this texture all are 1-dimensional. They have width, but no height or depth.
*/

class gl_texture_1d_base : public gl_texture_base {
public:

	gl_texture_1d_base() : gl_texture_base(gl_texture_type::TEXTURE_1D) {}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_1D, _handle);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
	}

};

template<
	gl_image_format FORMAT,
	std::int32_t BASE_WIDTH,
	std::int32_t MIPMAPS_COUNT = 1
>
class gl_texture_1d final : public gl_texture_1d_base {
public:
	using texture_t = gl_texture_1d<FORMAT, BASE_WIDTH, MIPMAPS_COUNT>;
	using pixels_t	= gl_pixels<FORMAT>;

	//static_assert(_WIDTH < 0, "_WIDTH must > 0");
	//static_assert(_MIPMAPS_COUNT < 1, "_MIPMAPS_COUNT must >= 1");

public:
	gl_texture_1d()
	{
		glTextureStorage1D(_handle,
			MIPMAPS_COUNT,
			static_cast<GLenum>(FORMAT),
            BASE_WIDTH
		);

		_generate_mipmaps();
	}

	gl_texture_1d(const gl_texture_1d&) = delete;
	gl_texture_1d& operator=(const gl_texture_1d&) = delete;
	
	~gl_texture_1d() override = default;

public:

	/*
	* fill whole image which specified by mipmap_index
	* mipmap_index => mipmap(dynamically query size), check size==pixels_count
	* 
	*/
	void fill(std::int32_t mipmap_index, const pixels_t& pixels) noexcept
	{
		// check mipmap_index
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		// check pixels range
		if (mipmap_size(mipmap_index) != pixels.size())
		{
			std::cerr << "pixels count must equal to mipmap size" << std::endl;
			return;
		}

		glTextureSubImage1D(_handle,
			mipmap_index, // level
			0, // offset 
			pixels.size(), // pixels count
			static_cast<GLenum>(pixels.pixel_format()), // pixels format 
			static_cast<GLenum>(pixels.pixel_type()), // pixels type
			pixels.data() // pixels data
		);
	}

	/*
	* fill image region which sepcified by mimap_index and offset
	* 
	*/
	void fill(std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels)
	{
		// check mipmap_index
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		const std::int32_t _mipmap_width = mipmap_size(mipmap_index);
		if (offset < 0 || offset >= _mipmap_width)
		{
			std::cerr << "offset is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (offset < 0 || offset + pixels.size() > _mipmap_width)
		{
			std::cerr << "pixels count does not fit with the specified range" << std::endl;
			return;
		}

		glTextureSubImage1D(_handle,
			mipmap_index, // level
			offset,
			pixels.size(),
			static_cast<GLenum>(pixels.pixel_format()), 
			static_cast<GLenum>(pixels.pixel_type()), 
			pixels.data()
		);
	}

	/*
	* fill image with mask which must be combine with pixels rapidly 
	* 
	*/
	void fill_mask(std::int32_t mipmap_index, const pixels_t& pixels_mask)
	{
		// check mipmap_index
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (mipmap_size(mipmap_index) % pixels_mask.size() != 0)
		{
			std::cerr << "mask pixels count must can be " << std::endl;
			return;
		}

		glClearTexImage(_handle, // tex
			mipmap_index, // level
			static_cast<GLenum>(pixels_mask.pixel_format()), 
			static_cast<GLenum>(pixels_mask.pixel_type()), 
			pixels_mask.data()
		);
	}

	/*
	* fill image region with mask which must be combine with pixels rapidly
	*
	*/
	void fill_mask(std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels_mask)
	{
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (offset < 0 || offset >= mipmap_size(mipmap_index))
		{
			std::cerr << "offset is out of bound [0, mipmaps_count]" << std::endl;
			return;
		}
		if ((mipmap_size(mipmap_index) - offset) % pixels_mask.size() != 0)
		{
			return;
		}
		
		glClearTexSubImage(_handle, // tex
			mipmap_index, // level
			offset, 0, 0, // x/y/z_offset
			pixels_mask.size(), 1, 1, // w/h/d
			static_cast<GLenum>(pixels_mask.pixel_format()),
			static_cast<GLenum>(pixels_mask.pixel_type()),
			pixels_mask.data()
		);
	}

public:

	/*
	* fetch all pixels from the image which specified by mipmap_index
	* 
	*/
	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index)
	{
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmap_index - 1]" << std::endl;
			return nullptr;
		}

		std::shared_ptr<gl_pixels_base> _pixels = std::make_shared<pixels_t>();
		_pixels->resize(mipmap_size(mipmap_index));
		
		glGetTextureImage(_handle,
			mipmap_index, 
			static_cast<GLenum>(_pixels->pixel_format()),
			static_cast<GLenum>(_pixels->pixel_type()),
			_pixels->pixel_size() * _pixels->size(),
			_pixels->data()
		);

		return _pixels;
	}
	
	/*
	* fetch pixels from the range of image which specified by mipmap_index
	*
	*/
	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index, std::int32_t offset, std::int32_t width)
	{
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (offset < 0 || offset + width > mipmap_size(mipmap_index))
		{
			std::cerr << "offset " << std::endl;
			return;
		}

		std::shared_ptr<gl_pixels_base> _pixels = std::make_shared<pixels_t>();
		_pixels->resize(width);

		glGetTextureSubImage(_handle,
			mipmap_index,
			offset, 0, 0,
			width, 1, 1,
			static_cast<GLenum>(_pixels->pixel_format()),
			static_cast<GLenum>(_pixels->pixel_type()),
			_pixels->pixel_size() * _pixels->size(),
			_pixels->data()
		);

		return _pixels;
	}
	

public:

	std::int32_t mipmap_size(std::int32_t mipmap_index = 0)
	{
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT) return -1;
		return _mipmaps_size[mipmap_index];
	}

private:

	std::array<pixels_t, MIPMAPS_COUNT> _mipmaps;

	std::array<std::int32_t, MIPMAPS_COUNT> _mipmaps_size;

private:

	void invalidate(std::int32_t mipmap_index) {}

	void invalidate(std::int32_t mipmap_index, std::int32_t offset, std::int32_t width)
		{
			if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
			{
				std::cerr << "" << std::endl;
				return;
			}

			if (offset < 0 || width < 0 || offset + width > mipmap_size(mipmap_index))
			{
				std::cerr << "" << std::endl;
				return;
			}

			glInvalidateTexSubImage(_handle,
				mipmap_index,
				offset, 0, 0,
				width, 1, 1
			);
		}

	inline void _generate_mipmaps()
	{
		_mipmaps_size[0] = BASE_WIDTH;
		for (std::int32_t _index = 1; _index < MIPMAPS_COUNT; ++_index)
		{
			_mipmaps_size[_index] = _mipmaps_size[_index - 1] / 2;
		}
	}
};

/*
* normalized coordinates, mipmapping, array
*
*/
class gl_texture_1d_array_base : public gl_texture_base {
public:
	gl_texture_1d_array_base() : gl_texture_base(gl_texture_type::TEXTURE_1D_ARRAY) {}

public:

	void generate_mipmaps(std::uint32_t target)
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
		glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	}

};

template<
	std::int32_t ELEMENTS_COUNT,
	gl_image_format FORMAT,
	std::int32_t BASE_WIDTH,
	std::int32_t MIPMAPS_COUNT = 1
>
class gl_texture_1d_array final : public gl_texture_1d_array_base {
public:
	using texture_t = gl_texture_1d_array<ELEMENTS_COUNT, FORMAT, BASE_WIDTH, MIPMAPS_COUNT>;
	using pixels_t = gl_pixels<FORMAT>;

	gl_texture_1d_array()
	{
		glTextureStorage2D(_handle,
			MIPMAPS_COUNT, static_cast<GLenum>(FORMAT),
			BASE_WIDTH,
			ELEMENTS_COUNT
		);
	}

	gl_texture_1d_array(const gl_texture_1d_array&) = default;
	gl_texture_1d_array& operator=(const gl_texture_1d_array&) = default;
	
	~gl_texture_1d_array() override = default;

public:
	/* 
	* element_index [0, elements_count-1]	
	* mipmap_index [0, mipmaps_count-1]
	* 
	*/
	void fill(std::int32_t element_index, std::int32_t mipmap_index, const pixels_t& pixels) noexcept
	{
		if (element_index < 0 || element_index >= ELEMENTS_COUNT)
		{
			std::cerr << "element_index is out of bound [0, elements_count - 1]" << std::endl;
			return;
		}
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		const std::int32_t _mipmap_width = mipmap_size(mipmap_index);
		if (_mipmap_width != pixels.size())
		{
			std::cerr << "" << std::endl;
			return;
		}
		
		glTextureSubImage2D(_handle,
			mipmap_index,
			0, element_index, // x/y_offset
			_mipmap_width, 1, // width, height
			static_cast<GLenum>(pixels.pixel_format()), 
			static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}

	/*
	* element_index [0, elements_count - 1]
	* mipmap_index [0, mipmaps_count - 1]
	* offset [0, elements_count - 1]
	* offset + pixels_count [0, elements_count]
	*/
	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels) noexcept
	{
		if (element_index < 0 || element_index >= ELEMENTS_COUNT)
		{
			std::cerr << "element_index is out of bound [0, elements_count - 1]" << std::endl;
			return;
		}
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap_index is out of bound [0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (offset < 0 || offset >= mipmap_size(mipmap_index))
		{
			std::cerr << "offset is out of bound [0, size - 1]" << std::endl;
			return;
		}
		if (mipmap_size(mipmap_index) != pixels.size())
		{
			std::cerr << "" << std::endl;
			return;
		}

		glTextureSubImage2D(_handle,
			mipmap_index, 
			offset, element_index, // x_offset, y_offset
			pixels.size(), 1, // width, height
			static_cast<GLenum>(pixels.pixel_format()), 
			static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}
	
	/*
	* size % pixels_mask.count() == 0
	* 
	*/
	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index,const pixels_t& pixels_mask) noexcept
	{
		if (element_index < 0 || element_index > ELEMENTS_COUNT - 1)
		{
			std::cerr << "element_index out of bounds[0, elements_count - 1]" << std::endl;
			return;
		}
		if (mipmap_index < 0 || mipmap_index > MIPMAPS_COUNT - 1)
		{
			std::cerr << "mipmap_index out of bounds[0, mipmaps_count - 1]" << std::endl;
			return;
		}
		if (mipmap_size(mipmap_index) % pixels_mask.size() != 0)
		{
			std::cerr << "pixels count does not fit" << std::endl;
			return;
		}

		glClearTexSubImage(_handle,
			mipmap_index,
			0, element_index, 0,
			pixels_mask.size(), 1, 1,
			static_cast<GLenum>(pixels_mask.pixel_format()),
			static_cast<GLenum>(pixels_mask.pixel_type()),
			pixels_mask.data()
		);
	}
	
	/*
	* (size - offset) % pixels_mask.count() == 0
	*  
	*/
	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, const pixels_t& pixels_mask) noexcept
	{
		glClearTexSubImage(_handle,
			mipmap_index,
			offset, element_index, 0,
			pixels_mask.size(), 1, 1,
			static_cast<GLenum>(pixels_mask.pixel_format()),
			static_cast<GLenum>(pixels_mask.pixel_type()),
			pixels_mask.data()
		);
	}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index) noexcept 
	{
		if (element_index < 0 || element_index >= ELEMENTS_COUNT)
		{
			std::cerr << "" << std::endl;
			return;
		}
		if(mipmap_index < 0 || mipmap_index > MIPMAPS_COUNT)
		{
			std::cerr << "" << std::endl;
			return;
		}


		auto _out_pixels = std::make_shared<pixels_t>();

		glGetTextureSubImage(_handle,
			mipmap_index,
			0, element_index, 0,
			mipmap_size(mipmap_index), 1, 1,
			_out_pixels->pixel_format(),
			_out_pixels->pixel_type(),
			_out_pixels->data()
		);
	}

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, std::int32_t width) noexcept 
	{
		if (element_index < 0 || element_index >= ELEMENTS_COUNT)
		{
			std::cerr << "element index out of bound " << std::endl;
			return;
		}
		if (mipmap_index < 0 || mipmap_index >= MIPMAPS_COUNT)
		{
			std::cerr << "mipmap index out of bound " << std::endl;
			return;
		}
		if (offset < 0 || offset + width > mipmap_size(mipmap_index))
		{
			std::cerr << "" << std::endl;
			return;
		}

		auto _pixels = std::make_shared<pixels_t>();

		glGetTextureSubImage(_handle,
			mipmap_index,
			offset, 0, 0,
			width, 1, 1,
			_pixels.pixel_format(),
			_pixels.pixel_type,
			_pixels.size() * _pixels.pixel_size(),
			_pixels.data()
		);

		return _pixels;
	}
	
	void invalidate(std::int32_t element_index, std::int32_t mipmap_index) noexcept {}
	
	void invalidate(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t offset, std::int32_t length) noexcept {}
	
public:

	std::int32_t mipmap_size(std::int32_t mipmap_index)
	{
		return _mipmaps_size[mipmap_index];
	}

private:

    void _generate_mipmaps(){}

    std::array<std::int32_t, MIPMAPS_COUNT> _mipmaps_size;
	

};

////////////////////////////////////////////////////////

/*
*  Images in this texture all are 2-dimensional. They have width and height, but no depth.
*/
class gl_texture_2d_base : public gl_texture_base
{};

template<
	gl_image_format _FORMAT, 
	std::int32_t _WIDTH, 
	std::int32_t _HEIGHT, 
	std::int32_t _MIPMAPS_COUNT = 1
>
class gl_texture_2d final : 
	public gl_texture_2d_base
{
public:
	using texture_t = gl_texture_2d<_FORMAT, _WIDTH, _HEIGHT, _MIPMAPS_COUNT>;
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_2d()
	{
		glTextureStorage2D(_handle,
			_MIPMAPS_COUNT,
			static_cast<std::uint32_t>(_FORMAT),
			_WIDTH, _HEIGHT
		);
	}

	~gl_texture_2d() override = default;

public:

	void fill(std::int32_t mipmap_index, const pixels_t& pixels)
	{
		if (mipmap_index < 0 || mipmap_index >= _MIPMAPS_COUNT)
		{
			return;
		}

		glTextureSubImage2D(_handle, 
			0, 
			0, 0,
			_WIDTH, _HEIGHT, 
			static_cast<GLenum>(pixels->pixel_format()), 
			static_cast<GLenum>(pixels->pixel_type()), 
			pixels->data()
		);
	}

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{

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

public:

	std::pair<std::int32_t, std::int32_t> mipmap_size(std::int32_t mipmap_index = 0)
	{
		return _mipmaps_size[mipmap_index];
	}

private:

	std::array<std::pair<std::int32_t, std::int32_t>, _MIPMAPS_COUNT> _mipmaps_size;

};

class gl_texture_2d_array_base : public gl_texture_base
{};

template<
	std::int32_t _ELEMENTS_COUNT,
	gl_image_format _FORMAT, 
	std::int32_t _WIDTH, 
	std::int32_t _HEIGHT, 
	std::int32_t _MIPMAPS_COUNT
>
class gl_texture_2d_array final : public gl_texture_2d_array_base
{
public:
    using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_2d_array()
	{
		glTextureStorage3D(_handle,
			_MIPMAPS_COUNT, static_cast<GLenum>(_FORMAT),
			_WIDTH, _HEIGHT,
			_ELEMENTS_COUNT
		);
	}
	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array() override = default;

public:

	void fill(std::int32_t element_index, const pixels_t& pixels)
	{
		glTextureSubImage3D(_handle,
			0,
			0, 0, element_index,
			pixels.size(), 1, 1,
			static_cast<GLenum>(pixels->pixel_format()),
			static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY,
			mipmap_index, x_offset, y_offset,
			element_index, 2, 2, 1,
			static_cast<GLenum>(pixels->pixel_format()), static_cast<GLenum>(pixels->pixel_type()),
			pixels->data()
		);
	}

	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index)
	{}

	void fill_mask(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset){}

public:

    std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index){}

    std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t length){}

public:

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

};

class gl_texture_rectangle_base : public gl_texture_base
{};

template<
	gl_image_format _FORMAT, 
	std::int32_t _WIDTH,
	std::int32_t _HEIGHT
>
class gl_texture_rectangle final : public gl_texture_rectangle_base
{
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_rectangle()
	{
		glTextureStorage2D(_handle,
			1,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _HEIGHT
		);
	}
	gl_texture_rectangle& operator=(const gl_texture_rectangle&) = delete;
	~gl_texture_rectangle() override = default;

public:

	void fill(const pixels_t& pixels) {}

	void fill(std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{
		glTextureSubImage2D(_handle, 
			0, 
			x_offset, y_offset, 
			pixels.size(), 1, 
			pixels.pixel_format(), pixels.pixel_type(),
			pixels.data()
		);
	}

	void fill_mask(const pixels_t& pixels_mask) {}

	void fill_mask(std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels) {}

public:

	std::shared_ptr<pixels_t> fetch() {}

	std::shared_ptr<pixels_t> fetch(std::int32_t x_offset, std::int32_t y_offset, std::int32_t length) {}

};

class gl_texture_cube_base : public gl_texture_base {
public:
    gl_texture_cube_base() : gl_texture_base(gl_texture_type::TEXTURE_CUBE_MAP){}
};

template<
	gl_image_format _FORMAT,
	std::int32_t _WIDTH,
	std::int32_t _MIPMAPS_COUNT = 1
>
class gl_texture_cube final : public gl_texture_cube_base
{
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_cube()
	{
		glTextureStorage3D(_handle,
			_MIPMAPS_COUNT,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _WIDTH, 6
		);
	}

	gl_texture_cube(const gl_texture_cube&) = delete;
	gl_texture_cube& operator=(const gl_texture_cube&) = delete;

	~gl_texture_cube() override = default;

public:

	void fill(gl_cube_face_index face_index, std::int32_t mipmap_index, const pixels_t& pixels)
	{}

	void fill(gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, format, type, data);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void fill_mask(gl_cube_face_index face_index, std::int32_t mipmap_index, const pixels_t& pixels_mask) {}

	void fill_mask(gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels_mask) {}

public:

    std::shared_ptr<pixels_t> fetch(gl_cube_face_index face_index, std::int32_t mipmap_index){}

    std::shared_ptr<pixels_t> fetch(gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t length)
    {}

public:

	const std::pair<std::int32_t, std::int32_t>& mipmap_size(std::int32_t mipmap_index)
	{
		return _mipmaps_size[mipmap_index];
	}

private:

	std::array<std::pair<std::int32_t, std::int32_t>, _MIPMAPS_COUNT> _mipmaps_size;

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

void test1()
{
    gl_texture_cube<gl_image_format::F_RGBA32, 1024> _skybox;
    decltype(_skybox)::pixels_t _pixels;
    _pixels.add({1.0f, 16.0f, 17.998f, 0.982f});
    _skybox.fill(gl_cube_face_index::NEGATIVE_X, 0, 0, 0, _pixels);
    _skybox.fill(gl_cube_face_index::POSITIVE_X, 0, _pixels);

}

class gl_texture_cube_array_base : public gl_texture_base {
public:
    gl_texture_cube_array_base() : gl_texture_base(gl_texture_type::TEXTURE_CUBE_MAP_ARRAY){}
};

template<
	std::int32_t _ELEMENTS_COUNT,
	gl_image_format _FORMAT,
	std::int32_t _WIDTH,
	std::int32_t _MIPMAPS_COUNT = 1
>
class gl_texture_cube_array final : gl_texture_cube_array_base
{
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_cube_array()
	{
		glTextureStorage3D(
			_handle,
			_MIPMAPS_COUNT,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _WIDTH,
			_ELEMENTS_COUNT * 6
		);
	}
	gl_texture_cube_array(const gl_texture_cube_array&) = delete;
	gl_texture_cube_array& operator=(const gl_texture_cube_array&) = delete;

	~gl_texture_cube_array() override = default;

public:

	void fill(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index, const pixels_t& pixels)
	{}

	void fill(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels)
	{
		glTexSubImage3D(
			static_cast<GLenum>(face_index),
			mipmap_index, 
			x_offset, y_offset, 0,
			pixels.size(), 1, (element_index + 1) * 6 - 1,
			static_cast<GLenum>(pixels.pixel_format()), 
			static_cast<GLenum>(pixels.pixel_type()), 
			pixels.data()
		);
	}

	void fill_mask(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index, const pixels_t& pixels_mask) {}

	void fill_mask(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels_mask) {}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index) {}

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t length) {}

public:

	std::pair<std::int32_t, std::int32_t> mipmap_size(std::int32_t mipmap_index)
	{
		return _mipmaps_size[mipmap_index];
	}

private:

	std::array<std::pair<std::int32_t, std::int32_t>, _MIPMAPS_COUNT> _mipmaps_size;

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP_ARRAY);
		glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);
	}

};

class gl_texture_3d_base : public gl_texture_base {};

template<
	gl_image_format _FORMAT,
	std::int32_t _WIDTH,
	std::int32_t _HEIGHT,
	std::int32_t _DEPTH,
	std::int32_t _MIPMAPS_COUNT
>
class gl_texture_3d final : public gl_texture_3d_base
{
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_3d()
	{
		glTextureStorage3D(_handle,
			_MIPMAPS_COUNT,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _HEIGHT, _DEPTH
		);
	}
	~gl_texture_3d() override = default;

public:

	void fill(std::int32_t mipmap_index, const pixels_t& pixels)
	{
	    if(mipmap_index < 0 || mipmap_index >= _MIPMAPS_COUNT) {}

	    glTextureSubImage3D(_handle,
                            mipmap_index,
                            0, 0, 0,
                            pixels.size(), 1, 1,
                            static_cast<GLenum>(pixels.pixel_format()),
                            static_cast<GLenum>(pixels.pixel_type()),
                            pixels.data()
                            );
	}

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const pixels_t& pixels)
	{
		glTextureSubImage3D(
			_handle,
			mipmap_index, x_offset, y_offset, z_offset,
			pixels.size(), 1, 1,
			static_cast<GLenum>(pixels.pixel_format()),
			static_cast<GLenum>(pixels.pixel_type()),
            pixels.data()
		);
	}

	void fill_mask(std::int32_t mipmap_index, const pixels_t& pixels_mask) {}

	void fill_mask(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const pixels_t& pixels_mask) {}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index) {}

	std::shared_ptr<pixels_t> fetch(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, std::int32_t length) {}


public:

	[[nodiscard]] const std::tuple<std::int32_t, std::int32_t, std::int32_t>& mipmap_size(std::int32_t mipmap_index) const
	{
		return _mipmaps_size[mipmap_index];
	}

private:

	std::array<std::tuple<std::int32_t, std::int32_t, std::int32_t>, _MIPMAPS_COUNT> _mipmaps_size;

};

class gl_texture_2d_multisample_base : public gl_texture_base {
public:
    gl_texture_2d_multisample_base() : gl_texture_base(gl_texture_type::TEXTURE_2D_MULTISAMPLE)
    {}
};

/*
* The image in this texture (No mipmapping) is 2-dimensional. 
* Each pixel in these images contains multiple samples instead of just one value.
* You can not transfer pixel from client to server, you can noly download pixels from server to client
*/
template<
	gl_image_format _FORMAT,
	std::int32_t _WIDTH,
	std::int32_t _HEIGHT,
	std::int32_t _SAMPLES_COUNT,
	bool _FIXED_SAMPLE_LOCATION
>
class gl_texture_2d_multisample final: public gl_texture_2d_multisample_base
{
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_2d_multisample()
	{
		glTextureStorage2DMultisample(_handle,
			_SAMPLES_COUNT,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _HEIGHT,
			_FIXED_SAMPLE_LOCATION
		);
	}

	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	~gl_texture_2d_multisample() override = default;

public:

	void fill(const pixels_t& pixels) {}

	void fill(std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels) {}

	void fill_mask(const pixels_t& pixels_mask) {}

	void fill_mask(std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels) {}

public:

	std::shared_ptr<pixels_t> fetch() 
	{
		auto _pixels = std::make_shared<pixels_t>();
		auto* _pixels_ptr = dynamic_cast<gl_pixels_base*>(_pixels.get());

		if (_pixels_ptr)
		{
            _pixels_ptr->resize(_WIDTH * _HEIGHT);

            glGetTextureImage(_handle,
				0,
				_pixels_ptr->pixel_format(),
				_pixels_ptr->pixel_type(),
				_pixels_ptr->size() * _pixels->pixel_size(),
				_pixels_ptr->data()
			);
		}

		return _pixels;
	}

	std::shared_ptr<pixels_t> fetch(std::int32_t x_offset, std::int32_t y_offset, std::int32_t length)
	{
		std::shared_ptr<gl_pixels_base> _pixels = std::make_shared<pixels_t>();
		_pixels->resize(length);

		if (_pixels)
		{
			glGetTextureSubImage(_handle,
				0,
				x_offset, y_offset, 0,
				length, 1, 1,
				_pixels->pixel_format(),
				_pixels->pixel_type(),
				_pixels->size() * _pixels->pixel_size(),
				_pixels->data()
			);
		}

		return _pixels;
	}
};

/*
* Combines 2D array and 2D multisample types. No mipmapping.
* 
*/

class gl_texture_2d_multisample_array_base : public gl_texture_base {
public:
    gl_texture_2d_multisample_array_base() : gl_texture_base(gl_texture_type::TEXTURE_2D_MULTISAMPLE_ARRAY) {}

};

template<
	std::int32_t _ELEMENTS_COUNT,
	gl_image_format _FORMAT,
	std::int32_t _WIDTH,
	std::int32_t _HEIGHT,
	std::int32_t _SAMPLES_COUNT,
	bool _FIXED_SAMPLE_LOCATION
>
class gl_texture_2d_multisample_array final : public gl_texture_2d_multisample_array_base {
public:
	using pixels_t = gl_pixels<_FORMAT>;

	gl_texture_2d_multisample_array()
	{
		glTextureStorage3DMultisample(_handle,
			_SAMPLES_COUNT,
			static_cast<GLenum>(_FORMAT),
			_WIDTH, _HEIGHT,
			_ELEMENTS_COUNT,
			_FIXED_SAMPLE_LOCATION
		);
	}

	gl_texture_2d_multisample_array(const gl_texture_2d_multisample_array&) = delete;
	gl_texture_2d_multisample_array& operator=(const gl_texture_2d_multisample_array&) = delete;

	~gl_texture_2d_multisample_array() override = default;

public:

	void fill(std::int32_t element_index, const pixels_t& pixels) noexcept
	{
		glTextureSubImage3D(_handle,
			0,
			0, 0, element_index,
			pixels.size(), 1, 1,
			static_cast<GLenum>(pixels.pixel_format()),
			static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}

	void fill(std::int32_t element_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels) noexcept
	{
		glTextureSubImage3D(_handle,
			0,
			x_offset, y_offset, element_index,
			pixels.size(), 1, 1,
			static_cast<GLenum>(pixels.pixel_format()),
			static_cast<GLenum>(pixels.pixel_type()),
			pixels.data()
		);
	}

	void fill_mask(std::int32_t element_index, const pixels_t& pixels_mask)
	{
	    if(element_index < 0 || element_index >= _ELEMENTS_COUNT) return;

	}

	void fill_mask(std::int32_t element_index, std::int32_t x_offset, std::int32_t y_offset, const pixels_t& pixels_mask) {}

public:

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index) {}

	std::shared_ptr<pixels_t> fetch(std::int32_t element_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t length) {}


};


class gl_texture_buffer_base : public gl_texture_base{
public:
    gl_texture_buffer_base() : gl_texture_base(gl_texture_type::TEXTURE_BUFFER)
    {}
};

/*
 *
 * No more mipmaps
 *
 *
 */
template<gl_image_format _FORMAT>
class gl_texture_buffer final: public gl_texture_buffer_base{
public:

	gl_texture_buffer() = default;

	gl_texture_buffer(const gl_texture_buffer&) = default;

	gl_texture_buffer& operator=(const gl_texture_buffer&) = default;

	~gl_texture_buffer() override = default;

public:

    /*
     * try to associate with a buffer
     *
     */
	void associate(const std::shared_ptr<gl_buffer>& buffer) noexcept
	{
		if (!buffer) return;

        glTextureBuffer(_handle,
                        static_cast<GLenum>(_FORMAT),
                        buffer->get_handle()
        );

        _associated_buffer = buffer;
	}

    /*
     * try to associate with a range of buffer
     *
     */
	void associate(const std::shared_ptr<gl_buffer>& buffer, std::int32_t offset, std::int32_t length) noexcept
	{
		if (!buffer) return;
		if (offset < 0 || offset >= buffer->get_capacity() || length < 0 || offset + length > buffer->get_capacity()) return;

        glTextureBufferRange(_handle,
                             static_cast<GLenum>(_FORMAT),
                             buffer->get_handle(),
                             offset, length
                             );

        _associated_buffer = buffer;
	}

	/*
	 * get the buffer has been associated to this texture
	 *
	 */
    [[nodiscard]] std::shared_ptr<gl_buffer> associated_buffer() const
    {
	    if(!_associated_buffer)
	        return nullptr;
	    return _associated_buffer;
    }

private:

	std::shared_ptr<gl_buffer> _associated_buffer;

};

#endif