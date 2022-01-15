#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/_lua.h"

#define __GC(FULL_FUNC_NAME)\
{"__gc", FULL_FUNC_NAME},\

#define __CALL(FULL_FUNC_NAME)\
{"__call", FULL_FUNC_NAME},\

#define __INDEX(FULL_FUNC_NAME)\
{"__index", FULL_FUNC_NAME},\

#define __ADD(FULL_FUNC_NAME)\
{"__add", FULL_FUNC_NAME},\

#define __SUB(FULL_FUNC_NAME)\
{"__sub", FULL_FUNC_NAME},\

#define __MUL(FULL_FUNC_NAME)\
{"__mul", FULL_FUNC_NAME},\

#define __DIV(FULL_FUNC_NAME)\
{"__div", FULL_FUNC_NAME},\

#define __MOD(FULL_FUNC_NAME)\
{"__mod", FULL_FUNC_NAME},\

#define __POW(FULL_FUNC_NAME)\
{"__pow", FULL_FUNC_NAME},\

#define __UNM(FULL_FUNC_NAME)\
{"__unm", FULL_FUNC_NAME},\

#define __IDIV(FULL_FUNC_NAME)\
{"__idiv", FULL_FUNC_NAME},\

#define __BAND(FULL_FUNC_NAME)\
{"__band", FULL_FUNC_NAME},\

#define __BOR(FULL_FUNC_NAME)\
{"__bor", FULL_FUNC_NAME},\

#define __BXOR(FULL_FUNC_NAME)\
{"__bxor", FULL_FUNC_NAME},\

#define __BNOT(FULL_FUNC_NAME)\
{"__bnot", FULL_FUNC_NAME},\

#define __SHL(FULL_FUNC_NAME)\
{"__shl", FULL_FUNC_NAME},\

#define __SHR(FULL_FUNC_NAME)\
{"__shr", FULL_FUNC_NAME},\

#define __CONCAT(FULL_FUNC_NAME)\
{"__concat", FULL_FUNC_NAME},\

#define __LEN(FULL_FUNC_NAME)\
{"__len", FULL_FUNC_NAME},\

#define __EQ(FULL_FUNC_NAME)\
{"__eq", FULL_FUNC_NAME},\

#define __LT(FULL_FUNC_NAME)\
{"__lt", FULL_FUNC_NAME},\

#define __LE(FULL_FUNC_NAME)\
{"__le", FULL_FUNC_NAME},\

#define __INDEX(FULL_FUNC_NAME)\
{"__eq", FULL_FUNC_NAME},\

#define FUNC(FUNC_NAME, FUNC_PTR)\
{FUNC_NAME, FUNC_PTR},\


#define LUA_FUNCS_B() \
static const luaL_Reg functions[] =\
{\

#define LUA_FUNCS_E()\
{nullptr}, {nullptr}\
};\

#define LUA_LIBS_B()\
static const luaL_Reg libs[] =\
{\

#define LUA_LIBS_E()\
{nullptr}, {nullptr}\
};\

#define ExtractStr(Specifier) #Specifier

#define IMPLEMENT_EXPORTER(NAME)\
struct NAME##_exporter\
{\
	static NAME##_exporter instance;\
	NAME##_exporter()\
	{\
		lua_vm::register_class_t(ExtractStr(NAME), functions);\
	}\
	~NAME##_exporter() = default;\
};\
NAME##_exporter NAME##_exporter::instance;\


namespace lua_api
{
	enum class lua_t : int
	{
		NONE = LUA_TNONE,
		NIL = LUA_TNIL,
		BOOLEAN = LUA_TBOOLEAN,
		LIGHTUSERDATA = LUA_TLIGHTUSERDATA,
		NUMBER = LUA_TNUMBER,
		STRING = LUA_TSTRING,
		TABLE = LUA_TTABLE,
		FUNCTION = LUA_TFUNCTION,
		USERDATA = LUA_TUSERDATA,
		THREAD = LUA_TTHREAD,
		
		NUMTYPES = LUA_NUMTYPES
	};
	//nil, boolean, number, string, function, userdata, thread, and table.

	inline void push_nil(lua_State* L) { lua_pushnil(L); }
	inline void push_boolean(lua_State* L, bool value) { lua_pushboolean(L, static_cast<int>(value)); }
	
	template<typename INTEGER_T>
	inline void push_integer(lua_State* L, INTEGER_T value)
	{ 
		static_assert(
			std::is_same_v<uint8, INTEGER_T> ||
			std::is_same_v<uint16, INTEGER_T> ||
			std::is_same_v<uint32, INTEGER_T> ||
			std::is_same_v<uint64, INTEGER_T> ||
			std::is_same_v<int8, INTEGER_T> ||
			std::is_same_v<int16, INTEGER_T> ||
			std::is_same_v<int32, INTEGER_T> ||
			std::is_same_v<int64, INTEGER_T>,
			"integer must be std(uint8, uint16, uin32, uint64, int8, int16, int32, int64)"
			);
		lua_pushinteger(L, static_cast<lua_Integer>(value)); 
	}

	template<typename NUMBER_T>
	inline void push_number(lua_State* L, NUMBER_T value)
	{ 
		static_assert(
			std::is_same_v<float, NUMBER_T> ||
			std::is_same_v<double, NUMBER_T>,
			"number must be std(float, double)"
			);
		lua_pushnumber(L, static_cast<lua_Number>(value)); 
	}

	inline void push_string(lua_State* L, char* value) { lua_pushstring(L, value); }
	inline void push_string(lua_State* L, const char* value) { lua_pushstring(L, value); }
	inline void push_string(lua_State* L, std::string& value) { lua_pushstring(L, value.c_str()); }
	inline void push_string(lua_State* L, const std::string& value) { lua_pushstring(L, value.c_str()); }
	inline void push_string(lua_State* L, std::string&& value) { lua_pushstring(L, value.c_str()); }

	inline void push_light_userdata(lua_State* L, void* value)
	{
		lua_pushlightuserdata(L, value);
	}
	inline void push_light_userdata(lua_State* L, const void* value)
	{
		lua_pushlightuserdata(L, (void*)value);
	}
	
	inline void push_thread(lua_State* L)
	{
		lua_pushthread(L);
	}
	inline void push_table(lua_State* L)
	{
		lua_pushglobaltable(L);
	}
	inline void push_from(lua_State* L, int32 index)
	{
		lua_pushvalue(L, index);
	}

	template<typename INTEGER_T>
	inline INTEGER_T get_integer(lua_State* L, int32 stack_index)
	{
		static_assert(
			std::is_same_v<uint8, INTEGER_T> ||
			std::is_same_v<uint16, INTEGER_T> ||
			std::is_same_v<uint32, INTEGER_T> ||
			std::is_same_v<uint64, INTEGER_T> ||
			std::is_same_v<int8, INTEGER_T> ||
			std::is_same_v<int16, INTEGER_T> ||
			std::is_same_v<int32, INTEGER_T> ||
			std::is_same_v<int64, INTEGER_T>,
			"must be uint8, uint16, uin32, uint64, int8, int16, int32, int64"
			);
		return static_cast<INTEGER_T>(lua_tointeger(L, stack_index));
	}

	template<typename NUMBER_T>
	inline NUMBER_T get_number(lua_State* L, int32 stack_index)
	{
		static_assert(
			std::is_same_v<float, NUMBER_T> ||
			std::is_same_v<double, NUMBER_T>,
			"number must be float or double"
			);
		return static_cast<NUMBER_T>(lua_tonumber(L, stack_index));
	}

	inline bool get_boolean(lua_State* L, int32 stack_index) { return lua_toboolean(L, stack_index) == 1; }
	inline std::string get_string(lua_State* L, int32 stack_index) { return std::string(lua_tostring(L, stack_index)); }
	inline lua_CFunction get_cfunction(lua_State* L, int32 stack_index) { return lua_tocfunction(L, stack_index); }
	inline void* get_userdata(lua_State* L, int32 index)
	{
		return lua_touserdata(L, index);
	}
	inline lua_State* get_thread(lua_State* L, int32 stack_index) { return lua_tothread(L, stack_index); }
	
#ifdef _DEBUG
	inline const void* get_pointer(lua_State* L, int32 stack_index)
	{
		return lua_topointer(L, stack_index);
	}
#endif

	/*
	* @return stack top index (1 ~ N)
	*/
	inline int32 get_stack_top_index(lua_State* L) { return lua_gettop(L); }

	/*
	* get the value with global name and push onto stack
	* @return the type of value
	*/
	inline int32 get_global(lua_State* L, const char* name)
	{
		return lua_getglobal(L, name);
	}

	/*
	* get the value (stack_index) 's value (index)
	* @return the type of value
	*/
	inline int32 geti(lua_State* L, int32 stack_index, int32 index)
	{
		return lua_geti(L, stack_index, index);
	}

	/*
	* stack[index][stack[top_index]]
	* @return the type of pushed value
	*/
	inline int32 get_table(lua_State* L, int32 index)
	{
		return lua_gettable(L, index);
	}

	/*
	* @return 1 has metatable and push the metatable onto stack, 0 has no metatable and push nothing
	*/
	inline int32 get_metatable(lua_State* L, int32 stack_index)
	{
		return lua_getmetatable(L, stack_index);
	}

	inline int32 getiuservalue(lua_State* L, int32 index, int32 n)
	{
		return lua_getiuservalue(L, index, n);
	}

	inline void* get_cpp_instance(lua_State* L, int32 stack_index)
	{
		int32 _type = lua_type(L, stack_index);
		switch (_type)
		{
		case LUA_TTABLE: 
		{
			_type = lua_rawget(L, stack_index);
			if (_type == LUA_TUSERDATA)
			{

			}
			else {

			}
		}
		break;
		case LUA_TUSERDATA: break;
		default:
			break;
		}

		void** _instance_ptr = (void**)lua_touserdata(L, stack_index);
		if (!_instance_ptr || !(*_instance_ptr))
		{
			luaL_argcheck(L, false, stack_index, "input val test, invalid user data");
			return nullptr;
		}
		return *_instance_ptr;
	}

	inline void* get_cpp_instance(lua_State* L, int32 stack_index, const char* metatable_name)
	{
		return luaL_checkudata(L, stack_index, metatable_name);
	}

	/*
	* @return type of value
	*/
	inline int32 get_metatable(lua_State* L, const char* name)
	{
		return luaL_getmetatable(L, name);
	}

	/*
	* set the top value as the stack[stack_index]'s metatable, then pop the top val
	* @return type of value
	*/
	inline void set_metatable(lua_State* L, int32 stack_index)
	{
		lua_setmetatable(L, stack_index);
	}

	inline bool is_number(lua_State* L, int32 stack_index) { return lua_isnumber(L, stack_index) == 1; }
	inline bool is_integer(lua_State* L, int32 stack_index) { return lua_isinteger(L, stack_index) == 1; }
	inline bool is_string(lua_State* L, int32 stack_index) { return lua_isstring(L, stack_index) == 1; }
	inline bool is_cfunction(lua_State* L, int32 stack_index) { return lua_iscfunction(L, stack_index) == 1; }
	inline bool is_userdata(lua_State* L, int32 stack_index) { return lua_isuserdata(L, stack_index) == 1; }
	inline bool is_light_userdata(lua_State* L, int32 stack_index) { return lua_islightuserdata(L, stack_index) == 1; }

	inline lua_t get_type(lua_State* L, int32 stack_index) { return static_cast<lua_t>(lua_type(L, stack_index)); }

	template<typename T>
	static int lua_desctroy_userdata(lua_State* l, const char* metatable_name)
	{
		T** pp_userdata = (T**)luaL_checkudata(l, 1, metatable_name);
		delete* pp_userdata;
		printf("userdata type of %s is deleted.", metatable_name);
		return 0;
	}

}

static int testModelOpen(lua_State* L)
{
	//luaL_newlib(L, libs);
	return 1;
}

struct lua_class
{
	std::string name;
	const luaL_Reg* funcs;
};

class lua_vm
{
public:
	lua_vm() = default;

	static int register_class_t(const char* name, const luaL_Reg* funcs)
	{
		std::cout << "register" << std::endl;
		auto _class = new lua_class();
		_class->name = name;
		_class->funcs = funcs;
		global_lua_classes.push_back(_class);
		return 0;
	}

	static std::vector<lua_class*> global_lua_classes;

	int get_classes_num()
	{
		return global_lua_classes.size();
	}

private:

	lua_State* _state = nullptr;

	std::unique_ptr<std::thread> _vm_thread = {};

	bool _should_exit = false;

private:

	std::vector<lua_class*> _classes;

	void _register_class(const std::string& class_name, const luaL_Reg* funcs)
	{
		std::string _clazz_name = class_name + "_clazz";

		luaL_newmetatable(_state, _clazz_name.c_str()); // -1 table, push onto top
		lua_pushvalue(_state, -1); // -1 table new -2 table old
		lua_setfield(_state, -2, "__index"); // set -1 table to -2 table's __index // -1 pop
		luaL_setfuncs(_state, funcs, 0); // set funcs to -1 table
		lua_pop(_state, 1); // pop 1 ele

		lua_newtable(_state);
		luaL_setmetatable(_state, _clazz_name.c_str());
		lua_setglobal(_state, class_name.c_str());
	}

	void _open_libs()
	{
		luaL_openlibs(_state);

		// open std
		//luaopen_base(_state);
		//luaopen_package(_state);
		//luaopen_coroutine(_state);
		//luaopen_string(_state);
		//luaopen_utf8(_state);
		//luaopen_table(_state);
		//luaopen_math(_state);
		//luaopen_io(_state);
		//luaopen_os(_state);
		//luaopen_debug(_state);
	}

	void _register()
	{
		for (auto _class : _classes)
		{
			luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);
			_register_class(_class->name, _class->funcs);
		}
	}

public:

	bool start()
	{
		_state = luaL_newstate();
		if (!_state) return false;
		int top = lua_gettop(_state);

		_open_libs();
		_register();

		// start dispatcher thread
		_vm_thread = std::make_unique<std::thread>(
			[this](int i) 
			{
				while (!_should_exit)
				{
					std::cout << "lvm tick" << std::endl;

					int ret = luaL_dofile(_state, "G:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\blue_freckle\\Test.lua");
					if (ret != 0)
					{
						printf("%s", lua_tostring(_state, -1));
					}

					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}

				lua_close(_state);
				std::cout << "Lua virtual machine exit." << std::endl;
				_should_exit = false;
			}, 1
		);

		std::cout << "Lua virtual machine has been initialized, now is running." << std::endl;
		_vm_thread->detach();
	}

	bool do_file(const std::string& path)
	{
		int _result = luaL_dofile(_state, path.c_str());
		switch (_result)
		{
		case LUA_OK(0): std::cout << "no errors." << std::endl; break;
		case LUA_ERRRUN: std::cout << "a runtime error." << std::endl; break;
		case LUA_ERRMEM: std::cout << "memory allocation error.For such errors, Lua does not call the message handler." << std::endl; break;
		case LUA_ERRERR: std::cout << "error while running the message handler." << std::endl; break;
		case LUA_ERRSYNTAX: std::cout << "syntax error during precompilation." << std::endl; break;
		case LUA_YIELD: std::cout << "the thread(coroutine) yields." << std::endl; break;
		case LUA_ERRFILE: std::cout << "a file - related error; e.g., it cannot open or read the file." << std::endl; break;
		default:
			break;
		}
		if (_result != 0)
		{
			printf("%s", lua_tostring(_state, -1));
		}
	}

public:

	void notify_to_exit()
	{
		_should_exit = true;

		while (_should_exit) {}
	}

};

#endif