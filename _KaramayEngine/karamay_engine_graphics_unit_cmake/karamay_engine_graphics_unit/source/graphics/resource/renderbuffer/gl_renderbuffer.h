#ifndef GL_RENDERBUFFER_H
#define GL_RENDERBUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class gl_renderbuffer_internal_format
{
	R_I8 = GL_R8I,
	R_I16 = GL_R16I,
	R_I32 = GL_R32I,
	RG_I8 = GL_RG8I,
	RG_I16 = GL_RG16I,
	RG_I32 = GL_RG32I,
	RGBA_I8 = GL_RGBA8I,
	RGBA_I16 = GL_RGBA16I,
	RGBA_I32 = GL_RGBA32I,

	R_UI8 = GL_R8UI,
	R_UI16 = GL_R16UI,
	R_UI32 = GL_R32UI,
	RG_UI8 = GL_RG8UI,
	RG_UI16 = GL_RG16UI,
	RG_UI32 = GL_RG32UI,
	RGBA_UI8 = GL_RGBA8UI,
	RGBA_UI16 = GL_RGBA16UI,
	RGBA_UI32 = GL_RGBA32UI,

	R_F32 = GL_R32F,
	RG_F32 = GL_RG32F,
	RGBA_F32 = GL_RGBA32F,

	NOR_R_UI8 = GL_R8,
	NOR_R_UI16 = GL_R16,
	NOR_RG_UI8 = GL_RG8,
	NOR_RG_UI16 = GL_RG16,
	NOR_RGBA_UI8 = GL_RGBA8,
	NOR_RGBA_UI16 = GL_RGBA16,
	NOR_RGBA_UI32_10_10_10_2 = GL_RGB10_A2,

	NOR_UI_SRGB8_ALPHA8 = GL_SRGB8_ALPHA8,

	UI_RGB10_A2 = GL_RGB10_A2UI,
	F_R11_G11_B10 = GL_R11F_G11F_B10F,

	DEPTH_COMPONENT16 = GL_DEPTH_COMPONENT16,
	DEPTH_COMPONENT24 = GL_DEPTH_COMPONENT24,
	DEPTH_COMPONENT32F = GL_DEPTH_COMPONENT32F,
	DPETH24_STENCIL8 = GL_DEPTH24_STENCIL8,
	DPETH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,

	STENCIL_INDEX8 = GL_STENCIL_INDEX8,
};

class gl_renderbuffer final : public gl_object
{
public:
	gl_renderbuffer(int32 width, int32 height, gl_renderbuffer_internal_format internal_format) :
        gl_object(gl_object_type::RENDERBUFFER_OBJ),
        _width(width),
		_height(height),
		_internal_format(internal_format)
	{
		glCreateRenderbuffers(1, &_handle);
        if (width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;
        glNamedRenderbufferStorage(_handle, static_cast<GLenum>(internal_format), width, height);
	}

    gl_renderbuffer(const gl_renderbuffer&) = delete;
    gl_renderbuffer& operator=(const gl_renderbuffer&) = delete;

	~gl_renderbuffer()
    {
        glDeleteRenderbuffers(1, &_handle);
    }

public:

	void bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, _handle);
    }

	void unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

public:

    int32 get_width() const { return _width; }

    int32 get_height() const { return _height; }

    gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }

private:

    int32 _width, _height;

    gl_renderbuffer_internal_format _internal_format;

};

class gl_renderbuffer_multisample final : public gl_object
{
public:
    gl_renderbuffer_multisample(int32 samples_num, int32 width, int32 height, gl_renderbuffer_internal_format internal_format) :
        gl_object(gl_object_type::RENDERBUFFER_OBJ),
        _samples_num(samples_num),
        _width(width),
        _height(height),
        _internal_format(internal_format)
    {
        glCreateRenderbuffers(1, &_handle);
        if (samples_num > GL_MAX_SAMPLES || width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;

        glNamedRenderbufferStorageMultisample(_handle, samples_num, static_cast<GLenum>(internal_format), width, height);
    }

    ~gl_renderbuffer_multisample() override
    {
        glDeleteRenderbuffers(1, &_handle);
    }

public:

    void bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, _handle);
    }

    void unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

private:

    int32 _samples_num;
    int32 _width, _height;
    gl_renderbuffer_internal_format _internal_format;

public:

    [[nodiscard]] std::int32_t get_samples_num() const { return _samples_num; }

    [[nodiscard]] std::int32_t get_width() const { return _width; }

    [[nodiscard]] std::int32_t get_height() const { return _height; }

    [[nodiscard]] gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }

};

#endif

