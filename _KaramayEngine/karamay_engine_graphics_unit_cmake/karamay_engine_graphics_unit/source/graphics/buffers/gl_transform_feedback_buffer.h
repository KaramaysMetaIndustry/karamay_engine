#ifndef KGL_TRANSFORM_FEEDBACK_BUFFER_H
#define KGL_TRANSFORM_FEEDBACK_BUFFER_H

#include "gl_buffer.h"

// 0xFC807e12026BedD66DD1f6e853fd93beBEA66558
struct gl_transform_feedback_buffer_descriptor{
};

class gl_transform_feedback_buffer {
public:
    gl_transform_feedback_buffer() = delete;
    explicit gl_transform_feedback_buffer(const gl_transform_feedback_buffer_descriptor& descriptor)
    {

    }

    ~gl_transform_feedback_buffer() = default;

public:

    void bind(){
        if(!_buffer) return;
        glBindBufferRange(GL_TRANSFORM_FEEDBACK_BUFFER, 0, _buffer->get_handle(), 0, 100);
    }

    void unbind(){
        if(!_buffer) return;
        glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    }

public:

    void flush(){}

    void read_back(){}

private:

    std::unique_ptr<gl_buffer> _buffer;

    void _initialize(const gl_transform_feedback_buffer_descriptor& descriptor)
    {
        gl_buffer_storage_options _options;
        _buffer = std::make_unique<gl_buffer>(100, _options);
        //_buffer->execute_mapped_memory_writer()
    }
};

#endif
