#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include "public/_lua.h"

namespace karamay_lua
{
	lua_State* state() { return nullptr; }

	struct lua_index
	{
		explicit lua_index(std::int32_t index) : _index(index)
		{
			if (_index < 0 && _index > LUA_REGISTRYINDEX)
			{
				std::int32_t _top = lua_gettop(state());
				_index = _top + _index + 1;
			}
		}

		std::int32_t index() const { return _index; }

	protected:

		std::int32_t _index;
	};

	struct lua_t : lua_index
	{
		template <typename T>
		T value() const
		{

		}

		template <typename T>
		operator T() const;
	};

	struct lua_result
	{
		explicit lua_result(std::int32_t num)
		{
			std::string s;
			int n;
		}

		void pop() {}
		bool is_valid() const { return _valid; }
		std::int32_t num() const { return _values.size(); }

		const lua_t& operator[](std::int32_t index) const { return _values[index]; }

	private:

		std::vector<lua_t> _values;
		bool _valid;
	};

	struct lua_table : lua_index {
		explicit lua_table(std::int32_t);
		explicit lua_table(lua_t value);

		void reset();
		std::int32_t length() const {}

		lua_t operator[](std::int32_t i) const;
		lua_t operator[](std::int64_t i) const;
		lua_t operator[](std::double_t d) const;
		lua_t operator[](const char* s) const;
		lua_t operator[](const void* p) const;
		lua_t operator[](lua_index stack_index) const;
		lua_t operator[](lua_t key) const;

		template<class... T>
		lua_result call(const char* method_name, T&&... args) const
		{
			if (!method_name) {
				return lua_result(0);
			}

			auto* _state = karamay_lua::state();
			lua_pushcfunction(_state, report_lua_call_error);

			lua_pushstring(_state, method_name);
			std::int32_t _type = lua_gettable(_state, _index);
			if (_type != LUA_TFUNCTION)
			{
				std::cout << "method does not exist" << std::endl;
				lua_pop(_state, 2);
				return lua_result(0);
			}


		}

	private:

		mutable std::int32_t pushed_values;
	};

	template<typename... T>
	lua_result call_function_internal(lua_State* state, T&&... args)
	{
		std::int32_t _message_handler_index = lua_gettop(state) - 1;
		if (_message_handler_index > 0)
		{
			std::int32_t _args_num;
			std::int32_t _code = lua_pcall(state, _args_num, LUA_MULTRET, _message_handler_index);
			std::int32_t _top_index = lua_gettop(state);
			if (_code == LUA_OK)
			{
				std::int32_t _results_num = _top_index - _message_handler_index;
				lua_remove(state, _message_handler_index);
				return lua_result(_results_num);
			}
			lua_pop(state, _top_index - _message_handler_index + 1);
			return lua_result(0);
		}
	}

	lua_CFunction report_lua_call_error;


	struct lua_nil
	{

	};

	struct lua_function
	{

	};

	struct lua_boolean { bool value;  };

	struct lua_number {};

	struct lua_string {};


	struct lua_userdata {};

	struct lua_thread {};


	template<typename LUA_T>
	void push(const LUA_T& value) 
	{
		
	}

	void push_nil() 
	{
		lua_pushnil(state());
	}
	
	void push_boolean(bool value) 
	{
		lua_pushboolean(state(), static_cast<int>(value));
	}

	void push_number(std::int64_t value)
	{
		lua_pushinteger(state(), value);
	}

	void push_number(std::double_t value)
	{
		lua_pushnumber(state(), value);
	}

	void push_string(const std::string& value) 
	{
		lua_pushstring(state(), value.c_str());
		/*lua_pushlstring(state, value, length);
		lua_pushliteral(state, "");
		lua_pushfstring(state, format, 1);
		lua_pushvfstring(state, format, argp);*/
	}

	void push(const lua_function& value) 
	{
		//lua_pushcclosure(state, func, captured_vars_num);
		//lua_pushcfunction(state, func);
	}

	void push_userdata(void* value_ptr) 
	{
		lua_pushlightuserdata(state(), value_ptr);
	}

	std::int32_t push_thread() 
	{
		return lua_pushthread(state());
	}

	void push_table() 
	{
		lua_pushglobaltable(state());
	}

	void _push_value(int index)
	{
		lua_pushvalue(state(), index);
	}


	class CTest
	{
	public:
		CTest() 
		{
			value = 0;
		}
		~CTest() {}

		int getA() { return value; }
		void setA(int a) 
		{
			value = a;
		}

		CTest* finishNewCTest(CTest* test) {
			if (test)
			{
				test->setA(10);
			}
			return test;
		}
	private:
		int value;

};

int lua_construct(lua_State* L)
{
	CTest** ppTest = (CTest**)lua_newuserdata(L, sizeof(CTest*)); // -1
	*ppTest = new CTest;
	luaL_getmetatable(L, "gl_renderer_clazz"); // -1 ; userdata -2
	lua_setmetatable(L, -2);  // set -1 as -2 's metatable
	return 1;
}

int lua_getA(lua_State* L)
{
	CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
	luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");
	lua_pushnumber(L, (int)(*ppTest)->getA());
	return 1;
}

int lua_setA(lua_State* L)
{
	int args_num = lua_gettop(L);

	CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
	luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

	int a = (int)lua_tointeger(L, 2);
	(*ppTest)->setA(a);

	return 0;
}

template<typename T>
struct lua_type
{
	T value;
};

template<typename T>
void get_parameter(lua_State* l, int index, lua_type<T>& out)
{

}

template<typename T>
T* get_parameter(lua_State* l, int index)
{
	T** ppParam = (T**)lua_touserdata(l, index);
	luaL_argcheck(l, ppParam != NULL, index, "input val test, invalid user data");
	return ppParam;
}

int lua_finishNewCTest(lua_State* L)
{
	// get this pointer, param 1
	CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
	luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

	// get param 2
	CTest** ppParamTest = (CTest**)lua_touserdata(L, 2);
	luaL_argcheck(L, ppTest != NULL, 2, "input val test, invalid user data");
	
	// invoke
	(*ppTest)->finishNewCTest(*ppParamTest);

	return 0;
}

int desctroy(lua_State* L)
{
	CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
	delete* ppTest;
	printf("gl_renderer_clazz is deleted \n");
	return 0;
}


static const struct luaL_Reg libs[] =
{
	/*{"gl_renderer", CTest::lua_construct},*/
	{NULL, NULL},
};

static const struct luaL_Reg test_reg_mf[] =
{
	{"TestGetA", lua_getA},
	{"TestSetA",lua_setA},
	{"FinishTest", lua_finishNewCTest},
	{"__gc", desctroy},
	{"__call", lua_construct},
	{NULL, NULL},
};

	static int testModelOpen(lua_State* L)
	{
		luaL_newlib(L, libs);
		return 1;
	}

	void create_test_metatable(lua_State* L, const char* metatable_name, const luaL_Reg* regs)
	{
		luaL_newmetatable(L, metatable_name); // -1 table, push onto top
		lua_pushvalue(L, -1); // -1 table new -2 table old
		lua_setfield(L, -2, "__index"); // set -1 table to -2 table's __index -1 pop
		luaL_setfuncs(L, regs, 0); // set funcs to -1 table
		lua_pop(L, 1);
		
		lua_newtable(L);
		luaL_setmetatable(L, metatable_name);
		lua_setglobal(L, "gl_renderer");
	}

	void register_testModel_module(lua_State* L)
	{
		luaL_requiref(L, "karamay_RHI", testModelOpen, 0);
		create_test_metatable(L, "gl_renderer_clazz", test_reg_mf);

	}

	void load()
	{

		//lua_State* l = luaL_newstate();
		//if (!l)return 1;
		//luaL_openlibs(l);

		////C:\PrivateRepos\Karamays\_KaramayEngine\karamay_engine_graphics_unit_cmake\karamay_engine_graphics_unit\scripts\blue_freckle\Test.lua
		//int state = luaL_dofile(l, "C:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/scripts/blue_freckle/Test.lua");
		//// C:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/scripts/blue_freckle/Test.lua
		//switch (state)
		//{
		//case LUA_OK(0): std::cout << "no errors." << std::endl; break;
		//case LUA_ERRRUN: std::cout << "a runtime error." << std::endl;
		//case LUA_ERRMEM: std::cout << "memory allocation error.For such errors, Lua does not call the message handler." << std::endl; break;
		//case LUA_ERRERR: std::cout << "error while running the message handler." << std::endl; break;
		//case LUA_ERRSYNTAX: std::cout << "syntax error during precompilation." << std::endl; break;
		//case LUA_YIELD: std::cout << "the thread(coroutine) yields." << std::endl; break;
		//case LUA_ERRFILE: std::cout << "a file - related error; e.g., it cannot open or read the file." << std::endl; break;
		//default:
		//	break;
		//}

		lua_State* L = luaL_newstate();
		int top = 0;
		top = lua_gettop(L);

		// 打开指定标准库
		/*luaopen_base(L);
		luaopen_package(L); 
		luaopen_coroutine(L); 
		luaopen_string(L); 
		luaopen_utf8(L);
		luaopen_table(L);
		luaopen_math(L);
		luaopen_io(L);
		luaopen_os(L);
		luaopen_debug(L);*/
		
		// Opens all standard Lua libraries into the given state.
		luaL_openlibs(L);
		top = lua_gettop(L);
		register_testModel_module(L);

		int ret = luaL_dofile(L, "C:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/scripts/blue_freckle/Test.lua");
		if (ret != 0)
		{
			printf("%s", lua_tostring(L, -1));
		}

		lua_close(L);
	}

	

}


class lua_manager{
public:

	void construct() {
        state = luaL_newstate();
        int result = luaL_loadfile(state, "C:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\blue_freckle\\Test.lua");
        switch (result) {
            case LUA_OK: std::cout<<"load lua file success"<<std::endl; break;
            case LUA_ERRSYNTAX : std::cout<<"err syntax"<<std::endl;break;
            case LUA_ERRMEM : std::cout<<"err mem"<<std::endl;break;
            default: break;
        }

        lua_register(state, "aa", lua_CFunction());
    }

protected:

    void _push(std::int8_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::int16_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::int32_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::int64_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }

    void _push(std::uint8_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::uint16_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::uint32_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }
    void _push(std::uint64_t value)
    {
        lua_pushinteger(state, static_cast<lua_Integer>(value));
    }

    void _push(std::float_t value){ lua_pushnumber(state, value);}
    void _push(std::double_t value){ lua_pushnumber(state, value);}

    void _push(bool value){ lua_pushboolean(state, value);}

    void _push(char* value){ lua_pushstring(state, value);}
    void _push(const char* value){ lua_pushstring(state, value);}

    void _push(void* value){ lua_pushlightuserdata(state, value);}
    void _push(const void* value) {lua_pushlightuserdata(state, (void*)value);}

    //void _push()

	// about stack
	void _push_nil()
	{
		lua_pushnil(state);
	}
	void _push_boolean(bool value)
	{
		lua_pushboolean(state, static_cast<int>(value));
	}
	void _push_c_closure(lua_CFunction func, int captured_vars_num)
	{
		lua_pushcclosure(state, func, captured_vars_num);
	}
	void _push_c_function(lua_CFunction func)
	{
		lua_pushcfunction(state, func);
	}
	void _push_global_table()
	{
		lua_pushglobaltable(state);
	}
	void _push_integer(lua_Integer value)
	{
		lua_pushinteger(state, value);
	}
	void _push_number(lua_Number value)
	{
		lua_pushnumber(state, value);
	}
	const char* _push_string(const char* value)
	{
		return lua_pushstring(state, value);
	}
	const char* _push_string(const char* value, size_t length)
	{
		return lua_pushlstring(state, value, length);
	}
	const char* _push_literal(const char* value)
	{
		return lua_pushliteral(state, "");
	}
	const char* _push_format_string(const char* format, ...)
	{
		return lua_pushfstring(state, format, 1);
	}
	const char* _push_format_string(const char* format, va_list argp)
	{
		return lua_pushvfstring(state, format, argp);
	}
	int _push_thread()
	{
		return lua_pushthread(state);
	}
	void _push_value(int index)
	{
		lua_pushvalue(state, index);
	}
	void _push_light_userdata(void* data)
	{
		lua_pushlightuserdata(state, data);
	}

	void _pop(int num)
	{
		lua_pop(state, num);
	}

	lua_Alloc _get_allocf()
	{
		return lua_getallocf(state, nullptr);
	}
	void _get_field() 
	{
		lua_getfield(state, 0, nullptr);
	}
	void _get_extra_space()
	{
		lua_getextraspace(state);
	}
	void _get_global()
	{
		lua_getglobal(state, "");
	}
	void _get_int32()
	{
		lua_geti(state, 0, 1);
	}
	void _get_metatable()
	{
		lua_getmetatable(state, 0);
	}
	void _get_table()
	{
		lua_gettable(state, 0);
	}
	void _get_top()
	{
		lua_gettop(state);
	}
	void _get_iuservalue()
	{
		lua_getiuservalue(state, 0, 1);
	}
	int _get_global(const char* name)
	{
		return lua_getglobal(state, name);
	}

	// about load 
	bool _load_lua_filex(const char* file_name, const char* mode)
	{
		if (!state) return false;
		return luaL_loadfilex(state, file_name, mode);
	}
	bool _load_lua_file() {}
	bool _load_lua() {}

	void _call()
	{
		//lua_call(state, )

	}

private:
	lua_State* state;


};

#endif