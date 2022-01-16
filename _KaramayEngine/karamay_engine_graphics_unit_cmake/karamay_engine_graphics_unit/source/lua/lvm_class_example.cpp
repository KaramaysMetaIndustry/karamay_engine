#include "lvm_class_example.h"
#include "lvm.h"
#include "graphics/renderer/pipeline/gl_graphics_pipeline.h"
#include "graphics/renderer/pipeline/gl_compute_pipeline.h"
#include "graphics/renderer/pipeline/gl_mesh_pipeline.h"

namespace CTest_for_lua
{
	static int construct(lua_State* L)
	{
		CTest** ppTest = (CTest**)lua_newuserdata(L, sizeof(CTest*)); // -1
		auto pTest = new CTest;
		*ppTest = pTest;

		luaL_getmetatable(L, "CTest_clazz"); // -1 ; userdata -2
		lua_setmetatable(L, -2);  // set -1 as -2 's metatable
		return 1;
	}

	static int getA(lua_State* L)
	{
		auto ppTest = lua_api::get_cpp_instance<CTest>(L, 1, "CTest_clazz");
		if (!ppTest)
		{
			luaL_argcheck(L, false, 1, "invalid user data");
			return 0;
		}
		lua_api::origin::push_integer(L, ppTest->getA());
		return 1;
	}

	static int setA(lua_State* L)
	{
		auto _params_num = lua_api::origin::get_stack_top_index(L);
		if (_params_num < 2)
		{
#ifdef _DEBUG
			std::cerr << __FUNCTION__ << " : Invalid parameters" << std::endl;
#endif
			return 0;
		}

		auto ppTest = lua_api::get_cpp_instance<CTest>(L, 1, "CTest_clazz");

		if (!ppTest)
		{
			luaL_argcheck(L, false, 1, "invalid user data");
			return 0;
		}

		auto a = lua_api::origin::get_integer<int32>(L, 2);
		ppTest->setA(a);

		return 1;
	}

	static int finishNewCTest(lua_State* L)
	{
		int32 _params_num = lua_gettop(L) - 1;
		if (_params_num != 1) return 0;

		CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "CTest_clazz");
		luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

		if (_params_num == 1)
		{
			auto test = lua_api::get_cpp_instance<CTest>(L, 2);
			CTest* pResult = (*ppTest)->finishNewCTest(test); 
			lua_api::origin::push_light_userdata(L, pResult);
		}
		if (_params_num == 2)
		{
			auto test = lua_api::get_cpp_instance<CTest>(L, 2);
			auto i = lua_api::origin::get_integer<int32>(L, 3);
			CTest* pResult = (*ppTest)->finishNewCTest(test, i);
			lua_api::origin::push_light_userdata(L, pResult);
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
		auto _pipeline = new gl_graphics_pipeline(nullptr);
		lua_api::origin::push_light_userdata(L, _pipeline);
		lua_api::origin::get_metatable(L, "gl_graphics_pipeline_clazz");
		lua_api::origin::set_metatable(L, -2);
		return 1;
	}

	static int load(lua_State* L)
	{

		return 1;
	}

	static int enable(lua_State* L)
	{
		gl_graphics_pipeline** _pp_gp = (gl_graphics_pipeline**)luaL_checkudata(L, 1, "gl_renderer_clazz");
		luaL_argcheck(L, _pp_gp != nullptr, 1, "invalid user data");
		if (_pp_gp)
		{
			(*_pp_gp)->enable();
		}
		return 1;
	}

	static int disable(lua_State* L)
	{
		gl_graphics_pipeline** _pp_gp = (gl_graphics_pipeline**)luaL_checkudata(L, 1, "gl_renderer_clazz");
		luaL_argcheck(L, _pp_gp != nullptr, 1, "invalid user data");
		if (_pp_gp)
		{
			(*_pp_gp)->disable();
		}
		return 1;
	}

	static int syncable_draw_arrays(lua_State* L)
	{
		auto _args_num = lua_api::origin::get_stack_top_index(L);
		if (_args_num != 3 || _args_num !=5)
		{
			return 0;
		}

		auto _pipeline = lua_api::get_cpp_instance<gl_graphics_pipeline>(L, 1, "gl_graphics_pipeline_clazz");
		if (!_pipeline)
		{
			return 0;
		}
		
		if (_args_num == 3)
		{
			_pipeline->syncable_draw_arrays(
				lua_api::origin::get_integer<uint32>(L, 2),
				lua_api::origin::get_integer<uint32>(L, 3)
			);
		}
		if (_args_num == 5)
		{
			_pipeline->syncable_draw_arrays(
				lua_api::origin::get_integer<uint32>(L, 2),
				lua_api::origin::get_integer<uint32>(L, 3),
				lua_api::origin::get_integer<uint32>(L, 4),
				lua_api::origin::get_integer<uint32>(L, 5)
			);
		}

		return 1;
	}

	LUA_FUNCS_B()
		__CALL(__call)
		FUNC("load", load)
		FUNC("enbale", enable)
		FUNC("disable", disable)
		FUNC("syncable_draw_arrays", syncable_draw_arrays)
	LUA_FUNCS_E()
	
	IMPLEMENT_EXPORTER(gl_graphics_pipeline)
}

namespace gl_compute_pipeline_for_lua
{
	static int construct(lua_State* L)
	{
		auto _pipeline = new gl_compute_pipeline(nullptr);
		lua_api::origin::push_light_userdata(L, _pipeline);
		lua_api::origin::get_metatable(L, "gl_compute_pipeline_clazz");
		lua_api::origin::set_metatable(L, -2);
		return 1;
	}

	static int load(lua_State* L)
	{
		auto _num = lua_api::origin::get_stack_top_index(L);
		if (_num < 2)
		{
			return 0;
		}

		auto _comp_pipeline = lua_api::get_cpp_instance<gl_compute_pipeline>(L, 1);
		if (!_comp_pipeline)
		{
			return 0;
		}

		auto _pipeline_dir = lua_api::origin::get_string(L, 2);
		lua_api::origin::push_boolean(L, _comp_pipeline->load(_pipeline_dir));
		return 1;
	}

	static int enable(lua_State* L)
	{
		auto _num = lua_api::origin::get_stack_top_index(L);
		if (_num < 1)
		{
			return 0;
		}

		auto _comp_pipeline = lua_api::get_cpp_instance<gl_compute_pipeline>(L, 1);
		if (!_comp_pipeline)
		{
			return 0;
		}
		_comp_pipeline->enable();

		return 1;
	}

	static int disable(lua_State* L)
	{
		auto _num = lua_api::origin::get_stack_top_index(L);
		if (_num < 1)
		{
			return 0;
		}

		auto _comp_pipeline =lua_api::get_cpp_instance<gl_compute_pipeline>(L, 1);
		if (!_comp_pipeline)
		{
			return 0;
		}
		_comp_pipeline->disable();

		return 1;
	}

	static int dispatch(lua_State* L)
	{
		auto _num = lua_api::origin::get_stack_top_index(L);
		if (_num < 4)
		{
			return 0;
		}

		auto _comp_pipeline = lua_api::get_cpp_instance<gl_compute_pipeline>(L, 1);
		if (!_comp_pipeline)
		{
			return 0;
		}

		auto _x = lua_api::origin::get_integer<uint32>(L, 2);
		auto _y = lua_api::origin::get_integer<uint32>(L, 3);
		auto _z = lua_api::origin::get_integer<uint32>(L, 4);

		_comp_pipeline->dispatch(_x, _y, _z);

		return 1;
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
