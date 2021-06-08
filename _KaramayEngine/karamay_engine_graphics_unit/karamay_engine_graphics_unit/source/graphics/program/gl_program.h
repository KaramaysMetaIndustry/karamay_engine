#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/shader/gl_shader.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/buffer/customization/gl_uniform_buffer.h"
#include "graphics/buffer/customization/gl_shader_storage_buffer.h"
#include "graphics/buffer/customization/gl_atomic_counter_buffer.h"
#include "graphics/texture/gl_texture.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/framebuffer/gl_default_framebuffer.h"

enum class gl_buffer_mode
{
	INTERLEAVED = GL_INTERLEAVED_ATTRIBS,
	SEPARATE_ATTRIBS = GL_SEPARATE_ATTRIBS
};

enum class gl_uniform_type : GLenum
{
	FLOAT = GL_FLOAT,	//float
	FLOAT_VEC2 = GL_FLOAT_VEC2,	//vec2
	FLOAT_VEC3 = GL_FLOAT_VEC3,	//vec3
	FLOAT_VEC4 = GL_FLOAT_VEC4,	//vec4
	DOUBLE = GL_DOUBLE,	//double
	DOUBLE_VEC2 = GL_DOUBLE_VEC2,	//dvec2
	DOUBLE_VEC3 = GL_DOUBLE_VEC3,	//dvec3
	DOUBLE_VEC4 = GL_DOUBLE_VEC4,	//dvec4
	INT = GL_INT,	//int
	INT_VEC2 = GL_INT_VEC2,	//ivec2
	INT_VEC3 = GL_INT_VEC3,	//ivec3
	INT_VEC4 = GL_INT_VEC4,	//ivec4
	UNSIGNED_INT = GL_UNSIGNED_INT,	//unsigned int
	UNSIGNED_INT_VEC2 = GL_UNSIGNED_INT_VEC2,	//uvec2
	UNSIGNED_INT_VEC3 = GL_UNSIGNED_INT_VEC3,	//uvec3
	UNSIGNED_INT_VEC4 = GL_UNSIGNED_INT_VEC4,	//uvec4
	BOOL = GL_BOOL,	//bool
	BOOL_VEC2 = GL_BOOL_VEC2,	//bvec2
	BOOL_VEC3 = GL_BOOL_VEC3,	//bvec3
	BOOL_VEC4 = GL_BOOL_VEC4,	//bvec4
	FLOAT_MAT2 = GL_FLOAT_MAT2,	//mat2
	FLOAT_MAT3 = GL_FLOAT_MAT3,	//mat3
	FLOAT_MAT4 = GL_FLOAT_MAT4,	// mat4
	FLOAT_MAT2x3 = GL_FLOAT_MAT2x3,	//mat2x3
	FLOAT_MAT2x4 = GL_FLOAT_MAT2x4,	//mat2x4
	FLOAT_MAT3x2 = GL_FLOAT_MAT3x2,	//mat3x2
	FLOAT_MAT3x4 = GL_FLOAT_MAT3x4,	//mat3x4
	FLOAT_MAT4x2 = GL_FLOAT_MAT4x2,	//mat4x2
	FLOAT_MAT4x3 = GL_FLOAT_MAT4x3,	//mat4x3
	DOUBLE_MAT2 = GL_DOUBLE_MAT2,	//dmat2
	DOUBLE_MAT3 = GL_DOUBLE_MAT3,	//dmat3
	DOUBLE_MAT4 = GL_DOUBLE_MAT4,	//dmat4
	DOUBLE_MAT2x3 = GL_DOUBLE_MAT2x3,	//dmat2x3
	DOUBLE_MAT2x4 = GL_DOUBLE_MAT2x4,	//dmat2x4
	DOUBLE_MAT3x2 = GL_DOUBLE_MAT3x2,	//dmat3x2
	DOUBLE_MAT3x4 = GL_DOUBLE_MAT3x4,	//dmat3x4
	DOUBLE_MAT4x2 = GL_DOUBLE_MAT4x2,	//dmat4x2
	DOUBLE_MAT4x3 = GL_DOUBLE_MAT4x3,	//dmat4x3
	SAMPLER_1D = GL_SAMPLER_1D,	//sampler1D
	SAMPLER_2D = GL_SAMPLER_2D,	//sampler2D
	SAMPLER_3D = GL_SAMPLER_3D,	//sampler3D
	SAMPLER_CUBE = GL_SAMPLER_CUBE,	//samplerCube
	SAMPLER_1D_SHADOW = GL_SAMPLER_1D_SHADOW,	//sampler1DShadow
	SAMPLER_2D_SHADOW = GL_SAMPLER_2D_SHADOW,	//sampler2DShadow
	SAMPLER_1D_ARRAY = GL_SAMPLER_1D_ARRAY,	//sampler1DArray
	SAMPLER_2D_ARRAY = GL_SAMPLER_2D_ARRAY,	//sampler2DArray
	SAMPLER_1D_ARRAY_SHADOW = GL_SAMPLER_1D_ARRAY_SHADOW,	//sampler1DArrayShadow
	SAMPLER_2D_ARRAY_SHADOW = GL_SAMPLER_2D_ARRAY_SHADOW,	//sampler2DArrayShadow
	SAMPLER_2D_MULTISAMPLE = GL_SAMPLER_2D_MULTISAMPLE, //sampler2DMS
	SAMPLER_2D_MULTISAMPLE_ARRAY = GL_SAMPLER_2D_MULTISAMPLE_ARRAY,	//sampler2DMSArray
	SAMPLER_CUBE_SHADOW = GL_SAMPLER_CUBE_SHADOW,	//samplerCubeShadow
	SAMPLER_BUFFER = GL_SAMPLER_BUFFER,	//samplerBuffer
	SAMPLER_2D_RECT = GL_SAMPLER_2D_RECT,	//sampler2DRect
	SAMPLER_2D_RECT_SHADOW = GL_SAMPLER_2D_RECT_SHADOW,	//sampler2DRectShadow
	INT_SAMPLER_1D = GL_INT_SAMPLER_1D,	//isampler1D
	INT_SAMPLER_2D = GL_INT_SAMPLER_2D,	//isampler2D
	INT_SAMPLER_3D = GL_INT_SAMPLER_3D,	//isampler3D
	INT_SAMPLER_CUBE = GL_INT_SAMPLER_CUBE,	//isamplerCube
	INT_SAMPLER_1D_ARRAY = GL_INT_SAMPLER_1D_ARRAY,	//isampler1DArray
	INT_SAMPLER_2D_ARRAY = GL_INT_SAMPLER_2D_ARRAY,	//isampler2DArray
	INT_SAMPLER_2D_MULTISAMPLE = GL_INT_SAMPLER_2D_MULTISAMPLE,	//isampler2DMS
	INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//isampler2DMSArray
	INT_SAMPLER_BUFFER = GL_INT_SAMPLER_BUFFER,	//isamplerBuffer
	INT_SAMPLER_2D_RECT = GL_INT_SAMPLER_2D_RECT,	//isampler2DRect
	UNSIGNED_INT_SAMPLER_1D = GL_UNSIGNED_INT_SAMPLER_1D,	//usampler1D
	UNSIGNED_INT_SAMPLER_2D = GL_UNSIGNED_INT_SAMPLER_2D,	//usampler2D
	UNSIGNED_INT_SAMPLER_3D = GL_UNSIGNED_INT_SAMPLER_3D,	//usampler3D
	UNSIGNED_INT_SAMPLER_CUBE = GL_UNSIGNED_INT_SAMPLER_CUBE,	//usamplerCube
	UNSIGNED_INT_SAMPLER_1D_ARRAY = GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,	//usampler2DArray
	UNSIGNED_INT_SAMPLER_2D_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,	//usampler2DArray
	UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,	//usampler2DMS
	UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,	//usampler2DMSArray
	UNSIGNED_INT_SAMPLER_BUFFER = GL_UNSIGNED_INT_SAMPLER_BUFFER,	//usamplerBuffer
	UNSIGNED_INT_SAMPLER_2D_RECT = GL_UNSIGNED_INT_SAMPLER_2D_RECT,	//usampler2DRect
	IMAGE_1D = GL_IMAGE_1D,	//image1D
	IMAGE_2D = GL_IMAGE_2D,	//image2D
	IMAGE_3D = GL_IMAGE_3D,	//image3D
	MAGE_2D_RECT = GL_IMAGE_2D_RECT,	//image2DRect
	MAGE_CUBE = GL_IMAGE_CUBE,	//imageCube
	MAGE_BUFFER = GL_IMAGE_BUFFER,	//imageBuffer
	MAGE_1D_ARRAY = GL_IMAGE_1D_ARRAY,	//image1DArray
	MAGE_2D_ARRAY = GL_IMAGE_2D_ARRAY,	//image2DArray
	IMAGE_2D_MULTISAMPLE = GL_IMAGE_2D_MULTISAMPLE,	//image2DMS
	IMAGE_2D_MULTISAMPLE_ARRAY = GL_IMAGE_2D_MULTISAMPLE_ARRAY,	//image2DMSArray
	INT_IMAGE_1D = GL_INT_IMAGE_1D,	//iimage1D
	INT_IMAGE_2D = GL_INT_IMAGE_2D,	//iimage2D
	INT_IMAGE_3D = GL_INT_IMAGE_3D,	//iimage3D
	INT_IMAGE_2D_RECT = GL_INT_IMAGE_2D_RECT,	//iimage2DRect
	INT_IMAGE_CUBE = GL_INT_IMAGE_CUBE,	//iimageCube
	INT_IMAGE_BUFFER = GL_INT_IMAGE_BUFFER,	//iimageBuffer
	INT_IMAGE_1D_ARRAY = GL_INT_IMAGE_1D_ARRAY,	//iimage1DArray
	INT_IMAGE_2D_ARRAY = GL_INT_IMAGE_2D_ARRAY,	//iimage2DArray
	INT_IMAGE_2D_MULTISAMPLE = GL_INT_IMAGE_2D_MULTISAMPLE,	//iimage2DMS
	INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//iimage2DMSArray
	UNSIGNED_INT_IMAGE_1D = GL_UNSIGNED_INT_IMAGE_1D,	//uimage1D
	UNSIGNED_INT_IMAGE_2D = GL_UNSIGNED_INT_IMAGE_2D,	//uimage2D
	UNSIGNED_INT_IMAGE_3D = GL_UNSIGNED_INT_IMAGE_3D,	//uimage3D
	UNSIGNED_INT_IMAGE_2D_RECT = GL_UNSIGNED_INT_IMAGE_2D_RECT,	//uimage2DRect
	UNSIGNED_INT_IMAGE_CUBE = GL_UNSIGNED_INT_IMAGE_CUBE,	//uimageCube
	UNSIGNED_INT_IMAGE_BUFFER = GL_UNSIGNED_INT_IMAGE_BUFFER,	//uimageBuffer
	UNSIGNED_INT_IMAGE_1D_ARRAY = GL_UNSIGNED_INT_IMAGE_1D_ARRAY,	//uimage1DArray
	UNSIGNED_INT_IMAGE_2D_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_ARRAY,	//uimage2DArray
	UNSIGNED_INT_IMAGE_2D_MULTISAMPLE = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,	//uimage2DMS
	UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY = GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,	//uimage2DMSArray
	UNSIGNED_INT_ATOMIC_COUNTER	= GL_UNSIGNED_INT_ATOMIC_COUNTER	//atomic_uint
};


/**
 * [Fixed] you must call this func at some time
 * [Optional] you call choose to call this func and remember to call all associated funcs
 * 
 * opengl org obj, which include diff shader stages
 * and in our logic, we do not choose a multiprogram solution
 * 
 * 
 */
class gl_program final : public gl_object
{
public:

	gl_program();

	virtual ~gl_program();

public:

	/**
	 * once you install these component, you have no chance to remove or add them until the program destroyed
	 * 
	 */
	void construct(const std::vector<std::string>& shader_paths);

	void assembly(const std::vector<std::string>& shader_paths)
	{
		for (const auto& path : shader_paths)
		{
			auto shader = std::make_shared<gl_shader>();
			if (shader)
			{
				shader->load(path);
				shader->compile();
				glAttachShader(_handle, shader->get_handle());
				_shaders.push_back(shader);
			}
		}

		/*if (is_separable)
			glProgramParameteri(_handle, GL_PROGRAM_SEPARABLE, GL_TRUE);*/

			/*glBindAttribLocation(_handle, 0, "Position");
			glBindFragDataLocation(_handle, 0, "FragColor");*/

		glLinkProgram(_handle);

		GLint logLength = 0;
		GLint success;
		char infoLog[512];
		glGetProgramiv(_handle, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(_handle, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		else {
			std::cout << "[program is linked.]" << std::endl;
		}

		glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 0) {
			char* log = (char*)malloc(logLength);
			glGetProgramInfoLog(_handle, NULL, &logLength, log);
			printf("============log: %s\n", log);
			free(log);
		}
	}

public:

	void set_vertex_array(std::shared_ptr<gl_vertex_array> vertex_array);

	void set_element_array_buffer(std::shared_ptr<gl_element_array_buffer> element_array_buffer);

	void set_transform_feedback(std::shared_ptr<gl_transform_feedback> transform_feedback);

	void add_uniform_buffers(const std::vector<std::shared_ptr<gl_uniform_buffer>>& uniform_buffers);

	void add_uniform_buffer(std::shared_ptr<gl_uniform_buffer> uniform_buffer);

	void add_shader_storage_buffers(const std::vector<std::shared_ptr<gl_shader_storage_buffer>>& shader_storage_buffers);

	void add_shader_storage_buffer(std::shared_ptr<gl_shader_storage_buffer> shader_storage_buffer);

	void add_atomic_counter_buffers(const std::vector<std::shared_ptr<gl_atomic_counter_buffer>>& atomic_counter_buffers);

	void add_atomic_counter_buffer(std::shared_ptr<gl_atomic_counter_buffer> atomic_counter_buffer);

	void set_framebuffer(std::shared_ptr<gl_framebuffer> framebuffer = nullptr);

	void set_commands(std::function<void(void)> commands_lambda);

public:

	std::shared_ptr<gl_vertex_array> get_vertex_array();

	std::shared_ptr<gl_element_array_buffer> get_element_array_buffer();

	std::shared_ptr<gl_transform_feedback> get_transform_feedback();

	std::shared_ptr<gl_uniform_buffer> get_uniform_buffer(std::uint32_t index);

	std::shared_ptr<gl_shader_storage_buffer> get_shader_storage_buffer(std::uint32_t index);

	std::shared_ptr<gl_atomic_counter_buffer> get_atomic_counter_buffer(std::uint32_t index);

	std::shared_ptr<gl_framebuffer> get_framebuffer();

public:

	void set_stencil_test()
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilMask(GL_TRUE);
	}

	void enable_stencil_test()
	{
		glEnable(GL_STENCIL_TEST);
	}

	void disable_stencil_test()
	{
		glDisable(GL_STENCIL_TEST);
	}

	void set_depth_test()
	{
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glClearDepth(1.0f);
	}

	void enable_depth_test()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void disable_depth_test()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void set_alpha_test()
	{
		//glAlphaFunc();
	}

	void enable_alpha_test()
	{
		glEnable(GL_ALPHA_TEST);
		
	}

	void disable_alpha_test()
	{
		glDisable(GL_ALPHA_TEST);
	}
	 
public:

	/**
	 * start render processing
	 */
	void render(std::float_t delta_time);

private:

	std::vector<std::shared_ptr<gl_shader>> _shaders;

	std::shared_ptr<gl_vertex_array> _vertex_array;
	
	std::shared_ptr<gl_element_array_buffer> _element_array_buffer;
	
	std::shared_ptr<gl_transform_feedback> _transform_feedback;
	
	std::vector<std::shared_ptr<gl_uniform_buffer>> _uniform_buffers;
	
	std::vector<std::shared_ptr<gl_shader_storage_buffer>> _shader_storage_buffers;
	
	std::vector<std::shared_ptr<gl_atomic_counter_buffer>> _atomic_counter_buffers;
	
	std::shared_ptr<gl_framebuffer> _framebuffer;
	
	static std::shared_ptr<gl_default_framebuffer> _default_framebuffer;
	
	std::function<void(void)> _commands_lambda;

private:
	//~ render begin
	void _tick_objects();
	void _install();
	void _enable();
	void _call_commands();
	void _disable();
	void _uninstall();
	//~ render end
private:

	// set only once time (when you first time setting the transform feedback)
	void _set_transform_feedback_varyings();

	// bind these persistent data to context (context is public)
	void _bind_vertex_array();
	void _bind_element_array_buffer();
	void _bind_transform_feedback();
	void _bind_uniform_buffers();
	void _bind_shader_storage_buffers();
	void _bind_atomic_counter_buffers();
	void _bind_framebuffer();
	void _bind_textures();

	void _launch_uniforms();

	// unbind these persistent data from context (you can not ensure that slots your have used will be overriden by next program)
	void _unbind_vertex_array()
	{
		glBindVertexArray(0);
	}
	void _unbind_element_array_buffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void _unbind_transform_feedback()
	{
		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	}
	void _unbind_uniform_buffers()
	{
		// clear all unifrom buffer binding is too expensive
		// use the stored ids
		for (std::int32_t i = 0; i < _uniform_buffers.size(); ++i)
		{
			glBindBufferBase(GL_UNIFORM_BUFFER, i, 0);
		}
	}
	void _unbind_shader_storage_buffers()
	{
		for (std::int32_t i = 0; i < _shader_storage_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_atomic_counter_buffers()
	{
		for (std::uint32_t i = 0; i < _atomic_counter_buffers.size(); ++i)
		{
			glBindBufferBase(GL_SHADER_STORAGE_BUFFER, i, 0);
		}
	}
	void _unbind_framebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void _unbind_textures() {}


#define DEF_ADD_UNIFORMS(TYPE)\
private:\
std::vector<std::shared_ptr<gl_variable<##TYPE##>>> _##TYPE##_uniforms;\
public:\
inline void add_uniforms(const std::vector<std::shared_ptr<gl_variable<##TYPE##>>>& TYPE##_uniforms)\
{\
	_##TYPE##_uniforms.insert(_##TYPE##_uniforms.cend(), TYPE##_uniforms.cbegin(), TYPE##_uniforms.cend());\
}\
inline void add_uniform(std::shared_ptr<gl_variable<##TYPE##>> TYPE##_uniform)\
{\
	_##TYPE##_uniforms.push_back(TYPE##_uniform);\
}\

	// float
	DEF_ADD_UNIFORMS(glu_f32vec1)
	DEF_ADD_UNIFORMS(glu_f32vec2)
	DEF_ADD_UNIFORMS(glu_f32vec3)
	DEF_ADD_UNIFORMS(glu_f32vec4)
	// double
	DEF_ADD_UNIFORMS(glu_f64vec1)
	DEF_ADD_UNIFORMS(glu_f64vec2)
	DEF_ADD_UNIFORMS(glu_f64vec3)
	DEF_ADD_UNIFORMS(glu_f64vec4)
	// int
	DEF_ADD_UNIFORMS(glu_i32vec1)
	DEF_ADD_UNIFORMS(glu_i32vec2)
	DEF_ADD_UNIFORMS(glu_i32vec3)
	DEF_ADD_UNIFORMS(glu_i32vec4)
	// uint
	DEF_ADD_UNIFORMS(glu_ui32vec1)
	DEF_ADD_UNIFORMS(glu_ui32vec2)
	DEF_ADD_UNIFORMS(glu_ui32vec3)
	DEF_ADD_UNIFORMS(glu_ui32vec4)
	// float mat
	DEF_ADD_UNIFORMS(glu_f32mat2)
	DEF_ADD_UNIFORMS(glu_f32mat3)
	DEF_ADD_UNIFORMS(glu_f32mat4)
	DEF_ADD_UNIFORMS(glu_f32mat2x3)
	DEF_ADD_UNIFORMS(glu_f32mat2x4)
	DEF_ADD_UNIFORMS(glu_f32mat3x2)
	DEF_ADD_UNIFORMS(glu_f32mat3x4)
	DEF_ADD_UNIFORMS(glu_f32mat4x2)
	DEF_ADD_UNIFORMS(glu_f32mat4x3)
	// double mat
	DEF_ADD_UNIFORMS(glu_f64mat2)
	DEF_ADD_UNIFORMS(glu_f64mat3)
	DEF_ADD_UNIFORMS(glu_f64mat4)
	DEF_ADD_UNIFORMS(glu_f64mat2x3)
	DEF_ADD_UNIFORMS(glu_f64mat2x4)
	DEF_ADD_UNIFORMS(glu_f64mat3x2)
	DEF_ADD_UNIFORMS(glu_f64mat3x4)
	DEF_ADD_UNIFORMS(glu_f64mat4x2)
	DEF_ADD_UNIFORMS(glu_f64mat4x3)



#define DEF_ADD_TEXTURES(TYPE)\
private:\
	std::vector<std::shared_ptr<gl_##TYPE##>> _##TYPE##s;\
public:\
	inline void add_texture(std::shared_ptr<gl_##TYPE##> TYPE)\
	{\
		_##TYPE##s.push_back(TYPE);\
		add_uniform(std::make_shared<gl_variable<glu_i32vec1>>(TYPE->get_name(), glu_i32vec1(static_cast<glm::int32>(_##TYPE##s.size() - 1))));\
	}\

	DEF_ADD_TEXTURES(texture_1d)
	DEF_ADD_TEXTURES(texture_1d_array)
	DEF_ADD_TEXTURES(texture_2d)
	DEF_ADD_TEXTURES(texture_2d_array)
	DEF_ADD_TEXTURES(texture_2d_multisample)
	DEF_ADD_TEXTURES(texture_2d_array_multisample)
	DEF_ADD_TEXTURES(texture_rectangle)
	DEF_ADD_TEXTURES(texture_3d)
	DEF_ADD_TEXTURES(texture_cube)
	DEF_ADD_TEXTURES(texture_cube_array)
	DEF_ADD_TEXTURES(texture_buffer)

private:
	//~ helper function
	/*inline void _update_uniform(const std::string& name, glm::float32 value)
	{
		glUniform1f(glGetUniformLocation(_handle, name.c_str()), value);
	}*/
	inline void _update_uniform(const std::string& name, glu_f32vec1 value)
	{
		glUniform1f(glGetUniformLocation(_handle, name.c_str()), value.r);
	}
	inline void _update_uniform(const std::string& name, glu_f32vec2 value)
	{
		glUniform2fv(glGetUniformLocation(_handle, name.c_str()), 2, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32vec3 value)
	{
		//glUniform3fv(glGetUniformLocation(_handle, name.c_str()), 3, glm::value_ptr(value));
		glUniform3f(glGetUniformLocation(_handle, name.c_str()), value.r, value.g, value.b);
	}
	inline void _update_uniform(const std::string& name, glu_f32vec4 value)
	{
		glUniform4fv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	/*inline void _update_uniform(const std::string& name, glm::float64 value)
	{
		glUniform1d(glGetUniformLocation(_handle, name.c_str()), value);
	}*/
	inline void _update_uniform(const std::string& name, glu_f64vec1 value)
	{
		glUniform1d(glGetUniformLocation(_handle, name.c_str()), value.r);
	}
	inline void _update_uniform(const std::string& name, glu_f64vec2 value)
	{
		glUniform2dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64vec3 value)
	{
		glUniform3dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64vec4 value)
	{
		glUniform4dv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	/*inline void _update_uniform(const std::string& name, glm::int32 value)
	{
		glUniform1i(glGetUniformLocation(_handle, name.c_str()), value);
	}*/
	inline void _update_uniform(const std::string& name, glu_i32vec1 value)
	{
		glUniform1i(glGetUniformLocation(_handle, name.c_str()), value.r);
	}
	inline void _update_uniform(const std::string& name, glu_i32vec2 value)
	{
		glUniform2iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_i32vec3 value)
	{
		glUniform3iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_i32vec4 value)
	{
		glUniform4iv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	/*inline void _update_uniform(const std::string& name, glm::uint32 value)
	{
		glUniform1ui(glGetUniformLocation(_handle, name.c_str()), value);
	}*/
	inline void _update_uniform(const std::string& name, glu_ui32vec1 value)
	{
		glUniform1ui(glGetUniformLocation(_handle, name.c_str()), value.r);
	}
	inline void _update_uniform(const std::string& name, glu_ui32vec2 value)
	{
		glUniform2uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_ui32vec3 value)
	{
		glUniform3uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_ui32vec4 value)
	{
		glUniform4uiv(glGetUniformLocation(_handle, name.c_str()), 1, glm::value_ptr(value));
	}
	
	inline void _update_uniform(const std::string& name, glu_bvec1 value)
	{
		
	}
	inline void _update_uniform(const std::string& name, glu_bvec2 value)
	{

	}
	inline void _update_uniform(const std::string& name, glu_bvec3 value)
	{

	}
	inline void _update_uniform(const std::string& name, glu_bvec4 value)
	{

	}
	
	inline void _update_uniform(const std::string& name, glu_f32mat2 value)
	{
		glUniformMatrix2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat3 value)
	{
		glUniformMatrix3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat2x3 value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat2x4 value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat3x2 value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat3x4 value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat4x2 value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f32mat4x3 value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	inline void _update_uniform(const std::string& name, glu_f64mat2 value)
	{
		glUniformMatrix2dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat3 value)
	{
		glUniformMatrix3dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat4 value)
	{
		glUniformMatrix4dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat2x3 value)
	{
		glUniformMatrix2x3dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat2x4 value)
	{
		glUniformMatrix2x4dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat3x2 value)
	{
		glUniformMatrix3x2dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat3x4 value)
	{
		glUniformMatrix3x4dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat4x2 value)
	{
		glUniformMatrix4x2dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void _update_uniform(const std::string& name, glu_f64mat4x3 value)
	{
		glUniformMatrix4x3dv(glGetUniformLocation(_handle, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

public:

	void generate_uniform_buffer_layout(const std::string& block_name)
	{
		
		std::vector<GLchar*> _names = {};
		std::vector<GLuint> _indices(_names.size());
		std::vector<GLint> _offsets(_names.size());
		// get block size

		std::int32_t _block_size = 0;
		const auto _block_index = glGetUniformBlockIndex(_handle, block_name.c_str());
		glGetActiveUniformBlockiv(_handle, _block_index, GL_UNIFORM_BLOCK_DATA_SIZE, &_block_size);
		//glGetUniformIndices(_handle, _names.size(), _names.data(), _indices.data());
		glGetActiveUniformsiv(_handle, 4, _indices.data(), GL_UNIFORM_OFFSET, _offsets.data());
		
	}


	const std::int32_t get_uniform_buffer_block_size(const std::string block_name) const
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle,
			glGetUniformBlockIndex(_handle, block_name.c_str()),
			GL_UNIFORM_BLOCK_DATA_SIZE, &_value);
		return _value;
	}

	const std::int32_t get_uniform_buffer_item_offset(const std::string& name) const
	{
		const char* str = name.data();
		GLuint _index = 0;
		GLint _offset = 0;
		glGetUniformIndices(_handle, 1, &str, &_index);
		glGetActiveUniformsiv(_handle, 1, &_index, GL_UNIFORM_OFFSET, &_offset);
		return _offset;
	}


	const std::int32_t get_shader_storage_buffer_block_size() const
	{
		GLint _value = 0;
		glGetProgramResourceIndex(_handle, GL_SHADER_STORAGE_BLOCK, "");
		return _value;
	}

	const std::int32_t get_shader_storage_buffer_item_offset() const
	{
		return 0;
	}




	std::vector<std::int32_t> get_uniform_buffer_uniform_indices(const std::string& block_name)
	{
		GLint* _value = nullptr;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, _value);
		const auto _size = get_uniform_buffer_uniforms_num(block_name);

		std::vector<std::int32_t> _indices;
		for (std::int32_t i = 0; i < _size; ++i)
		{
			_indices.push_back(_value[i]);
		}

		return _indices;
	}

	std::int32_t get_uniform_buffer_block_name_length(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_NAME_LENGTH, &_value);
		return _value;
	}

	std::int32_t get_uniform_buffer_binding_index(const std::string& block_name)
	{
		GLint _value;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_BINDING, &_value);
		return _value;
	}

	std::int32_t get_uniform_buffer_uniforms_num(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &_value);
		return _value;
	}

	bool is_uniform_buffer_referred_by_vert_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_tesc_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_tese_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_geom_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_frag_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &_value);
		return _value == GL_TRUE;
	}
	bool is_uniform_buffer_referred_by_comp_shader(const std::string& block_name)
	{
		GLint _value = 0;
		glGetActiveUniformBlockiv(_handle, glGetUniformBlockIndex(_handle, block_name.c_str()), GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, &_value);
		return _value == GL_TRUE;
	}
 
};
