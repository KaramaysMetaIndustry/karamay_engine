#ifndef GL_RENDERBUFFER_H
#define GL_RENDERBUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class gl_renderbuffer_internal_format
{
    NONE,
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

	~gl_renderbuffer() override
    {
        glDeleteRenderbuffers(1, &_handle);
    }


public:

    int32 get_width() const { return _width; }

    int32 get_height() const { return _height; }

    gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }

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

    int32 _width, _height;

    gl_renderbuffer_internal_format _internal_format;

};

class gl_renderbuffer_multisample final : public gl_object
{
public:
    gl_renderbuffer_multisample(int32 samples_count, int32 width, int32 height, gl_renderbuffer_internal_format internal_format) :
        gl_object(gl_object_type::RENDERBUFFER_OBJ),
        _samples_count(samples_count),
        _width(width),
        _height(height),
        _internal_format(internal_format)
    {
        glCreateRenderbuffers(1, &_handle);
        if (samples_count > GL_MAX_SAMPLES || width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;

        glNamedRenderbufferStorageMultisample(_handle, samples_count, static_cast<GLenum>(internal_format), width, height);
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

    int32 _samples_count;

    int32 _width{}, _height{};

    gl_renderbuffer_internal_format _internal_format;


public:

    [[nodiscard]] std::int32_t get_samples_count() const { return _samples_count; }

    [[nodiscard]] std::int32_t get_width() const { return _width; }

    [[nodiscard]] std::int32_t get_height() const { return _height; }

    [[nodiscard]] gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }



};

#endif

