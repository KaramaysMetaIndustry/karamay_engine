#ifndef GL_FRAMEBUFFER_H
#define GL_FRAMEBUFFER_H

#include "graphics/resource/glo/gl_object.h"
#include "graphics/resource/texture/gl_texture.h"
#include "graphics/resource/renderbuffer/gl_renderbuffer.h"

class gl_framebuffer_base : public gl_object{
protected:
    gl_framebuffer_base() : gl_object(gl_object_type::FRAMEBUFFER_OBJ) {}

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

class gl_framebuffer final : public gl_framebuffer_base{
public:
    gl_framebuffer()
    {
        glCreateFramebuffers(1, &_handle);
    }

    gl_framebuffer(const gl_framebuffer&) = delete;
    gl_framebuffer& operator=(const gl_framebuffer&) = delete;

    ~gl_framebuffer() override
    {
        glDeleteFramebuffers(1, &_handle);
    }

public:

    void bind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    }

    void unbind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

public:

    void color(std::uint32_t attachment_index, const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer || attachment_index >= GL_MAX_COLOR_ATTACHMENTS) return;
        glNamedFramebufferRenderbuffer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, GL_RENDERBUFFER, renderbuffer->get_handle());
    }
    
    void depth(const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer) return;
        glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }

    void stencil(const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer) return;
        glNamedFramebufferRenderbuffer(_handle, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }

    void depth_stencil(const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (renderbuffer)
        {
            glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
        }
    }

public:

    void set_drawable_color_components(std::vector<std::uint32_t> color_attachment_indices)
    {
        for (auto& elem : color_attachment_indices)
        {
            elem += GL_COLOR_ATTACHMENT0;
        }

        glDrawBuffers(static_cast<GLsizei>(color_attachment_indices.size()), color_attachment_indices.data());
    }

    void set_readable_color_component(std::uint32_t color_attachment_index)
    {
        glReadBuffer(GL_COLOR_ATTACHMENT0 + color_attachment_index);
    }

public:

    void read_color(int attachment_index, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
    void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
    void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);
    void read_depth_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type, void* pixels);

    void draw_color(int attachment_index, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
    void draw_depth(GLsizei width, GLsizei height, GLenum type, const void* pixels);
    void draw_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);
    void draw_depth_stencil(GLsizei width, GLsizei height, GLenum type, const void* pixels);

    void check_status()
    {
        glCheckFramebufferStatus(GL_FRAMEBUFFER);
    }

private:

    bool is_framebuffer() const
    {
        return glIsFramebuffer(_handle) == GL_TRUE ? true : false;
    }

};

class gl_default_framebuffer : public gl_framebuffer_base{
public:
    gl_default_framebuffer(){}

    virtual ~gl_default_framebuffer() {}

public:

    void set_draw_color_targets()
    {
        glDrawBuffer(GL_BACK_LEFT);
    }

    void read_color(GLenum mode, GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels)
    {
        glReadBuffer(mode);
        glReadPixels(x, y, width, height, format, type, pixels);
    }

    void read_depth(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);

    void read_stencil(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);


    void clear_all_color_buffers(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void clear_depth_buffer(double depth)
    {
        glClearDepth(depth);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void clear_stencil_buffer(int s)
    {
        glClearStencil(s);
        glClear(GL_STENCIL_BUFFER_BIT);

        glBlitFramebuffer()
    }

public:

    void bind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
    }

    void unbind() override
    {}

};


#endif