#ifndef GL_RENDERBUFFER_H
#define GL_RENDERBUFFER_H

#include "graphics/resource/glo/gl_object.h"

enum class gl_renderbuffer_internal_format
{
    NONE,
};

struct gl_renderbuffer_descriptor
{

};

class gl_renderbuffer final : public gl_object{
public:
    gl_renderbuffer() = delete;
    explicit gl_renderbuffer(const gl_renderbuffer_descriptor& descriptor) :
        gl_object(gl_object_type::RENDERBUFFER_OBJ)
    {}

	gl_renderbuffer(std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format) :
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

private:
	
	std::int32_t _width{}, _height{};

    gl_renderbuffer_internal_format _internal_format;

public:

    [[nodiscard]] std::int32_t get_width() const { return _width; }

    [[nodiscard]] std::int32_t get_height() const { return _height; }

    [[nodiscard]] gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }

public:

	void bind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, _handle);
    }

	void unbind()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

};

struct gl_renderbuffer_multisample_descriptor
{

};

class gl_renderbuffer_multisample final : public gl_object{
public:

    gl_renderbuffer_multisample(const gl_renderbuffer_multisample_descriptor& descriptor) :
        gl_object(gl_object_type::RENDERBUFFER_OBJ)
    {}

    gl_renderbuffer_multisample(std::int32_t samples_count, std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format) :
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

private:

    std::int32_t _samples_count{};

    std::int32_t _width{}, _height{};

    gl_renderbuffer_internal_format _internal_format;

public:

    [[nodiscard]] std::int32_t get_samples_count() const { return _samples_count; }

    [[nodiscard]] std::int32_t get_width() const { return _width; }

    [[nodiscard]] std::int32_t get_height() const { return _height; }

    [[nodiscard]] gl_renderbuffer_internal_format get_internal_format() const { return _internal_format; }

public:

    void bind();

    void unbind();

};

#endif

