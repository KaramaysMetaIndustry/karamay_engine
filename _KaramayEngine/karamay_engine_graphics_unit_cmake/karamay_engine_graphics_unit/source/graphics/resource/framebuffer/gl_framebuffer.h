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

    void set_color_attachment(uint32 attachment_index, const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer || attachment_index >= GL_MAX_COLOR_ATTACHMENTS) return;
        glNamedFramebufferRenderbuffer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, GL_RENDERBUFFER, renderbuffer->get_handle());
    }
    void set_depth_attchment(const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer) return;
        glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }
    void set_stencil_attachment(const std::shared_ptr<gl_renderbuffer>& renderbuffer)
    {
        if (!renderbuffer) return;
        glNamedFramebufferRenderbuffer(_handle, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }
    void set_depth_stencil(const gl_renderbuffer* renderbuffer)
    {
        if (renderbuffer)
        {
            glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
        }
    }

    void set_color_attachment()
    {
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

    void read_pixels(int32 x, int32 y, int32 width, int32 height)
    {
        
        glReadPixels(x, y, width, height, 0, 0, nullptr);
    }

    void clamp_color()
    {
        //glClampColor();
    }

    void blit(int32 src_x0, int32 src_y0, int32 src_x1, int32 src_y1, gl_framebuffer* dst_framebuffer, int32 dst_x0, int32 dst_y0, int32 dst_x1, int32 dst_y1)
    {
        glBlitNamedFramebuffer(_handle, dst_framebuffer->get_handle(),
            src_x0, src_y0, src_x1, src_y1, dst_x0, dst_y0, dst_x1, dst_y1, 
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT, 
            GL_NEAREST); // GL_LINEAR
    }

    void copy_to()
    {
        //glCopyTextureSubImage2D()
    }

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


/*
* GL_FONT_LEFT GL_FONT_RIGHT
* GL_BACK_LEFT GL_BACK_RIGHT
* GL_DEPTH
* GL_STENCIL
*/
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

public:

    static void clear_color_buffer()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    static void clear_color_buffer(std::float_t red, std::float_t green, std::float_t blue, std::float_t alpha)
    {
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    static void clear_depth_buffer() noexcept {}
    static void clear_depth_buffer(std::double_t depth) noexcept
    {
        glClearDepth(depth);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    static void clear_stencil_buffer() noexcept
    {

    }
    static void clear_stencil_buffer(std::int32_t stencil) noexcept
    {
        glClearStencil(stencil);
        glClear(GL_STENCIL_BUFFER_BIT);
    }

public:

    static void read_pixels()
    {
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