#ifndef LUA_MANAGER_H
#define LUA_MANAGER_H

#include "public/_lua.h"

namespace karamay_lua
{
    lua_State* state(){}
}

struct lua_index
{
    explicit lua_index(std::int32_t index): _index(index){}

    std::int32_t index() const { return _index; }

protected:

    std::int32_t _index;
};

struct lua_t
{

};

struct lua_result
{
    explicit lua_result(std::int32_t num){}

    void pop(){}
    bool is_valid() const{ return _valid;}
    std::int32_t num() const{return _values.size();}

    const lua_t& operator[](std::int32_t index) const { return _values[index];}

private:

    std::vector<lua_t> _values;
    bool _valid;
};



template<typename... T>
lua_result call_function_internal(lua_State* state, T&&... args)
{
    std::int32_t _message_handler_index = lua_gettop(state) - 1;
    if(_message_handler_index > 0)
    {
        std::int32_t _args_num;
        std::int32_t _code = lua_pcall(state, _args_num, LUA_MULTRET, _message_handler_index);
        std::int32_t _top_index = lua_gettop(state);
        if(_code == LUA_OK)
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

struct lua_table : lua_index{
    explicit lua_table(std::int32_t){}
    explicit lua_table(lua_t value){}

    void reset();
    std::int32_t length() const{}

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
        if(!method_name){
            return lua_result(0);
        }

        auto* _state = karamay_lua::state();
        lua_pushcfunction(_state, report_lua_call_error);

        lua_pushstring(_state, method_name);
        std::int32_t _type = lua_gettable(_state, _index);
        if(_type != LUA_TFUNCTION)
        {
            std::cout<<"method does not exist"<<std::endl;
            lua_pop(_state, 2);
            return lua_result(0);
        }


    }

private:

    mutable std::int32_t pushed_values;
};


struct lua_function
{

    template<typename... T>
    lua_result invoke(T&&... args) const
    {
        
    }

};


int test(lua_State* L)
{
	return 1;
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


public:

	template<typename... Rests>
	struct lua_func_renturn
	{

	};


	template<typename... Rests, typename... Args>
	lua_func_renturn<Rests...> invoke(const std::string& method_name, Args... args)
	{
		auto _global_func_idx = _get_global(method_name.c_str());

		//_push_args(args);

		lua_pushnumber(state, 1);
		lua_pushnumber(state, 2);

		if (lua_pcall(state, 2, 1, 0) != 0)
		{

		}


		//double z;
		//lua_getglobal(L, "f");
		//lua_pushnumber(L, x);
		//lua_pushnumber(L, y);
		///* do the call (2 arguments, 1 result) */
		//if (lua_pcall(L, 2, 1, 0) != 0)
		//	error(L, "error running function 'f': %s",
		//		lua_tostring(L, -1));

		//if (!lua_isnumber(L, -1))
		//	error(L, "function 'f' must return a number");
		//z = lua_tonumber(L, -1);

		//lua_pop(L, 1);
		//return z; 
		//invoke("construct", lua_number_t(), lua_integer_t())
	}



};

#endif