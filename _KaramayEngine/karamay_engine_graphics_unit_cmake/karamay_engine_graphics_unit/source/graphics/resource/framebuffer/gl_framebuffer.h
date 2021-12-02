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

enum class gl_framebuffer_draw_format : GLenum
{
    COLOR_INDEX = GL_COLOR_INDEX,
    STENCIL_INDEX = GL_STENCIL_INDEX,
    DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
    
    RGB = GL_RGB,
    BGR = GL_BGR,
    RGBA = GL_RGBA,
    BGRA = GL_BGRA,
    RED = GL_RED,
    GREEN = GL_GREEN,
    BLUE = GL_BLUE,
    ALPHA = GL_ALPHA,

    LUMINANCE = GL_LUMINANCE,
    LUMINANCE_ALPHA = GL_LUMINANCE_ALPHA
};

enum class gl_framebuffer_draw_type : GLenum
{
    BITMAP = GL_BITMAP,

    BYTE = GL_BYTE,
    SHORT = GL_SHORT,
    INT = GL_INT,
    FLOAT = GL_FLOAT,

    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_BYTE_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
    UNSIGNED_BYTE_2_3_3_REV = GL_UNSIGNED_BYTE_2_3_3_REV,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_SHORT_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
    UNSIGNED_SHORT_5_6_5_REV = GL_UNSIGNED_SHORT_5_6_5_REV,
    UNSIGNED_SHORT_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
    UNSIGNED_SHORT_4_4_4_4_REV = GL_UNSIGNED_SHORT_4_4_4_4_REV,
    UNSIGNED_SHORT_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
    UNSIGNED_SHORT_1_5_5_5_REV = GL_UNSIGNED_SHORT_1_5_5_5_REV,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    UNSIGNED_INT_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
    UNSIGNED_INT_8_8_8_8_REV = GL_UNSIGNED_INT_8_8_8_8_REV,
    UNSIGNED_INT_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
    UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
    
};


class gl_framebuffer final : public gl_framebuffer_base{
public:
    gl_framebuffer(uint32 width, uint32 height)
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

    void reallocate(uint32 width, uint32 height)
    {

    }

private:

    std::vector<gl_texture_2d*> colors_attachments;
    gl_texture_2d* depth_component;
    gl_texture_2d* stencil_component;

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

    void set_color_attachment(uint32 attachment_index, gl_renderbuffer* renderbuffer)
    {
        glNamedFramebufferRenderbuffer(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, GL_RENDERBUFFER, renderbuffer->get_handle());
    }

    void set_color_attachment(uint32 attachment_index, gl_texture_2d* texture_2d, int32 mipmap_index)
    {
        glNamedFramebufferTexture(_handle, GL_COLOR_ATTACHMENT0 + attachment_index, texture_2d->get_handle(), mipmap_index);
    }

    void set_depth_attachment(gl_renderbuffer* renderbuffer)
    {
        glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }

    void set_stencil_attachment(gl_renderbuffer* renderbuffer)
    {
        glNamedFramebufferRenderbuffer(_handle, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
    }

    void set_depth_stencil_attachment(gl_renderbuffer* renderbuffer)
    {
        glNamedFramebufferRenderbuffer(_handle, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->get_handle());
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

    void draw_pixels(int32 width, int32 height, gl_framebuffer_draw_format format, gl_framebuffer_draw_type type, const void* pixels)
    {
        //glPixelStoref();
        //glPixelTransferf();
        //glPixelMapfv();
        //glPixelZoom()
        glDrawPixels(width, height, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
    }


    void draw_depth_stencil(int32 width, int32 height, GLenum type, const void* pixels)
    {
        glDrawPixels(width, height, GL_DEPTH_STENCIL, type, pixels);
    }

    void read_color(int32 attachment_index, int32 x, int32 y, int32 width, int32 height, GLenum format, GLenum type, void* pixels)
    {
        glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
        glClampColor(GL_CLAMP_READ_COLOR, GL_TRUE); // GL_FALSE, GL_FIXED_ONLY
        glReadPixels(x, y, width, height, format, type, pixels);
    }

    void read_depth(int32 x, int32 y, int32 width, int32 height, GLenum type, void* pixels)
    {
        glReadPixels(x, y, width, height, GL_DEPTH_COMPONENT, type, pixels);
    }

    void read_stencil(int32 x, int32 y, int32 width, int32 height, GLenum type, void* pixels)
    {
        glReadPixels(x, y, width, height, GL_STENCIL_INDEX, type, pixels);
    }

    void read_depth_stencil(int32 x, int32 y, int32 width, int32 height, GLenum type, void* pixels)
    {
        glReadPixels(x, y, width, height, GL_DEPTH_STENCIL, type, pixels);
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

 private:

    void check_status()
    {
        glCheckFramebufferStatus(GL_FRAMEBUFFER);
    }

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