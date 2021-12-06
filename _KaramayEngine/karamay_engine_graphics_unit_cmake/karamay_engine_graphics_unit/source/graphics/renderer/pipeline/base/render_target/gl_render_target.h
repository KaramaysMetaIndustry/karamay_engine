#ifndef GL_RENDER_TARGET
#define GL_RENDER_TARGET

class gl_render_target
{
public:

    gl_render_target() : _framebuffer(nullptr)
    {}

    gl_render_target(const gl_render_target&) = delete;
    gl_render_target& operator=(const gl_render_target&) = delete;

    ~gl_render_target() {}

public:

    void set_framebuffer(gl_framebuffer* framebuffer) { _framebuffer = framebuffer; }

    gl_framebuffer* get_framebuffer() const { return _framebuffer; }

    void set_default() { _framebuffer = nullptr; }

public:

    void bind()
    {
        if (_framebuffer)
        {
            _framebuffer->bind();
        }
        else {
            gl_default_framebuffer::get_instance()->bind();
        }
    }

    void unbind()
    {
        if (_framebuffer)
        {
            _framebuffer->unbind();
        }
        else {
            gl_default_framebuffer::get_instance()->unbind();
        }
    }

private:

    gl_framebuffer* _framebuffer;

};


#endif