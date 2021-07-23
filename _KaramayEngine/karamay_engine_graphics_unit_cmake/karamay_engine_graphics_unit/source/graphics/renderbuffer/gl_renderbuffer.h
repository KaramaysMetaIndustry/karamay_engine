#ifndef H_GL_RENDERBUFFER
#define H_GL_RENDERBUFFER

#include "graphics/glo/gl_object.h"

enum class gl_renderbuffer_internal_format
{
    NONE,
};


class gl_renderbuffer final : public gl_object
{
public:

	gl_renderbuffer(std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format) :
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
	
	std::int32_t _width, _height;

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

class gl_multisample_renderbuffer final : public gl_object
{
public:

    gl_multisample_renderbuffer(std::int32_t samples_count, std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format) :
        _samples_count(samples_count),
        _width(width),
        _height(height),
        _internal_format(internal_format)
    {
        glCreateRenderbuffers(1, &_handle);
        if (samples_count > GL_MAX_SAMPLES || width > GL_MAX_RENDERBUFFER_SIZE || height > GL_MAX_RENDERBUFFER_SIZE) return;

        glNamedRenderbufferStorageMultisample(_handle, samples_count, static_cast<GLenum>(internal_format), width, height);
    }

    ~gl_multisample_renderbuffer() override
    {
        glDeleteRenderbuffers(1, &_handle);
    }

private:

    std::int32_t _samples_count;

    std::int32_t _width, _height;

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


class gl_renderbuffer_factory
{
private:

    static std::forward_list<std::shared_ptr<gl_renderbuffer>> _renderbuffer_pool;

    static std::forward_list<std::shared_ptr<gl_multisample_renderbuffer>> _multisample_renderbuffer_pool;

public:

    static std::shared_ptr<gl_renderbuffer> get_renderbuffer(std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format)
    {
        for(const auto& _renderbuffer : _renderbuffer_pool)
        {
            if(_renderbuffer &&
            _renderbuffer->get_width() == width &&
            _renderbuffer->get_height() == height &&
            _renderbuffer->get_internal_format() == internal_format) return _renderbuffer;
        }
        return std::make_shared<gl_renderbuffer>(width, height, internal_format);
    }

    static std::shared_ptr<gl_multisample_renderbuffer> get_multisample_renderbuffer(std::int32_t samples_count, std::int32_t width, std::int32_t height, gl_renderbuffer_internal_format internal_format)
    {
        for(const auto& _multisample_renderbuffer : _multisample_renderbuffer_pool)
        {
            if(_multisample_renderbuffer &&
            _multisample_renderbuffer->get_samples_count() == samples_count &&
            _multisample_renderbuffer->get_width() == width &&
            _multisample_renderbuffer->get_height() == height &&
            _multisample_renderbuffer->get_internal_format() == internal_format) return _multisample_renderbuffer;
        }
        return std::make_shared<gl_multisample_renderbuffer>(samples_count, width, height, internal_format);
    }

};


#endif

