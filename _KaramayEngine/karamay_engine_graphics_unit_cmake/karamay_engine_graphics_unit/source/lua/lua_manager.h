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

	class lua_boolean {
	public:
		lua_boolean() : _value(false) {}

		void fetch(lua_State* l, std::int32_t index)
		{
			if (!lua_isboolean(l, index)) return;
			_value = lua_toboolean(l, index);
		}

		bool get() { return _value; }

	private:

		bool _value;

	};

	class lua_number {
	public:
		lua_number() : _value(0.0l) {}

		void fetch(lua_State* l, std::int32_t index)
		{
			if (!lua_isnumber(l, index)) return;
			_value = lua_tonumber(l, index);
		}

		std::double_t get() { return _value; }

	private:

		std::double_t _value;
	};

	class lua_string {
	public:
		lua_string() : _string(nullptr) {}

		void fetch(lua_State* l, std::int32_t index)
		{
			_string = lua_tostring(l, index);
		}

		std::string to_std_string() const
		{
			if (!_string) return std::string("");
			return std::string(_string);
		}

		const char* to_string() const
		{
			if (!_string) return "";
			return _string;
		}

	private:
		const char* _string;
	};

	class lua_userdata {
	public:
		lua_userdata() : _userdata(nullptr) {}

		~lua_userdata() {}

		void fetch(lua_State* l, std::int32_t index)
		{
			if (!lua_isuserdata(l, index)) return;
			_userdata = *((void**)lua_touserdata(l, index));
		}

		template<typename T> T* to_class() { return (T*)(_userdata); }

	private:

		void* _userdata;

	};

	class lua_function {
	public:

		lua_function() : _func_ptr(nullptr) {}

		~lua_function() = default;

		void fetch(lua_State* l, std::int32_t index)
		{
			if (!lua_iscfunction(l, index)) return;
			_func_ptr = lua_tocfunction(l, index);
		}

		std::function<std::int32_t(lua_State*)> to_std_function()
		{
			return std::function<std::int32_t(lua_State*)>(_func_ptr);
		}

		lua_CFunction to_c_function() { return _func_ptr; }

		static void push(lua_State* l, lua_CFunction function)
		{
			lua_pushcfunction(l, function);
			lua_pushcclosure(l, function, 0);
		}

	private:

		lua_CFunction _func_ptr;

	};

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