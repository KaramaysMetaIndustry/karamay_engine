#ifndef H_GL_SHADER
#define H_GL_SHADER

#include "graphics/glo/gl_object.h"

namespace gl_shader_enum
{
	enum class type : GLenum
	{
        UNKNOWN = 0,

	    VERTEX_SHADER = GL_VERTEX_SHADER,
	    TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
	    TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
	    GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
	    FRAGMENT_SHADER = GL_FRAGMENT_SHADER,

	    COMPUTE_SHADER = GL_COMPUTE_SHADER
	};

	std::string enum_to_string(gl_shader_enum::type shader_type)
    {
        switch (shader_type) {
            case type::VERTEX_SHADER:
                return std::string("VERTEX_SHADER");
            case type::TESS_CONTROL_SHADER:
                return std::string("TESS_CONTROL_SHADER");
            case type::TESS_EVALUATION_SHADER:
                return std::string("TESS_EVALUATION_SHADER");
            case type::GEOMETRY_SHADER:
                return std::string("GEOMETRY_SHADER");
            case type::FRAGMENT_SHADER:
                return std::string("FRAGMENT_SHADER");
            case type::COMPUTE_SHADER:
                return std::string("COMPUTE_SHADER");
            default:
                return std::string("UNKNOWN");
        }
    }

    gl_shader_enum::type string_to_enum(const std::string& shader_type)
    {
        if(shader_type == "VERTEX_SHADER") return gl_shader_enum::type::VERTEX_SHADER;
        if(shader_type == "TESS_CONTROL_SHADER") return gl_shader_enum::type::TESS_CONTROL_SHADER;
        if(shader_type == "TESS_EVALUATION_SHADER") return gl_shader_enum::type::TESS_EVALUATION_SHADER;
        if(shader_type == "GEOMETRY_SHADER") return gl_shader_enum::type::GEOMETRY_SHADER;
        if(shader_type == "FRAGMENT_SHADER") return gl_shader_enum::type::FRAGMENT_SHADER;
        return gl_shader_enum::type::UNKNOWN;
    }
}

class gl_shader final : public gl_object
{
public:

	explicit gl_shader(gl_shader_enum::type shader_type, const std::vector<std::uint8_t>& source_stream);
	
	~gl_shader() override;

private:

    gl_shader_enum::type _shader_type;

    std::vector<std::uint8_t> _source_stream;

public:

    [[nodiscard]] gl_shader_enum::type get_shader_type() const { return _shader_type; }


private:

	void load(const std::string& path)
	{
		auto _suffix = path.substr(path.find_last_of('.'));
		std::uint32_t _shader_type = 0;
		if (_suffix == ".vert")
		{
			_shader_type = GL_VERTEX_SHADER;
		}
		if (_suffix == ".tesc")
		{
			_shader_type = GL_TESS_CONTROL_SHADER;
		}
		if (_suffix == ".tese")
		{
			_shader_type = GL_TESS_EVALUATION_SHADER;
		}
		if (_suffix == ".geom")
		{
			_shader_type = GL_GEOMETRY_SHADER;
		}
		if (_suffix == ".frag")
		{
			_shader_type = GL_FRAGMENT_SHADER;
		}
		if (_suffix == ".comp")
		{
			_shader_type = GL_COMPUTE_SHADER;
		}

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
		_handle = glCreateShader(_shader_type);
		glShaderSource(_handle, 1, &source, NULL);
	}

public:

	gl_shader_enum::type get_type()
	{
		GLint _shader_type = 0;
		_get_shader_params(GL_SHADER_TYPE, &_shader_type);
		return static_cast<gl_shader_enum::type>(_shader_type);
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
};

#endif

