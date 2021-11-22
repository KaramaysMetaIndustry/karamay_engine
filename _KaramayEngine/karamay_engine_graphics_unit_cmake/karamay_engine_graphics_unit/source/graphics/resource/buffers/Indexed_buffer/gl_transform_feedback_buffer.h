#ifndef GL_TRANSFORM_FEEDBACK_BUFFER_H
#define GL_TRANSFORM_FEEDBACK_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"
#include "graphics/glsl/glsl_class.h"

enum class gl_transform_feedback_buffer_mode
{
    SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS,
    INTERLEAVED = GL_INTERLEAVED_ATTRIBS
};

// 0xFC807e12026BedD66DD1f6e853fd93beBEA66558
class gl_transform_feedback_buffer {
public:
    explicit gl_transform_feedback_buffer()
    {}

    gl_transform_feedback_buffer(const gl_transform_feedback_buffer&) = delete;
    gl_transform_feedback_buffer& operator=(const gl_transform_feedback_buffer&) = delete;

    ~gl_transform_feedback_buffer() = default;

public:

    void bind() noexcept
    {
        uint32 _binding = 0;
        for (const auto& _raw_buffer : _raw_buffers)
        {
            glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, _binding, _buffer->get_handle(), 0, 100); ++_binding;
        }
        
    }

    void unbind() noexcept
    {
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    }


    void download()
    {
        glMemoryBarrier(GL_TRANSFORM_FEEDBACK_BARRIER_BIT);
    }

private:

    std::unique_ptr<gl_buffer> _buffer;

    std::vector<std::unique_ptr<gl_buffer>> _raw_buffers;

};

#endif
