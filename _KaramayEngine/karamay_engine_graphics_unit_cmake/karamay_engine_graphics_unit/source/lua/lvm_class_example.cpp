#include "lvm_class_example.h"
#include "lvm.h"
#include "graphics/renderer/gl_renderer.h"
#include "graphics/renderer/pipeline/gl_graphics_pipeline.h"
#include "graphics/renderer/pipeline/gl_compute_pipeline.h"
#include "graphics/renderer/pipeline/gl_mesh_pipeline.h"

namespace CTest_for_lua
{
	// In order to communicate properly with Lua, a C function must use the following protocol, which defines the way parameters and results are passed: 
	// a C function receives its arguments from Lua in its stack in direct order (the first argument is pushed first). 
	//So, when the function starts, lua_gettop(L) returns the number of arguments received by the function. 
	// The first argument (if any) is at index 1 and its last argument is at index lua_gettop(L).
	// To return values to Lua, a C function just pushes them onto the stack, in direct order (the first result is pushed first), and returns in C the number of results. 
	// Any other value in the stack below the results will be properly discarded by Lua. Like a Lua function, a C function called by Lua can also return many results.
	static int construct(lua_State* L)
	{
		// stack : null
		int32 _num = lua_api::origin::stack_top_index(L); // index = 0
		CTest* test = new CTest();
		//lua_api::origin::new_userdata(L, test); // this creation will make lua take over its lifecycle
		lua_api::origin::push_light_userdata(L, test); // this creation you should manager its lifecycle
		// stack : lightuserdata
		lua_api::origin::get_metatable(L, "CTest_clazz");
		// stack : metatable, lightuserdata
		lua_api::origin::set_top_as_value_metatable(L, -2);
		// stack : (lightuserdata)
		return 1;
	}

	static int getA(lua_State* L)
	{
		// stack : lightuserdata
		auto _num = lua_api::origin::stack_top_index(L); // 1
		auto ppTest = lua_api::to_cpp_instance_with_validation<CTest>(L, 1, "CTest_clazz");
		lua_api::origin::push_integer(L, ppTest->getA());
		// stack : (integer), lightuserdata
		return 1;
	}

	static int setA(lua_State* L)
	{
		// stack : integer, lighteruserdata
		auto _num = lua_api::origin::stack_top_index(L); // 2
		if (_num < 2)
		{
#ifdef _DEBUG
			std::cerr << __FUNCTION__ << " : Invalid parameters" << std::endl;
#endif
			return 0;
		}
		auto ppTest = lua_api::to_cpp_instance_with_validation<CTest>(L, 1, "CTest_clazz");
		auto a = lua_api::origin::to_integer<int32>(L, 2);
		ppTest->setA(a);
		// stack : integer, lighteruserdata
		return 0;
	}

	static int finishNewCTest(lua_State* L)
	{
		// stack : userdata, userdata
		int32 _num = lua_gettop(L); // 2
		auto test = lua_api::to_cpp_instance_with_validation<CTest>(L, 1, "CTest_clazz");
		if (_num == 1)
		{
			auto testParam = lua_api::to_cpp_instance<CTest>(L, 2);
			auto testReturn = test->finishNewCTest(testParam);
			lua_api::origin::push_light_userdata(L, testReturn);
			// stack : (userdata), userdata, userdata
		}
		if (_num == 2)
		{
			auto test = lua_api::to_cpp_instance<CTest>(L, 2);
			auto i = lua_api::origin::to_integer<int32>(L, 3);
			auto testReturn = test->finishNewCTest(test, i);
			lua_api::origin::push_light_userdata(L, testReturn);
			// stack : (userdata), userdata, userdata
		}
		return 1;
	}

	LUA_LIBS_B()
		
	LUA_LIBS_E()

	LUA_FUNCS_B()
		__CALL(construct)
		FUNC("get", getA)
		FUNC("set", setA)
		FUNC("finish", finishNewCTest)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(CTest)
};

namespace gl_renderer_for_lua
{
	static int construct(lua_State* L)
	{
		// stack : null
		auto _num = lua_api::origin::stack_top_index(L); // index : 0

		gl_renderer* _renderer;
		lua_api::origin::push_light_userdata(L, _renderer);
		// stack : userdata
		return 1;
	}

	LUA_FUNCS_B()
		__CALL(construct)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(gl_renderer)
}

namespace gl_graphics_pipline_for_lua
{
	static int __call(lua_State* L)
	{
		// stack : null
		auto _num = lua_api::origin::stack_top_index(L); // index : 0
		auto _pipeline = new gl_graphics_pipeline(nullptr);
		lua_api::origin::push_light_userdata(L, _pipeline);
		// stack : lightuserdata
		lua_api::origin::get_metatable(L, "gl_graphics_pipeline_clazz");
		// stack : metatable, lightuserdata
		lua_api::origin::set_top_as_value_metatable(L, -2);
		// stack : lightuserdata
		return 1;
	}

	static int load(lua_State* L)
	{
		return 0;
	}

	static int enable(lua_State* L)
	{
		// stack : userdata
		int32 _num = lua_api::origin::stack_top_index(L); // index : 1
		auto _pipeline = lua_api::to_cpp_instance_with_validation<gl_graphics_pipeline>(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline) return 0;
		_pipeline->enable();
		return 0;
	}

	static int disable(lua_State* L)
	{
		// stack : userdata
		int32 _num = lua_api::origin::stack_top_index(L); // index : 1
		auto _pipeline = lua_api::to_cpp_instance_with_validation<gl_graphics_pipeline>(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline) return 0;
		_pipeline->disable();
		return 0;
	}

	static int syncable_draw_arrays(lua_State* L)
	{
		// stack : (2)/(4) userdata
		int32 _num = lua_api::origin::stack_top_index(L); // index : 4+1 or 2+1
		auto _pipeline = lua_api::to_cpp_instance_with_validation<gl_graphics_pipeline>(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline) return 0;

		if (_num == 3)
		{
			auto _fence = _pipeline->syncable_draw_arrays(
				lua_api::origin::to_integer<uint32>(L, 2),
				lua_api::origin::to_integer<uint32>(L, 3)
			);
			//lua_api::origin::push_light_userdata(L, nullptr);
		}
		if (_num == 5)
		{
			auto _fence = _pipeline->syncable_draw_arrays(
				lua_api::origin::to_integer<uint32>(L, 2),
				lua_api::origin::to_integer<uint32>(L, 3),
				lua_api::origin::to_integer<uint32>(L, 4),
				lua_api::origin::to_integer<uint32>(L, 5)
			);
			//lua_api::origin::push_light_userdata(L, nullptr);
		}

		return 1;
	}

	static int unsyncable_draw_arrays(lua_State* L)
	{
		// stack : (2)/(4) userdata
		int32 _num = lua_api::origin::stack_top_index(L); // index : 2+1 or 4+1
		auto _pipeline = lua_api::to_cpp_instance_with_validation<gl_graphics_pipeline>(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline) return 0;

		if (_num == 3)
		{
			_pipeline->unsyncable_draw_arrays(
				lua_api::origin::to_integer<uint32>(L, 2),
				lua_api::origin::to_integer<uint32>(L, 3)
			);
		}
		if (_num == 5)
		{
			_pipeline->unsyncable_draw_arrays(
				lua_api::origin::to_integer<uint32>(L, 2),
				lua_api::origin::to_integer<uint32>(L, 3),
				lua_api::origin::to_integer<uint32>(L, 4),
				lua_api::origin::to_integer<uint32>(L, 5)
			);
		}
		return 0;
	}

	LUA_FUNCS_B()
		__CALL(__call)
		FUNC("load", load)
		FUNC("enbale", enable)
		FUNC("disable", disable)
		FUNC("syncable_draw_arrays", syncable_draw_arrays)
		FUNC("unsyncable_draw_arrays", unsyncable_draw_arrays)
	LUA_FUNCS_E()
	
	IMPLEMENT_EXPORTER(gl_graphics_pipeline)
}

namespace gl_compute_pipeline_for_lua
{
	static int construct(lua_State* L)
	{
		// stack : null
		auto _pipeline = new gl_compute_pipeline(nullptr);
		lua_api::origin::push_light_userdata(L, _pipeline);
		// stack : userdata
		lua_api::origin::get_metatable(L, "gl_compute_pipeline_clazz");
		// stack : metatable, userdata 
		lua_api::origin::set_top_as_value_metatable(L, -2);
		// stack : userdata
		return 1;
	}

	static int load(lua_State* L)
	{
		// stack : string, userdata
		auto _num = lua_api::origin::stack_top_index(L); // index : 2
		auto _comp_pipeline = lua_api::to_cpp_instance<gl_compute_pipeline>(L, 1);
		auto _pipeline_dir = lua_api::origin::to_string(L, 2);
		auto _result = _comp_pipeline->load(_pipeline_dir);
		lua_api::origin::push_boolean(L, _result);
		// stack : (boolean), string, userdata
		return 1;
	}

	static int enable(lua_State* L)
	{
		// stack : userdata
		auto _num = lua_api::origin::stack_top_index(L); // index : 1
		auto _comp_pipeline = lua_api::to_cpp_instance<gl_compute_pipeline>(L, 1);
		_comp_pipeline->enable();
		return 0;
	}

	static int disable(lua_State* L)
	{
		// stack : userdata
		auto _num = lua_api::origin::stack_top_index(L); // index : 1
		auto _comp_pipeline =lua_api::to_cpp_instance<gl_compute_pipeline>(L, 1);
		_comp_pipeline->disable();
		return 0;
	}

	static int dispatch(lua_State* L)
	{
		// stack : integer, integer, integer, userdata
		auto _num = lua_api::origin::stack_top_index(L); // index : 4
		auto _comp_pipeline = lua_api::to_cpp_instance<gl_compute_pipeline>(L, 1);

		auto _x = lua_api::origin::to_integer<uint32>(L, 2);
		auto _y = lua_api::origin::to_integer<uint32>(L, 3);
		auto _z = lua_api::origin::to_integer<uint32>(L, 4);
		_comp_pipeline->dispatch(_x, _y, _z);

		return 0;
	}

	LUA_FUNCS_B()
		__CALL(construct)
		FUNC("load", load)
		FUNC("enable", enable)
		FUNC("disable", disable)
		FUNC("dispatch", dispatch)
	LUA_FUNCS_E()

	IMPLEMENT_EXPORTER(gl_compute_pipeline)
}

namespace gl_mesh_pipeline_for_lua
{

}
