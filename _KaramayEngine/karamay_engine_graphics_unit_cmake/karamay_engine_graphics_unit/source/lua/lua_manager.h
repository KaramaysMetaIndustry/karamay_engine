#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include "public/_lua.h"


int test(lua_State* L)
{

}

class lua_manager{
public:

	void construct()
	{
		lua_State* L = luaL_newstate();


		luaL_loadfilex(L, "hello.lua", "");

		lua_pushcclosure(state, test, 1);
		lua_pushcfunction(state, test);
		
	}

	void _pop(std::int32_t num)
	{
		lua_pop(state, num);
	}

	void _push_nil()
	{
		lua_pushnil(state);
	}
	void _push_boolean(bool value)
	{
		lua_pushboolean(state, static_cast<int>(value));
	}
	void _push_c_closure()
	{}
	void _push_c_function()
	{}
	void _push_global_table()
	{
		lua_pushglobaltable(state);
	}
	void _push_int64(std::int64_t value)
	{
	}
	void _push_double(std::double_t value)
	{
		lua_pushnumber(state, value);
	}
	const char* _push_string(const char* value)
	{
		return lua_pushstring(state, value);
	}
	const char* _push_string(const char* value, std::uint64_t length)
	{
		lua_pushlstring(state, value, length);
	}
	const char* _push_literal(const char* value)
	{
		return lua_pushliteral(state);
	}
	const char* _push_format_string(const char* format, ...)
	{
		lua_pushfstring(state, format, 1);
	}
	const char* _push_format_string() 
	{
		//lua_pushvfstring();
	}
	void _push_thread()
	{
		lua_pushthread(state);
	}
	void _push_value(std::int32_t index)
	{
		lua_pushvalue(state, index);
	}
	void _push_light_userdata()
	{
		lua_pushlightuserdata(state, nullptr);
	}




	void tick(std::float_t delta_time = 0.0f) {}


	bool _load_lua_file(const char* file_name, const char* mode)
	{
		if (!state) return false;
		return luaL_loadfilex(state, file_name, mode);
	}

	const char* push_string(const char* value)
	{
		if (!state) return nullptr;
		return lua_pushstring(state, value);
	}
	void push_number(std::double_t value)
	{
		lua_pushnumber(state, value);
	}

private:
	lua_State* state;
};

#endif