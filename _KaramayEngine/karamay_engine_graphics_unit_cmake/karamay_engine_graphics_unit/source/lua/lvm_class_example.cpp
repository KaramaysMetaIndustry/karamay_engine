#include "lvm_class_example.h"
#include "lvm.h"
#include "graphics/renderer/gl_renderer.h"
#include "graphics/renderer/pipeline/gl_graphics_pipeline.h"
#include "graphics/renderer/pipeline/gl_compute_pipeline.h"
#include "graphics/renderer/pipeline/gl_mesh_pipeline.h"
#include "renderers/gl_static_mesh_renderer.h"

namespace CTest_for_lua
{
	// In order to communicate properly with Lua, a C function must use the following protocol, which defines the way parameters and results are passed: 
	// a C function receives its arguments from Lua in its stack in direct order (the first argument is pushed first). 
	//So, when the function starts, lua_gettop(L) returns the number of arguments received by the function. 
	// The first argument (if any) is at index 1 and its last argument is at index lua_gettop(L).
	// To return values to Lua, a C function just pushes them onto the stack, in direct order (the first result is pushed first), and returns in C the number of results. 
	// Any other value in the stack below the results will be properly discarded by Lua. Like a Lua function, a C function called by Lua can also return many results.
	static int __call(lua_State* L)
	{
		// stack : self
		int32 _num = lua_api::basic::top_index(L);
		/*if (_num != 0)
		{
			return 0;
		}*/
		CTest* test = new CTest();
		lua_api::basic::push_light_userdata(L, test);
		// stack : userdata, self
		lua_api::auxiliary::set_metatable(L, "CTest_clazz");
		return 1;
	}

	static int get(lua_State* L)
	{
		// stack : userdata
		auto _num = lua_api::basic::top_index(L);
		if (_num != 1)
		{
			return 0;
		}
		auto ppTest = (CTest*)lua_api::to_cpp_instance(L, 1, "CTest_clazz");
		lua_api::basic::push_integer(L, ppTest->getA());
		// stack : integer, lightuserdata
		return 1;
	}

	static int set(lua_State* L)
	{
		// stack : integer, userdata
		auto _num = lua_api::basic::top_index(L);
		if (_num < 2)
		{
#ifdef _DEBUG
			std::cerr << __FUNCTION__ << " : Invalid parameters" << std::endl;
#endif
			return 0;
		}
		auto ppTest = (CTest*)lua_api::to_cpp_instance(L, 1, "CTest_clazz");
		auto a = lua_api::basic::to_integer<int32>(L, 2);
		ppTest->setA(a);
		return 0;
	}

	static int finish(lua_State* L)
	{
		// stack : userdata, userdata
		// stack : integer, userdata, userdata
		int32 _num = lua_gettop(L);
	
		auto test = (CTest*)lua_api::to_cpp_instance(L, 1, "CTest_clazz");
		if (_num == 2)
		{
			auto testParam = (CTest*)lua_api::to_cpp_instance(L, 2, "CTest_clazz");
			auto testReturn = test->finishNewCTest(testParam);
			lua_api::basic::push_light_userdata(L, testReturn);
			// stack : userdata, userdata, userdata
		}
		if (_num == 3)
		{
			auto test = (CTest*)lua_api::to_cpp_instance(L, 2);
			auto i = lua_api::basic::to_integer<int32>(L, 3);
			auto testReturn = test->finishNewCTest(test, i);
			lua_api::basic::push_light_userdata(L, testReturn);
			// stack : userdata, integer, userdata, userdata
		}
		return 1;
	}

	LUA_LIBS_B()
		
	LUA_LIBS_E()

	LUA_FUNCS_B()
		__CALL()
		FUNC(get)
		FUNC(set)
		FUNC(finish)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(CTest)
};


namespace glsl_vertex_shader_for_lua
{

}

namespace glsl_tessellation_control_shader_for_lua
{

}

namespace glsl_tessellation_evaluation_shader_for_lua
{

}

namespace glsl_geometry_shader_for_lua
{

}

namespace glsl_fragment_shader_for_lua
{

}

namespace glsl_graphics_pipeline_program_for_lua
{

	static int __call(lua_State* l)
	{
		// stack : 
		auto _num = lua_api::basic::top_index(l);

		return 1;
	}



	LUA_FUNCS_B()
		__CALL()
	LUA_FUNCS_E()

}

namespace glsl_compute_shader_for_lua
{

}

namespace glsl_compute_pipeline_program_for_lua
{

}

namespace glsl_mesh_pipeline_program_for_lua
{

}

namespace gl_graphics_pipline_for_lua
{
	static int __call(lua_State* l)
	{
		// stack : userdata
		auto _num = lua_api::basic::top_index(l);
		if (_num != 1)
		{
			return 0;
		}
		auto _program = (glsl_graphics_pipeline_program*)lua_api::to_cpp_instance(l, 1, "glsl_graphics_pipeline_program");
		if (!_program)
		{
			return 0;
		}
		auto _pipeline = new gl_graphics_pipeline(_program);
		if (!_pipeline)
		{
			return 0;
		}
		lua_api::basic::push_light_userdata(l, _pipeline);
		// stack : (userdata), userdata
		lua_api::auxiliary::set_metatable(l, "gl_graphics_pipeline_clazz");
		return 1;
	}


	static int load(lua_State* l)
	{
		// stack : string, userdata
		auto _num = lua_api::basic::top_index(l);
		if (_num != 2)
		{
			return 0;
		}
		
		auto _pipeline = (gl_graphics_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_graphics_pipeline");
		if (!_pipeline)
		{
			return 0;
		}
		auto _pipeline_dir = lua_api::basic::to_string(l, 2);
		auto _result = _pipeline->load(_pipeline_dir);
		lua_api::basic::push_boolean(l, _result);
		// stack : (boolean), string, userdata
		return 1;
	}

	static int enable(lua_State* l)
	{
		// stack : userdata
		int32 _num = lua_api::basic::top_index(l);
		if (_num != 1)
		{
			return 0;
		}
		auto _pipeline = (gl_graphics_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_graphics_pipeline_clazz");
		_pipeline->enable();
		return 0;
	}

	static int disable(lua_State* l)
	{
		// stack : userdata
		int32 _num = lua_api::basic::top_index(l);
		auto _pipeline = (gl_graphics_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline)
		{
			return 0;
		}
		_pipeline->disable();
		return 0;
	}

	static int syncable_draw_arrays(lua_State* L)
	{
		// integer, integer, userdata
		// integer, integer, integer, integer, userdata
		int32 _num = lua_api::basic::top_index(L);
		if (_num < 3)
		{
			return 0;
		}
		auto _pipeline = (gl_graphics_pipeline*)lua_api::to_cpp_instance(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline)
		{
			return 0;
		}

		if (_num == 3)
		{
			auto _fence = _pipeline->syncable_draw_arrays(
				lua_api::basic::to_integer<uint32>(L, 2),
				lua_api::basic::to_integer<uint32>(L, 3)
			);
			//lua_api::origin::push_light_userdata(L, nullptr);
		}
		if (_num == 5)
		{
			auto _fence = _pipeline->syncable_draw_arrays(
				lua_api::basic::to_integer<uint32>(L, 2),
				lua_api::basic::to_integer<uint32>(L, 3),
				lua_api::basic::to_integer<uint32>(L, 4),
				lua_api::basic::to_integer<uint32>(L, 5)
			);
			//lua_api::origin::push_light_userdata(L, nullptr);
		}

		return 1;
	}

	static int unsyncable_draw_arrays(lua_State* L)
	{
		// integer, integer, userdata
		// integer, integer, integer, integer, userdata
		int32 _num = lua_api::basic::top_index(L); // index : 2+1 or 4+1
		auto _pipeline = (gl_graphics_pipeline*)lua_api::to_cpp_instance(L, 1, "gl_graphics_pipeline_clazz");
		if (_num == 3)
		{
			_pipeline->unsyncable_draw_arrays(
				lua_api::basic::to_integer<uint32>(L, 2),
				lua_api::basic::to_integer<uint32>(L, 3)
			);
		}
		if (_num == 5)
		{
			_pipeline->unsyncable_draw_arrays(
				lua_api::basic::to_integer<uint32>(L, 2),
				lua_api::basic::to_integer<uint32>(L, 3),
				lua_api::basic::to_integer<uint32>(L, 4),
				lua_api::basic::to_integer<uint32>(L, 5)
			);
		}
		return 0;
	}

	LUA_FUNCS_B()
		__CALL()
		FUNC(load)
		FUNC(enable)
		FUNC(disable)
		FUNC(syncable_draw_arrays)
		FUNC(unsyncable_draw_arrays)
	LUA_FUNCS_E()
	
	IMPLEMENT_EXPORTER(gl_graphics_pipeline)
}

namespace gl_compute_pipeline_for_lua
{
	static int __call(lua_State* l)
	{
		// stack : userdata
		auto _num = lua_api::basic::top_index(l);
		if (_num != 1)
		{
			return 0;
		}
		auto _program = (glsl_compute_pipeline_program*)lua_api::to_cpp_instance(l, 1, "glsl_compute_pipeline_program_clazz");
		auto _pipeline = new gl_compute_pipeline(_program);
		lua_api::basic::push_light_userdata(l, _pipeline);
		// stack : userdata, userdata
		lua_api::auxiliary::set_metatable(l, "gl_compute_pipeline_clazz");
		// stack : (userdata), userdata
		return 1;
	}


	static int load(lua_State* l)
	{
		// stack : string, userdata
		auto _num = lua_api::basic::top_index(l);
		if (_num != 2)
		{
			std::cerr << __FUNCTION__ << " invalid parameters" << std::endl;
			return 0;
		}
		auto _comp_pipeline = (gl_compute_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_compute_pipeline_clazz");
		auto _pipeline_dir = lua_api::basic::to_string(l, 2);
		auto _result = _comp_pipeline->load(_pipeline_dir);
		lua_api::basic::push_boolean(l, _result);
		// stack : (boolean), string, userdata
		return 1;
	}

	static int enable(lua_State* l)
	{
		// stack : userdata
		auto _num = lua_api::basic::top_index(l);
		auto _comp_pipeline = (gl_compute_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_compute_pipeline_clazz");
		_comp_pipeline->enable();
		return 0;
	}

	static int disable(lua_State* l)
	{
		// stack : userdata
		auto _num = lua_api::basic::top_index(l);
		auto _comp_pipeline = (gl_compute_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_compute_pipeline_clazz");
		_comp_pipeline->disable();
		return 0;
	}

	static int dispatch(lua_State* l)
	{
		// stack : integer, integer, integer, userdata
		auto _num = lua_api::basic::top_index(l);
		auto _comp_pipeline = (gl_compute_pipeline*)lua_api::to_cpp_instance(l, 1, "gl_compute_pipeline_clazz");
		auto _x = lua_api::basic::to_integer<uint32>(l, 2);
		auto _y = lua_api::basic::to_integer<uint32>(l, 3);
		auto _z = lua_api::basic::to_integer<uint32>(l, 4);
		_comp_pipeline->dispatch(_x, _y, _z);
		return 0;
	}

	LUA_FUNCS_B()
		__CALL()
		FUNC(load)
		FUNC(enable)
		FUNC(disable)
		FUNC(dispatch)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(gl_compute_pipeline)
}

namespace gl_mesh_pipeline_for_lua
{

}

namespace gl_renderer_for_lua
{
	static int __call(lua_State* l)
	{
		// stack : self
		auto _num = lua_api::basic::top_index(l);
		if (_num != 1)
		{
			return 0;
		}
		gl_renderer* _renderer = new gl_static_mesh_renderer();
		lua_api::basic::push_light_userdata(l, _renderer);
		// stack : userdata, self
		lua_api::auxiliary::set_metatable(l, "gl_renderer_clazz");
		return 1;
	}

	static int load(lua_State* l) 
	{
		// stack : userdata, string
		auto _num = lua_api::basic::top_index(l);
		if (_num != 2)
		{
			return 0;
		}
		auto s = lua_api::basic::to_string(l, 2);
		std::cout << "s : " << s << std::endl;
		lua_api::basic::push_boolean(l, true);
		return 1; 
	}

	LUA_FUNCS_B()
		__CALL()
		FUNC(load)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(gl_renderer)
}
