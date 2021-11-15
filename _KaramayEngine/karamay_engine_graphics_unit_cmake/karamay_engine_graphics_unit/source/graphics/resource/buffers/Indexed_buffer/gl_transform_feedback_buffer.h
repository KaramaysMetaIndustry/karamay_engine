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
class TransformFeedbackBuffer {
public:
    TransformFeedbackBuffer() = delete;
    explicit TransformFeedbackBuffer(UInt32 Binding) : _Binding(Binding)
    {}

    ~TransformFeedbackBuffer() = default;

public:

    Buffer* GetRaw(UInt32 Index)
    {
        if (Index >= _Buffers.size()) return nullptr;
        return _Buffers.at(Index).get();
    }

public:

    void Bind() noexcept
    {
        if(!_buffer) return;
        glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, _Binding, _buffer->get_handle(), 0, 100);
    }

    void Unbind() noexcept
    {
        if(!_buffer) return;
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    }

private:

    UInt32 _Binding;

    std::unique_ptr<Buffer> _buffer;

    std::vector<UniquePtr<Buffer>> _Buffers;

};

#endif
