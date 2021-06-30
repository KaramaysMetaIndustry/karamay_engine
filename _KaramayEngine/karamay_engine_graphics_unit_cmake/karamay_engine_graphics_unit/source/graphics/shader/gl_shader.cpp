#include "gl_shader.h"

gl_shader::gl_shader(gl_shader_enum::type shader_type, const std::vector<std::uint8_t>& source_stream) :
    _shader_type(shader_type),
    _source_stream(source_stream)
{
    _handle = glCreateShader(static_cast<GLenum>(_shader_type));
    auto _source = reinterpret_cast<GLchar*>(_source_stream.data());
    glShaderSource(_handle, 1, &_source, nullptr);
    glCompileShader(_handle);


    GLint _result = GL_FALSE;
    char info[512];
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &_result);
    if (_result != GL_TRUE) {
        glGetShaderInfoLog(_handle, 512, nullptr, info);
        std::cout << "shader compile fail : " << info << std::endl;
    }
}

gl_shader::~gl_shader()
{
    glDeleteShader(_handle);
}

gl_shader::gl_shader(const std::string &path) {
    load(path);

    glCompileShader(_handle);

    GLint _result = GL_FALSE;
    char info[512];
    glGetShaderiv(_handle, GL_COMPILE_STATUS, &_result);
    if (_result != GL_TRUE) {
        glGetShaderInfoLog(_handle, 512, nullptr, info);
        std::cout << "shader compile fail : " << info << std::endl;
    }
}


