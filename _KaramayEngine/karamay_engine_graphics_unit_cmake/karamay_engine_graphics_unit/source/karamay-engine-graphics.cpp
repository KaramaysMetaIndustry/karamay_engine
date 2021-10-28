#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/program/gl_program.h"
#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"
#include "window/window.h"
#include "lua/lua_manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb/stb_image.h"




float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, //0
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f //35
};

std::uint32_t indices[] = {
	1, 2, 2, 3, 4, 5, 6
};

//std::vector<glv::f32vec3> offset_positions{
//	glv::f32vec3(0.0f,  0.0f,  0.0f),
//	glv::f32vec3(2.0f,  5.0f, -15.0f),
//	glv::f32vec3(-1.5f, -2.2f, -2.5f),
//	glv::f32vec3(-3.8f, -2.0f, -12.3f),
//	glv::f32vec3(2.4f, -0.4f, -3.5f),
//	glv::f32vec3(-1.7f,  3.0f, -7.5f),
//	glv::f32vec3(1.3f, -2.0f, -2.5f),
//	glv::f32vec3(1.5f,  2.0f, -2.5f),
//	glv::f32vec3(1.5f,  0.2f, -1.5f),
//	glv::f32vec3(-1.3f,  1.0f, -1.5f)
//};
//
//std::vector<glv::f32vec3> normals{
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//		glv::f32vec3(0.0f, 0.0f, -1.0f),
//
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//		glv::f32vec3(0.0f, 0.0f, 1.0f),
//
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//		glv::f32vec3(-1.0f, 0.0f, 0.0f),
//
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//		glv::f32vec3(1.0f, 0.0f, 0.0f),
//
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//		glv::f32vec3(0.0f, -1.0f, 0.0f),
//
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//		glv::f32vec3(0.0f, 1.0f, 0.0f),
//};
//
//std::vector<glv::f32vec2> uvs{
//		glv::f32vec2(0.0f, 0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  0.0f),
//
//		glv::f32vec2(0.0f,  0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  0.0f),
//
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(0.0f,  0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(0.0f,  0.0f),
//		glv::f32vec2(0.0f,  1.0f),
//
//		glv::f32vec2(0.0f,  1.0f),
//		glv::f32vec2(1.0f,  1.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(1.0f,  0.0f),
//		glv::f32vec2(0.0f,  0.0f),
//		glv::f32vec2(0.0f,  1.0f)
//};
//
//std::vector<glv::f32vec3> positions{
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f,  0.5f, -0.5f),
//		glv::f32vec3( 0.5f,  0.5f, -0.5f),
//		glv::f32vec3(-0.5f,  0.5f, -0.5f),
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//
//		glv::f32vec3(-0.5f, -0.5f,  0.5f),
//		glv::f32vec3( 0.5f, -0.5f,  0.5f),
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//		glv::f32vec3(-0.5f,  0.5f,  0.5f),
//		glv::f32vec3(-0.5f, -0.5f,  0.5f),
//
//		glv::f32vec3(-0.5f,  0.5f,  0.5f),
//		glv::f32vec3(-0.5f,  0.5f, -0.5f),
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//		glv::f32vec3(-0.5f, -0.5f,  0.5f),
//		glv::f32vec3(-0.5f,  0.5f,  0.5f),
//
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//		glv::f32vec3( 0.5f,  0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f,  0.5f),
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f, -0.5f),
//		glv::f32vec3( 0.5f, -0.5f,  0.5f),
//		glv::f32vec3( 0.5f, -0.5f,  0.5f),
//		glv::f32vec3(-0.5f, -0.5f,  0.5f),
//		glv::f32vec3(-0.5f, -0.5f, -0.5f),
//
//		glv::f32vec3(-0.5f,  0.5f, -0.5f),
//		glv::f32vec3( 0.5f,  0.5f, -0.5f),
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//		glv::f32vec3( 0.5f,  0.5f,  0.5f),
//		glv::f32vec3(-0.5f,  0.5f,  0.5f),
//		glv::f32vec3(-0.5f,  0.5f, -0.5f)
//};

#define sptr(T)\
std::make_shared<T##>()\

#define uptr(T)\
std::make_unique<T##>()\

template<typename T>
std::weak_ptr<T> make_weak(std::shared_ptr<T> sptr)
{
	return std::weak_ptr<T>(sptr);
}

#define wptr(sptr)\
make_weak(sptr)\


struct gl_texture_pixels
{
	stbi_uc* pixels;

	std::int32_t width, height;

	std::uint32_t format;


	gl_texture_pixels(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		std::int32_t _channels = 0;
		pixels = stbi_load(path.c_str(), &width, &height, &_channels, 0);

		//std::cout << "channels: " << _channels << std::endl;

		if (pixels == nullptr) {
			std::cout << "load fail" << std::endl;
		}

		switch (_channels)
		{
		case 1: format = GL_RED; break;
		case 3:	format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default:
			break;
		}
	}
};

void test0();

#define CLASS_NAME(__CLASS__)  #__CLASS__

#define DEFINE_UNIFORM_BLOCK(...)\
__VA_ARGS__\


void pt(glsl_transparent_t*)
{

}

template<typename T, typename... Ts>
void pt(T v, Ts... ts)
{
	
	pt(ts...);
}

int main()
{
	test0();
}


enum class gl_debug_type : GLenum
{
    DEPRECATED_BEHAVIOR = GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR,
    UNDEFINED_BEHAVIOR = GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR,
    ERROR = GL_DEBUG_TYPE_ERROR,
    MARKER = GL_DEBUG_TYPE_MARKER,
    OTHER = GL_DEBUG_TYPE_OTHER,
    PERFORMANCE = GL_DEBUG_TYPE_PERFORMANCE,
    POP_GROUP = GL_DEBUG_TYPE_POP_GROUP,
    PORTABILITY = GL_DEBUG_TYPE_PORTABILITY,
    PUSH_GROUP = GL_DEBUG_TYPE_PUSH_GROUP
};

enum class gl_debug_source : GLenum
{
    API = GL_DEBUG_SOURCE_API,
    APPLICATION = GL_DEBUG_SOURCE_APPLICATION,
    OTHER = GL_DEBUG_SOURCE_OTHER,
    SHADER_COMPILER = GL_DEBUG_SOURCE_SHADER_COMPILER,
    THIRD_PARTY = GL_DEBUG_SOURCE_THIRD_PARTY,
    WINDOW_SYSTEM = GL_DEBUG_SOURCE_WINDOW_SYSTEM
};

enum class gl_debug_severity : GLenum
{
    SEVERITY_HIGH = GL_DEBUG_SEVERITY_HIGH, // 高级
    SEVERITY_LOW = GL_DEBUG_SEVERITY_LOW, // 低级
    SEVERITY_MEDIUM = GL_DEBUG_SEVERITY_MEDIUM, // 中级
    SEVERITY_NOTIFICATION = GL_DEBUG_SEVERITY_NOTIFICATION, // 通知
};


void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
//    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
//             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
//             type, severity, message );

    auto _source = static_cast<gl_debug_source>(source);
    auto _type = static_cast<gl_debug_type>(type);
    auto _severity = static_cast<gl_debug_severity>(severity);

    std::string _source_str;
    std::string _type_str;
    std::string _severity_str;


    switch (_source) {

        case gl_debug_source::API: _source_str = "API";
            break;
        case gl_debug_source::APPLICATION: _source_str = "APPLICATION";
            break;
        case gl_debug_source::OTHER: _source_str = "OTHER";
            break;
        case gl_debug_source::SHADER_COMPILER: _source_str = "SHADER_COMPILER";
            break;
        case gl_debug_source::THIRD_PARTY: _source_str = "THIRD_PARTY";
            break;
        case gl_debug_source::WINDOW_SYSTEM: _source_str = "WINDOW_SYSTEM";
            break;
    }

    switch (_type) {

        case gl_debug_type::DEPRECATED_BEHAVIOR: _type_str = "DEPRECATED_BEHAVIOR";
            break;
        case gl_debug_type::UNDEFINED_BEHAVIOR: _type_str = "UNDEFINED_BEHAVIOR";
            break;
        case gl_debug_type::ERROR: _type_str = "ERROR";
            break;
        case gl_debug_type::MARKER: _type_str = "MARKER";
            break;
        case gl_debug_type::OTHER: _type_str = "OTHER";
            break;
        case gl_debug_type::PERFORMANCE: _type_str = "PERFORMANCE";
            break;
        case gl_debug_type::POP_GROUP: _type_str = "POP_GROUP";
            break;
        case gl_debug_type::PORTABILITY: _type_str = "PORTABILITY";
            break;
        case gl_debug_type::PUSH_GROUP: _type_str = "PUSH_GROUP";
            break;
    }

    switch (_severity) {

        case gl_debug_severity::SEVERITY_HIGH: _severity_str = "SEVERITY_HIGH";
            break;
        case gl_debug_severity::SEVERITY_LOW: _severity_str = "SEVERITY_LOW";
            break;
        case gl_debug_severity::SEVERITY_MEDIUM: _severity_str = "SEVERITY_MEDIUM";
            break;
        case gl_debug_severity::SEVERITY_NOTIFICATION: _severity_str = "SEVERITY_NOTIFICATION";
            break;
    }

    std::string _message_str(message, length);

    std::cerr<<"["<<std::endl;
    std::cerr<<"  DEBUG SOURCE: "<< _source_str << std::endl;
    std::cerr<<"  DEBUG TYPE: "<< _type_str << std::endl;
    std::cerr<<"  DEBUG ID: "<< id << std::endl;
    std::cerr<<"  DEBUG SEVERITY: "<< _severity_str << std::endl;
    std::cerr<<"  DEBUG MESSAGE: "<< _message_str << std::endl;
    std::cerr<<"]"<<std::endl;

}



void _create(std::string name) {
	std::cout << name << std::endl;
}

void _create(glm::vec3 a) {
	std::cout << a.x << a.y << a.z << std::endl;
}

void _create(int32_t a) {
	std::cout << a << std::endl;
}

void create() {
	std::cout << "null" << std::endl;
}

template<typename T, typename... Args>
void create(T v, Args... args)
{
	struct MATR{} a;
	_create(v);
	create(args...);
}


#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"

void test0()
{
//	lua_manager _lua_mana;
//	_lua_mana.construct();

	auto* window = new glfw_window();
	window->load_context();
	
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
	glewInit();
	glViewport(0, 0, window->get_framebuffer_width(), window->get_framebuffer_height());
    // During init, enable debug output
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
#endif // _DEBUG



	// vetex launcher
	// vertices
	auto _vertices = std::make_shared<gl_vertex_array>();
	_vertices->reallocate_vertex_attributes(100);
	std::vector<glm::vec4> _raw_colors;
	// indices
	auto _indices = std::make_shared<gl_element_array_buffer>();
	_indices->reallocate(1024 * sizeof(std::uint32_t));
	_indices->fill(nullptr);

	auto _vertex_launcher = std::make_shared<gl_vertex_launcher>();
	_vertex_launcher->vertices = _vertices;
	_vertex_launcher->indices = _indices;
	_vertex_launcher->assembly();

	// shader program
	auto _vs = std::make_shared<glsl_vertex_shader>();
	auto _ts = std::make_shared<glsl_tessellation_shader>();
	auto _gs = std::make_shared<glsl_geometry_shader>();
	auto _fs = std::make_shared<glsl_fragment_shader>();

	auto _program = std::make_shared<glsl_graphics_pipeline_program>(_vs, _ts, _gs, _fs);
	
	// framebuffer
	auto _framebuffer = std::make_shared<gl_framebuffer>();

	// state
	auto _state = std::make_shared<gl_graphics_pipeline_state>();
	_state->vertex_processing.post_vertex_processing.primitive_clipping.clip_control_depth_mode;
	_state->vertex_assembly.primitive_restart.enabled;
	_state->primitive_assembly.discard_all_primitives = false;
	_state->fragment_processing.pre_fragment_operations.scissor_test.enabled = true;
	_state->fragment_processing.post_fragment_operations.blending;

	// pipeline
	auto  _gp_des = std::make_shared<gl_graphics_pipeline_descriptor>();
	_gp_des->name = "test_pipeline";
	_gp_des->owner_renderer_dir = "/shaders/test_renderer/";
	_gp_des->vertex_launcher = _vertex_launcher;
	_gp_des->program = _program;
	_gp_des->transform_feedback = nullptr;
	_gp_des->framebuffer = _framebuffer;
	_gp_des->state = _state;
	
	auto _test_pipeline = std::make_shared<gl_graphics_pipeline>(_gp_des);

	_test_pipeline->enable();
	//_test_pipeline->draw_indices();
	//_test_pipeline->draw_arrays();
	_test_pipeline->disable();






	gl_buffer_storage_options _options;
	_options.is_client_storage = false; // backing storage in client or server, server will be more fast
	_options.is_dynamic_storage = false; // allow client directly send data to gpu
	_options.is_map_read = true; // allow mapfunc read
	_options.is_map_write = true; // allow mapfunc write
	_options.is_map_coherent = false;
	_options.is_map_persistent = false;

	const std::int64_t _size = sizeof(glsl_vec4) * 10;
	gl_buffer _buffer{ _options, _size };

	_buffer.execute_mapped_memory_writer(0, _size, [](std::uint8_t* data, std::int64_t size) {
		glm::vec4* _data = reinterpret_cast<glm::vec4*>(data);
		std::int64_t _size = size / sizeof(glm::vec4);
		if (!data || size < 0) return;

		for (std::int32_t _idx = 0; _idx < _size; ++_idx)
		{
			std::cout << "add" << std::endl;
			_data[_idx] = glm::vec4(1.0f, 1.2f, 1.3f,1.11f);
		}
		});

	glm::vec4 a(0.0f);
	//_buffer.write(0, reinterpret_cast<const std::uint8_t*>(&a), sizeof glm::vec4);
	//_buffer.read(0, sizeof(glm::vec4), &a);
	//std::cout << "direct get: " << a.x << ", " << a.y << ", " << a.z << ", " << a.w << std::endl;

	_buffer.execute_mapped_memory_reader(0, _size, [](const std::uint8_t* data, std::int64_t size) {
		const glm::vec4* _data = reinterpret_cast<const glm::vec4*>(data);
		std::int64_t _size = size / sizeof(glm::vec4);
		if (!data || size < 0) return;

		for (std::int32_t _idx = 0; _idx < _size; ++_idx)
		{
			std::cout << _data[_idx].x << ", " << _data[_idx].y << ", " << _data[_idx].z << ", " << _data[_idx].w << std::endl;
		}
		});


//	std::vector<glv::f32vec3> positions{
//		glv::f32vec3(0.5f, 0.5f, 0.0f), //0
//		glv::f32vec3(0.5f, -0.5f, 0.0f), //1
//		glv::f32vec3(-0.5f, -0.5f, 0.0f), //2
//		glv::f32vec3(-0.5f, 0.5f, 0.0f) //3
//	};
//
//	std::vector<glv::f32vec2> uvs{
//		glv::f32vec2(1.0f, 1.0f),
//		glv::f32vec2(1.0f, 0.0f),
//		glv::f32vec2(0.0f, 0.0f),
//		glv::f32vec2(0.0f, 1.0f)
//	};
//
//	std::vector<glm::i16vec4> tests{
//		glm::i16vec4(1, 0, 0, 1),
//		glm::i16vec4(0, 1, 0, 1),
//		glm::i16vec4(0, 0, 1, 1),
//		glm::i16vec4(0, 1, 0, 1)
//	};

	std::vector<glm::uint32> indices{
		0, 1, 3, // polygon0
		1, 2, 3 // polygon1
	};


	// uniforms
	// textures

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
	//glFrontFace(GL_CW);//default ��ʱ�� GL_CW ˳ʱ��

	//glEnable(GL_COLOR_BUFFER_BIT);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glEnable(GL_ACCUM_BUFFER_BIT);
	//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);

	// when current frag-z < 1.0, keep it
	// fragShader write its z value before working
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glDepthMask(GL_TRUE);
	//glClearDepth(1.0f);

	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glStencilMask(GL_TRUE);
	//glClearStencil(0);



	int i = 10;

	while (i--)
	{
		
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		
		window->tick(0.0f);

//		if(i%2 == 0)
//        {
//            _va->update_attribute("position", 2, v0);
//        }else{
//            _va->update_attribute("position", 2, v2);
//		}
//
//		_va->set_vertices_count(3);



		/*ubod->clear_uniforms();
		ubod->add_uniforms({
			create_uniform("color", glu_f32vec4(w, 0.0f, 0.0f, 1.0f)),
			create_uniform("pos", glu_f32vec3(0.0f, 0.0f, 0.0f)),
			create_uniform("text", glu_f32vec4(0.0f, 0.0f, 0.0f, 1.0f))
			});
		w += 0.001f;*/
	}
}
//
//void test1()
//{
//	glfw_window* window = new glfw_window();
//	window->load_context();
//
//	glewInit();
//
//
//	/*auto ubod = std::make_shared<gl_uniform_buffer_descriptor>();
//
//	ubod->add_uniform(glm::vec4(0.0f, 1.0f, 0.5f, 0.0f));
//	ubod->add_uniform(glm::vec3(1.2f, 1.6f, 0.7f));
//	ubod->add_uniform(glm::mat4(0.0f));*/
//
//
//	//std::uint8_t* data = (std::uint8_t*)ubod->get_data();
//	//
//	//glm::vec3* d = (glm::vec3*)(data + 16);
//
//	/*const void* _data = vao->get_mapped_data();
//	const glv_vec3* _dv = (glv_vec3*)_data;
//	for (int i = 0; i < 36; ++i)
//	{
//		std::cout << _dv[i].r << "," << _dv[i].g << "," << _dv[i].b << std::endl;
//	}*/
//
//
//	//std::cout << "size :" << vao->get_attribute_components_num(0) << std::endl;
//	//std::cout << "size :" << vao->get_attribute_components_num(1) << std::endl;
//	//std::cout << "size :" << vao->get_attribute_components_num(2) << std::endl;
//
//
//	// camera / view_matrix/ camera_position
//	auto camera = std::make_shared<gl_camera>();
//
//	// model_matrix
//	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
//	float Pitch, Yaw, Roll;
//	Pitch = Yaw = Roll = 0.0f;
//	glm::mat4 model_mat(1.0f);
//	model_mat = glm::translate(model_mat, Position);
//	model_mat = glm::rotate(model_mat, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
//	model_mat = glm::rotate(model_mat, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
//	model_mat = glm::rotate(model_mat, glm::radians(Roll), glm::vec3(0.0f, 0.0f, 1.0f));
//	// projection_matrix
//	glm::mat4 proj_matrix
//		= glm::perspective(glm::radians(45.0f),
//			(float)window->get_framebuffer_width() / (float)window->get_framebuffer_height(),
//			0.1f, 40.0f);
//
//
//	// uniforms
//	auto camera_position
//		= std::make_shared<gl_variable<glv_vec3>>("camera_position", camera->get_position());
//	auto projection_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("projection_matrix", proj_matrix);
//	auto model_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("model_matrix", model_mat);
//	auto view_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("view_matirx", camera->get_view_matrix());
//
//	auto ambient_light
//		= std::make_shared<gl_variable<glv_vec3>>("en_lights.ambient_light", glv_vec3());
//
//	auto directional_light
//		= std::make_shared<gl_variable<glv_vec3>>("en_lights.directional_light[0]", glv_vec3());
//
//	/*auto directional_lights_num = std::make_shared< gl_variable<glv_int>>();
//
//	auto point_light = std::make_shared< gl_variable<glv_vec3>>();
//	auto point_lights_num = std::make_shared< gl_variable<glv_int>>();
//
//	auto spot_light = std::make_shared< gl_variable<glv_vec3>>();
//	auto spot_lights_num = std::make_shared< gl_variable<glv_int>>();*/
//
//	// textures
//	auto container2 = std::make_shared<gl_texture_2d>();
//	auto albedo_map = std::make_shared<gl_texture_2d>();
//	auto normal_map = std::make_shared<gl_texture_2d>();
//	//auto metalness_map = std::make_shared<gl_texture_2d>();
//	auto roughness_map = std::make_shared<gl_texture_2d>();
//	auto displacement_map = std::make_shared<gl_texture_2d>();
//	auto ambient_occlusion_map = std::make_shared<gl_texture_2d>();
//
//	/*gl_texture_pixels container2_pixels("assets/Textures/container2.png");
//	container2->fill(container2_pixels.width, container2_pixels.height, container2_pixels.format, (const void*)container2_pixels.pixels);
//	container2->set_name("container2");*/
//
//	gl_texture_pixels albedo_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Color.jpg");
//	albedo_map->fill(albedo_pixels.width, albedo_pixels.height, albedo_pixels.format, (const void*)albedo_pixels.pixels);
//	albedo_map->set_name("mat.albedo_map");
//
//	gl_texture_pixels normal_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Normal.jpg");
//	normal_map->fill(normal_pixels.width, normal_pixels.height, normal_pixels.format, (const void*)normal_pixels.pixels);
//	normal_map->set_name("mat.normal_map");
//
//	/*gl_texture_pixels metalness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_.jpg");
//	metalness_map->fill(metalness_pixels.width, metalness_pixels.height, (const void*)metalness_pixels.pixels);
//	metalness_map->set_name("mat.metalness_map");*/
//
//	gl_texture_pixels roughness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Roughness.jpg");
//	roughness_map->fill(roughness_pixels.width, roughness_pixels.height, roughness_pixels.format, (const void*)roughness_pixels.pixels);
//	roughness_map->set_name("mat.roughness_map");
//
//	gl_texture_pixels displacement_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Displacement.jpg");
//	displacement_map->fill(displacement_pixels.width, displacement_pixels.height, displacement_pixels.format, (const void*)displacement_pixels.pixels);
//	displacement_map->set_name("mat.displacement_map");
//
//	gl_texture_pixels ambient_occlusion_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_AmbientOcclusion.jpg");
//	ambient_occlusion_map->fill(ambient_occlusion_pixels.width, ambient_occlusion_pixels.height, ambient_occlusion_pixels.format, (const void*)ambient_occlusion_pixels.pixels);
//	ambient_occlusion_map->set_name("mat.ambient_occlusion_map");
//
//
//	glViewport(0, 0, window->get_framebuffer_width(), window->get_framebuffer_height());
//
//	/*std::vector<glv_vec3> poss{
//		glv_vec3(0.5f, 0.5f, 0.0f),
//		glv_vec3(0.5f, -0.5f, 0.0f),
//		glv_vec3(-0.5f, -0.5f, 0.0f),
//		glv_vec3(-0.5f, 0.5f, 0.0f)
//	};
//
//	std::vector<glv_vec2> uvss{
//		glv_vec2(1.0f, 1.0f),
//		glv_vec2(1.0f, 0.0f),
//		glv_vec2(0.0f, 0.0f),
//		glv_vec2(0.0f, 1.0f)
//	};
//
//	std::vector<glm::uint32> indices{
//		0, 1, 3,
//		1, 2, 3
//	};*/
//
//	std::size_t size = positions.size();
//
//	// vertex array
//	auto vaod = sptr(gl_vertex_array_descriptor);
//	//vaod->add_attributes<glv_vec3>(poss);
//	//vaod->add_attributes<glv_vec2>(uvss);
//	vaod->add_attributes<glv_vec3>(positions);
//	vaod->add_attributes<glv_vec2>(uvs);
//	vaod->add_attributes<glv_vec3>(normals);
//	auto vao = sp_vertex_array(vaod);
//
//	// element array
//	/*auto ebod = std::make_shared<gl_element_array_buffer_descriptor>();
//	ebod->set_indices(indices);
//	auto ebo = std::make_shared<gl_element_array_buffer>();
//	ebo->fill(ebod);*/
//
//	// program
//	auto program = std::make_shared<gl_program>();
//	/*program->construct({
//		"shaders/test.vert",
//		"shaders/test.frag" });*/
//	program->construct({
//		"shaders/Mesh/PBRMesh/PBRMesh.vert",
//		"shaders/Mesh/PBRMesh/PBRMesh.tesc",
//		"shaders/Mesh/PBRMesh/PBRMesh.tese",
//		"shaders/Mesh/PBRMesh/PBRMesh.geom",
//		"shaders/Mesh/PBRMesh/PBRMesh.frag" });
//	// ...
//	program->set_vertex_array(vao);
//	// ...
//	program->add_texture(albedo_map);
//	program->add_texture(normal_map);
//	program->add_texture(roughness_map);
//	program->add_texture(displacement_map);
//	program->add_texture(ambient_occlusion_map);
//	// ...
//	program->add_uniform(camera_position);
//	program->add_uniform(projection_matrix);
//	program->add_uniform(view_matrix);
//	program->add_uniform(model_matrix);
//	// ...
//	program->set_framebuffer();
//	program->set_commands([&size] {
//		//glDrawArrays(GL_TRIANGLES, 0, 5);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glPatchParameteri(GL_PATCH_VERTICES, 3);
//		glDrawArraysInstancedBaseInstance(GL_PATCHES, 0, size, 1, 0);
//		});
//
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
//	//glFrontFace(GL_CW);//default ��ʱ�� GL_CW ˳ʱ��
//
//	//glEnable(GL_COLOR_BUFFER_BIT);
//	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//
//	//glEnable(GL_ACCUM_BUFFER_BIT);
//	//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);
//
//	// when current frag-z < 1.0, keep it
//	// fragShader write its z value before working
//	//glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//	//glDepthMask(GL_TRUE);
//	//glClearDepth(1.0f);
//
//	//glEnable(GL_STENCIL_TEST);
//	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
//	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//	//glStencilMask(GL_TRUE);
//	//glClearStencil(0);
//
//
//
//	int i = 1;
//	while (i--)
//	{
//
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT);
//		program->render(0.0f);
//		window->tick(0.0f);
//	}
//}
