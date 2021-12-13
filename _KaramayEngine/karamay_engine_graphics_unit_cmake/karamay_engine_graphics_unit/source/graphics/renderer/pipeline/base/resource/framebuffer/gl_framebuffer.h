#ifndef GL_FRAMEBUFFER_H
#define GL_FRAMEBUFFER_H

#include "../glo/gl_object.h"
#include "../texture/gl_texture.h"
#include "../renderbuffer/gl_renderbuffer.h"

class gl_framebuffer_base : public gl_object
{
protected:
    gl_framebuffer_base() : gl_object(gl_object_type::FRAMEBUFFER_OBJ) {}

public:
    virtual void bind() = 0;
    virtual void unbind() = 0;
};

enum class gl_default_framebuffer_draw_buffer : GLenum
{
    NONE = GL_NONE,

    FRONT_LEFT = GL_FRONT_LEFT,
    FRONT_RIGHT = GL_FRONT_RIGHT,
    BACK_LEFT = GL_BACK_LEFT,
    BACK_RIGHT = GL_BACK_RIGHT,
    FRONT = GL_FRONT,
    BACK = GL_BACK,
    LEFT = GL_LEFT,
    RIGHT = GL_RIGHT,

    FRONT_AND_BACK = GL_FRONT_AND_BACK
};

enum class gl_default_framebuffer_read_buffer : GLenum
{
    FRONT_LEFT = GL_FRONT_LEFT,
    FRONT_RIGHT = GL_FRONT_RIGHT,
    BACK_LEFT = GL_BACK_LEFT,
    BACK_RIGHT = GL_BACK_RIGHT,
    FRONT = GL_FRONT,
    BACK = GL_BACK,
    LEFT = GL_LEFT,
    RIGHT = GL_RIGHT
};

/*
* GL_FONT_LEFT GL_FONT_RIGHT
* GL_BACK_LEFT GL_BACK_RIGHT
* GL_DEPTH
* GL_STENCIL
*/
class gl_default_framebuffer : public gl_framebuffer_base
{
private:
    
    gl_default_framebuffer() = default;

    static gl_default_framebuffer* _instance;

public:

    static gl_default_framebuffer* get_instance()
    {
        if (_instance == nullptr)
        {
            _instance = new gl_default_framebuffer();
        }
        return _instance;
    }

public:

    void clear_color_buffer() noexcept
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void clear_color_buffer(float r, float g, float b, float a) noexcept
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void clear_depth_buffer() noexcept
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    void clear_depth_buffer(double depth) noexcept
    {
        glClearDepth(depth);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    void clear_stencil_buffer() noexcept
    {
        glClear(GL_STENCIL_BUFFER_BIT);
    }
    void clear_stencil_buffer(int32 stencil) noexcept
    {
        glClearStencil(stencil);
        glClear(GL_STENCIL_BUFFER_BIT);
    }

    void set_depth_test(bool open)
    {
        open ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
    }
    void set_stencil_test(bool open)
    {
        open ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    }

public:

    void set_draw_buffer(gl_default_framebuffer_draw_buffer buffer)
    {
        glDrawBuffer(static_cast<GLenum>(buffer));
    }
    void set_read_buffer(gl_default_framebuffer_read_buffer buffer)
    {
        glReadBuffer(static_cast<GLenum>(buffer));
    }

public:

    void bind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void unbind() override
    {}

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


class gl_framebuffer final : public gl_framebuffer_base
{
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

    void bind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _handle);
    }

    void unbind() override
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

public:

    void enable_color_attchments(std::vector<uint32>& indices)
    {
        for (auto& index : indices)
        {
            index += GL_COLOR_ATTACHMENT0;
        }
        glNamedFramebufferDrawBuffers(_handle, indices.size(), indices.data());
    }

    void disable_color_attchments()
    {
        glNamedFramebufferDrawBuffer(_handle, GL_NONE);
    }
    

private:

    std::vector<GLenum> _active_color_attachments;

    void _set()
    {
        
    }

    std::vector<GLenum> _target_color_attachs;

    std::vector<gl_texture_2d*> _colors_tex_attachments;
    std::vector<gl_texture_2d_multisample*> _colors_tex_ms_attachments;
    gl_texture_2d* _depth_tex_component;
    gl_texture_2d* _stencil_tex_component;
    gl_texture_2d* _depth_stencil_tex_component;

    std::vector<gl_renderbuffer*> _colors_rb_attachments;
    std::vector<gl_renderbuffer_multisample*> _color_rb_ms_attachments;
    gl_texture_2d* _depth_rb_component;
    gl_texture_2d* _stencil_rb_component;
    gl_texture_2d* _depth_stencil_rb_component;

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

    void set_draw_buffer(uint32 index)
    {
        glNamedFramebufferDrawBuffer(_handle, GL_COLOR_ATTACHMENT0 + index);
    }
    void set_read_buffer(uint32 index)
    {
        glNamedFramebufferReadBuffer(_handle, GL_COLOR_ATTACHMENT0 + index);
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


#endif