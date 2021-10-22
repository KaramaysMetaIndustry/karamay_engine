#ifndef H_GL_SHADER
#define H_GL_SHADER

#include "graphics/resource/glo/gl_object.h"

enum class gl_shader_type : GLenum
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
	GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	COMPUTE_SHADER = GL_COMPUTE_SHADER
};

class gl_shader final : public gl_object{
public:
	gl_shader() = delete;
	gl_shader(gl_shader_type shader_type, const std::string& shader_path) :
		gl_object(gl_object_type::SHADER_OBJ),
		_shader_type(shader_type)
	{
		_handle = glCreateShader(static_cast<GLenum>(shader_type));
		_load(shader_path);
	}

	~gl_shader() override
	{
		glDeleteShader(_handle);
	}

private:

	void _load(const std::string& path)
	{
		// load bytes - FilePath
		std::ifstream file;
		std::string content;
		file.exceptions(std::fstream::failbit | std::fstream::badbit);
		try {
			file.open(path);
			std::stringstream sstream;
			sstream << file.rdbuf();
			file.close();
			content = sstream.str();
		}
		catch (const std::exception& e) {
			std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
		}

		auto source = content.c_str();
		glShaderSource(_handle, 1, &source, NULL);

        glCompileShader(_handle);
        GLint _result = GL_FALSE;
        char info[512];
        glGetShaderiv(_handle, GL_COMPILE_STATUS, &_result);
        if (_result != GL_TRUE) {
            glGetShaderInfoLog(_handle, 512, nullptr, info);
            std::cout << "shader compile fail : " << info << std::endl;
        }
	}

public:

	gl_shader_type get_type()
	{
		GLint _shader_type = 0;
		_get_shader_params(GL_SHADER_TYPE, &_shader_type);
		return static_cast<gl_shader_type>(_shader_type);
	}

	bool get_delete_status()
	{
		GLint _status = 0;
		_get_shader_params(GL_DELETE_STATUS, &_status);
		return _status == GL_TRUE;
	}

	bool get_compile_status()
	{
		GLint _status = 0;
		_get_shader_params(GL_COMPILE_STATUS, &_status);
		return _status == GL_TRUE;
	}

	std::uint32_t get_info_log_length()
	{
		GLint _length = 0;
		_get_shader_params(GL_INFO_LOG_LENGTH, &_length);
		return static_cast<std::uint32_t>(_length);
	}

	std::uint32_t get_source_length()
	{
		GLint _length = 0;
		_get_shader_params(GL_SHADER_SOURCE_LENGTH, &_length);
		return static_cast<std::uint32_t>(_length);
	}


	inline void _get_shader_params(GLenum param, GLint* value)
	{
		glGetShaderiv(_handle, param, value);
	}

private:

	gl_shader_type _shader_type;

    std::vector<std::uint8_t> _source_stream;

};


#endif

