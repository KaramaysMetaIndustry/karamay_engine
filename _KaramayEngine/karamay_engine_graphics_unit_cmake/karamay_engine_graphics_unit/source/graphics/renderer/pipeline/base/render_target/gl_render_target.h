#ifndef GL_RENDER_TARGET
#define GL_RENDER_TARGET

class gl_render_target
{
public:

    gl_render_target() {}

    ~gl_render_target() {}

public:

    void set_framebuffer(gl_framebuffer* framebuffer)
    {
        if (framebuffer == nullptr)
        {
            _default_framebuffer = gl_default_framebuffer::get_instance();
            _framebuffer = nullptr;
        }
        else {
            _default_framebuffer = nullptr;
            _framebuffer = framebuffer;
        }
    }

    gl_framebuffer* get_framebuffer() const { return _framebuffer; }

public:

    void bind()
    {
        if (_framebuffer)
        {
            _framebuffer->bind();
        }
        else {
            _default_framebuffer->bind();
        }
    }

    void unbind()
    {
        if (_framebuffer)
        {
            _framebuffer->unbind();
        }
        else {
            _default_framebuffer->unbind();
        }
    }

private:

    gl_framebuffer* _framebuffer;
    gl_default_framebuffer* _default_framebuffer;

};


#endif