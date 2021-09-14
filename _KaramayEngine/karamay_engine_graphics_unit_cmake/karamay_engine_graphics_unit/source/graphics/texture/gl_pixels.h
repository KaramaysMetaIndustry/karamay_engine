
#include "public/_glew.h"

enum class gl_image_format : GLenum
{
	NOR_UI_R8 = GL_R8,
	NOR_UI_R16 = GL_R16,
	NOR_UI_RG8 = GL_RG8,
	NOR_UI_RG16 = GL_RG16,
	NOR_UI_RGB8 = GL_RGB8,
	NOR_UI_RGB16 = GL_RGB16,
	NOR_UI_RGBA8 = GL_RGBA8,
	NOR_UI_RGBA16 = GL_RGBA16,

	NOR_I_R8 = GL_R8_SNORM,
	NOR_I_R16 = GL_R16_SNORM,
	NOR_I_RG8 = GL_RG8_SNORM,
	NOR_I_RG16 = GL_RG16_SNORM,
	NOR_I_RGB8 = GL_RGB8_SNORM,
	NOR_I_RGB16 = GL_RGB16_SNORM,
	NOR_I_RGBA8 = GL_RGBA8_SNORM,
	NOR_I_RGBA16 = GL_RGBA16_SNORM,

	F_R16 = GL_R16F,
	F_RG16 = GL_RG16F,
	F_RGB16 = GL_RGB16F,
	F_RGBA16 = GL_RGBA16F,
	F_R32 = GL_R32F,
	F_RG32 = GL_RG32F,
	F_RGB32 = GL_RGB32F,
	F_RGBA32 = GL_RGBA32F,

	I_R8 = GL_R8I,
	I_R16 = GL_R16I,
	I_R32 = GL_R32I,
	I_RG8 = GL_RG8I,
	I_RG16 = GL_RG16I,
	I_RG32 = GL_RG32I,
	I_RGB8 = GL_RGB8I,
	I_RGB16 = GL_RGB16I,
	I_RGB32 = GL_RGB32I,
	I_RGBA8 = GL_RGBA8I,
	I_RGBA16 = GL_RGBA16I,
	I_RGBA32 = GL_RGBA32I,

	UI_R8 = GL_R8UI,
	UI_R16 = GL_R16UI,
	UI_R32 = GL_R32UI,
	UI_RG8 = GL_RG8UI,
	UI_RG16 = GL_RG16UI,
	UI_RG32 = GL_RG32UI,
	UI_RGB8 = GL_RGB8UI,
	UI_RGB16 = GL_RGB16UI,
	UI_RGB32 = GL_RGB32UI,
	UI_RGBA8 = GL_RGBA8UI,
	UI_RGBA16 = GL_RGBA16UI,
	UI_RGBA32 = GL_RGBA32UI,

	NOR_UI_R3_G3_B2 = GL_R3_G3_B2,
	//NOR_UI_RGB4 = GL_RGB4,
	//NOR_UI_RGB5 = GL_RGB5,
	NOR_UI_R5_G6_B5 = GL_RGB565,
	//NOR_UI_RGB10 = GL_RGB10,
	//NOR_UI_RGB12 = GL_RGB12,
	NOR_UI_RGBA2 = GL_RGBA2,
	NOR_UI_RGBA4 = GL_RGBA4,
	NOR_UI_RGB5_A1 = GL_RGB5_A1,
	NOR_UI_RGB10_A2 = GL_RGB10_A2,
	//NOR_UI_RGBA12 = GL_RGBA12,
	NOR_UI_SRGB8 = GL_SRGB8,
	NOR_UI_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,
	UI_RGB10_A2 = GL_RGB10_A2UI,
	F_R11_G11_B10 = GL_R11F_G11F_B10F,
	RGB9_E5 = GL_RGB9_E5,

	// base format
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	DEPTH_STENCIL = GL_DEPTH_STENCIL,
	/*r = GL_RED,
	rg = GL_RG,
	rgb = GL_RGB,
	rgba = GL_RGBA,*/

	// compressed format
	COMPRESSED_R = GL_COMPRESSED_RED,
	COMPRESSED_RG = GL_COMPRESSED_RG,
	COMPRESSED_RGB = GL_COMPRESSED_RGB,
	COMPRESSED_RGBA = GL_COMPRESSED_RGBA,
	COMPRESSED_SRGB = GL_COMPRESSED_SRGB,
	COMPRESSED_SRGB_ALPHA = GL_COMPRESSED_SRGB_ALPHA,
};

enum class gl_pixel_format : GLenum
{
	R = GL_RED,
	RG = GL_RG,
	RGB = GL_RGB,
	RGBA = GL_RGBA,
	BGR = GL_BGR,
	BGRA = GL_BGRA,

	R_INTEGER = GL_RED_INTEGER,
	RG_INTEGER = GL_RG_INTEGER,
	RGB_INTEGER = GL_RGB_INTEGER,
	RGBA_INTEGER = GL_RGBA_INTEGER,
	BGR_INTEGER = GL_BGR_INTEGER,
	BGRA_INTEGER = GL_BGRA_INTEGER,

	DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
	STENCIL_INDEX = GL_STENCIL_INDEX,
	DEPTH_STENCIL = GL_DEPTH_STENCIL
};

enum class gl_pixel_type : GLenum
{
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	UNSIGNED_INT = GL_UNSIGNED_INT,
	BYTE = GL_BYTE,
	SHORT = GL_SHORT,
	INT = GL_INT,

	HALF_FLOAT = GL_HALF_FLOAT,
	FLOAT = GL_FLOAT,

	UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2, // RGB
	UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV, // RGB
	UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5, // RGB
	UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV, //RGB

	UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1, // RGBA RGBA_INTEGER
	UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV, // RGBA RGBA_INTEGER

	UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8, // RGBA RGBA_INTEGER
	UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV, //RGBA RGBA_INTEGER
	UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2, // RGBA RGBA_INTEGER
	UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV, //RGBA RGBA_INTEGER

	UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
	UNSIGNED_INT_5_9_9_9_REV = GL_UNSIGNED_INT_5_9_9_9_REV, // GL_RGB GL_RGB9_E5

	UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8, // DEPTH_STENCIL

	FLOAT_32_UNSIGNED_INT_24_8_REV = GL_FLOAT_32_UNSIGNED_INT_24_8_REV //  GL_DEPTH32F_STENCIL8
};


class gl_pixels_base
{
public:
	virtual gl_image_format internal_format() const = 0;
	virtual gl_pixel_format pixel_format() const = 0;
	virtual gl_pixel_type pixel_type() const = 0;
	virtual std::uint32_t pixel_size() const = 0;
	virtual std::uint32_t size() const = 0;
	virtual void resize(std::uint32_t new_size) = 0;
	virtual std::uint8_t* data() = 0;
	virtual const std::uint8_t* data() const = 0;
};

template<gl_image_format format>
class gl_pixels : private gl_pixels_base
{
	gl_image_format internal_format() const override {};
	gl_pixel_format pixel_format() const override {};
	gl_pixel_type pixel_type() const override {};
	std::uint32_t pixel_size() const override {};
	std::uint32_t size() const override {};
	void resize(std::uint32_t new_size) override {};
	std::uint8_t* data() override {};
	const std::uint8_t* data() const override {};
};

template<>
class gl_pixels<gl_image_format::NOR_UI_R8> final : public gl_pixels_base
{
public:
	using pixel_t = std::uint8_t;
	using client_pixel_t = pixel_t;

	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_R8; }
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(pixel_t); }
	std::uint32_t size() const override { return _pixels.size(); }
	void resize(std::uint32_t new_size) override { _pixels.resize(new_size); }
	std::uint8_t* data() override{ return _pixels.data(); }
	const std::uint8_t* data()  const override{ return _pixels.data(); }

public:

	void add(client_pixel_t pixel)
	{
		_pixels.push_back(pixel);
	}

	void set(std::uint32_t index, client_pixel_t new_pixel) 
	{
		_pixels.at(index) = new_pixel;
	}

	client_pixel_t get(std::uint32_t index) 
	{
		return _pixels.at(index);
	}

private:

	std::vector<pixel_t> _pixels;

};

template<>
class gl_pixels<gl_image_format::NOR_UI_R16> final : private gl_pixels_base
{
public:
	using pixel_t = std::uint16_t;
	using client_pixel_t = pixel_t;

	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_R16; }
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	std::uint32_t size() const override { return _pixels.size(); }
	void resize(std::uint32_t new_size) override { _pixels.resize(new_size); }
	std::uint8_t* data() override { return reinterpret_cast<std::uint8_t*>(_pixels.data()); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

public:

	void add(std::uint16_t r) {}

	void set(std::uint32_t index, client_pixel_t) {}

	client_pixel_t get(std::uint32_t index) {}

private:

	std::vector<std::uint16_t> _pixels;

};

template<>
class gl_pixels<gl_image_format::NOR_UI_RG8> final : private gl_pixels_base
{
public:

	using pixel_t = glm::u8vec2;
	using client_pixel_t = pixel_t;

private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(pixel_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RG8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<pixel_t> _pixels;

public:

	void add(client_pixel_t client_pixel)
	{

	}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_RG16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec2); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RG16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u16vec2> _pixels;

public:

	void add(std::uint16_t r, std::uint16_t g) {}
};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGB8> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec3); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGB8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u8vec3> _pixels;

public:

	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b) {}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGB16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec3); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGB16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u16vec3> _pixels;

public:

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b) {}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGBA8> final : private gl_pixels_base
{
private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec4); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGBA8; }
	std::uint32_t count() const override { _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u8vec4> _pixels;

public:

	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {}
};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGBA16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec4); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGBA16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u16vec4> _pixels;

public:

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b, std::uint16_t a) {}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_R3_G3_B2> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE_3_3_2; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint8_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_R3_G3_B2; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint8_t> _pixels;

public:

	void add(std::uint8_t r, std::uint8_t g, std::uint8_t b)
	{}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_R5_G6_B5> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT_5_6_5; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { gl_image_format::NOR_UI_R5_G6_B5; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint16_t> _pixels;

public:

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b) {}
};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGB5_A1> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT_5_5_5_1; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGB5_A1; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint16_t> _pixels;

public:

	void add(std::uint16_t r, std::uint16_t g, std::uint16_t b, std::uint16_t a)
	{

	}

};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGB10_A2> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_INT_10_10_10_2; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint32_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGB10_A2; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint32_t> _pixels;

public:
	void add(std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a)
	{}
};

//template<>
//class gl_pixels<gl_image_format::NOR_UI_RGBA2> final : private gl_pixels_base
//{
//	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
//	gl_pixel_type pixel_type() const override {}
//	std::uint32_t pixel_size() const override {}
//	gl_image_format internal_format() const override {}
//	std::uint32_t count() const override {}
//	const std::uint8_t* data() const override {}
//};

template<>
class gl_pixels<gl_image_format::NOR_UI_RGBA4> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT_4_4_4_4; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_UI_RGBA4; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }


	std::vector<std::uint16_t> _pixels;

public:
	void add(const glm::u16vec4& pixel) {}

};


template<>
class gl_pixels<gl_image_format::NOR_I_R8> final : private gl_pixels_base
{
private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint8_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_R8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }
	std::uint8_t* data() override { return reinterpret_cast<std::uint8_t*>(_pixels.data()); }
	void resize(std::size_t new_size) override { _pixels.resize(new_size); }

	std::vector<std::int8_t> _pixels;

public:

	void add(std::int8_t r) {}
};

template<>
class gl_pixels<gl_image_format::NOR_I_R16> final : private gl_pixels_base
{
private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_R16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::int16_t> _pixels;

public:

	void add(std::int16_t r) {}

};

template<>
class gl_pixels<gl_image_format::NOR_I_RG8> final : private gl_pixels_base
{
private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec2); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RG8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i8vec2> _pixels;

public:

	void add(std::int8_t r, std::int8_t g) {}

};

template<>
class gl_pixels<gl_image_format::NOR_I_RG16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec2); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RG16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i16vec2> _pixels;

public:

	void add(std::int16_t r, std::int16_t g) {}
};

template<>
class gl_pixels<gl_image_format::NOR_I_RGB8> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec3); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RGB8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i8vec3> _pixels;

public:

	void add(std::int8_t r, std::uint8_t g, std::int8_t b) {}

};

template<>
class gl_pixels<gl_image_format::NOR_I_RGB16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec3); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RGB16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i16vec3> _pixels;

public:

	void add(std::int16_t r, std::int16_t g, std::int16_t b) {}

};

template<>
class gl_pixels<gl_image_format::NOR_I_RGBA8> final : private gl_pixels_base
{
private:
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec4); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RGBA8; }
	std::uint32_t count() const override { _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i8vec4> _pixels;

public:

	void add(std::int8_t r, std::int8_t g, std::int8_t b, std::int8_t a) {}
};

template<>
class gl_pixels<gl_image_format::NOR_I_RGBA16> final : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u16vec4); }
	gl_image_format internal_format() const override { return gl_image_format::NOR_I_RGBA16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::i16vec4> _pixels;

public:

	void add(std::int16_t r, std::int16_t g, std::int16_t b, std::int16_t a) {}

};




//template<>
//class gl_pixels<gl_image_format::NOR_UI_SRGB8> : private gl_pixels_base
//{
//	gl_pixel_format pixel_format() const override {}
//	gl_pixel_type pixel_type() const override {}
//	std::uint32_t pixel_size() const override {}
//	gl_image_format internal_format() const override {}
//	std::uint32_t count() const override {}
//	const std::uint8_t* data() const override {}
//};
//
//template<>
//class gl_pixels<gl_image_format::NOR_UI_SRGB8> : private gl_pixels_base
//{
//	gl_pixel_format pixel_format() const override {}
//	gl_pixel_type pixel_type() const override {}
//	std::uint32_t pixel_size() const override {}
//	gl_image_format internal_format() const override {}
//	std::uint32_t count() const override {}
//	const std::uint8_t* data() const override {}
//};
//
//template<>
//class gl_pixels<gl_image_format::NOR_UI_SRGB8_ALPHA8> : private gl_pixels_base
//{
//	gl_pixel_format pixel_format() const override {}
//	gl_pixel_type pixel_type() const override {}
//	std::uint32_t pixel_size() const override {}
//	gl_image_format internal_format() const override {}
//	std::uint32_t count() const override {}
//	const std::uint8_t* data() const override {}
//};


template<>
class gl_pixels<gl_image_format::UI_R8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint8_t); }
	gl_image_format internal_format() const override { return gl_image_format::UI_R8; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint8_t> _pixels;

public:

	void add(std::uint8_t r) {}
};

template<>
class gl_pixels<gl_image_format::UI_R16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { return gl_image_format::UI_R16; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { reinterpret_cast<std::uint16_t>(_pixels.data()); }

	std::vector<std::uint16_t> _pixels;

public:

	void add(std::uint16_t r) {}

};

template<>
class gl_pixels<gl_image_format::UI_R32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_INT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint32_t); }
	gl_image_format internal_format() const override { return gl_image_format::UI_R32; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::uint32_t> _pixels;

public:

	void add(std::uint32_t r) {}

};

template<>
class gl_pixels<gl_image_format::UI_RG8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_BYTE; }
	std::uint32_t pixel_size() const override { return sizeof(glm::u8vec2); }
	gl_image_format internal_format() const override { return gl_image_format::UI_RG8; }
	std::uint32_t count() const override { _pixels.size(); }
	const std::uint8_t* data() const override { reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u8vec2> _pixels;

public:

	void add(std::uint8_t r, std::uint8_t g) {}

};

template<>
class gl_pixels<gl_image_format::UI_RG16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_SHORT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint16_t); }
	gl_image_format internal_format() const override { return gl_image_format::UI_RG16; }
	std::uint32_t count() const override { _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::u16vec2> _pixels;

public:

	void add() {}
};

template<>
class gl_pixels<gl_image_format::UI_RG32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::UNSIGNED_INT; }
	std::uint32_t pixel_size() const override { return sizeof(std::uint32_t); }
	gl_image_format internal_format() const override { return gl_image_format::UI_RG32; }
	std::uint32_t count() const override { _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::uvec2> _pixels;

public:

	void add(std::uint32_t r, std::uint32_t g) {}
};

template<>
class gl_pixels<gl_image_format::UI_RGB8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::UI_RGB16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::UI_RGB32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::UI_RGBA8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::UI_RGBA16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::UI_RGBA32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_R8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_R16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_R32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RG8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RG16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RG32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGB8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGB16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGB32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGBA8> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGBA16> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};

template<>
class gl_pixels<gl_image_format::I_RGBA32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override {}
	gl_pixel_type pixel_type() const override {}
	std::uint32_t pixel_size() const override {}
	gl_image_format internal_format() const override {}
	std::uint32_t count() const override {}
	const std::uint8_t* data() const override {}
};



template<>
class gl_pixels<gl_image_format::F_R32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { gl_pixel_format::R; }
	gl_pixel_type pixel_type() const override { gl_pixel_type::FLOAT; }
	std::uint32_t pixel_size() const override { sizeof(std::float_t); }
	gl_image_format internal_format() const override { gl_image_format::F_R32; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<std::float_t> _pixels;

public:

	void add(std::float_t r) {}

};

template<>
class gl_pixels<gl_image_format::F_RG32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { gl_pixel_format::RG; }
	gl_pixel_type pixel_type() const override { gl_pixel_type::FLOAT; }
	std::uint32_t pixel_size() const override { sizeof(glm::vec2); }
	gl_image_format internal_format() const override { gl_image_format::F_RG32; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::vec2> _pixels;

public:

	void add(std::float_t r, std::float_t g) {}
};

template<>
class gl_pixels<gl_image_format::F_RGB32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { gl_pixel_format::RGB; }
	gl_pixel_type pixel_type() const override { gl_pixel_type::FLOAT; }
	std::uint32_t pixel_size() const override { sizeof(glm::vec3); }
	gl_image_format internal_format() const override { gl_image_format::F_RGB32; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::vec3> _pixels;

public:
	void add(std::float_t r, std::float_t g, std::float_t b) {}
};

template<>
class gl_pixels<gl_image_format::F_RGBA32> : private gl_pixels_base
{
	gl_pixel_format pixel_format() const override { return gl_pixel_format::RGBA; }
	gl_pixel_type pixel_type() const override { return gl_pixel_type::FLOAT; }
	std::uint32_t pixel_size() const override { return sizeof(glm::vec4); }
	gl_image_format internal_format() const override { return gl_image_format::F_RGBA32; }
	std::uint32_t count() const override { return _pixels.size(); }
	const std::uint8_t* data() const override { return reinterpret_cast<const std::uint8_t*>(_pixels.data()); }

	std::vector<glm::vec4> _pixels;

public:

	void add(const glm::vec4& pixel) {}

};