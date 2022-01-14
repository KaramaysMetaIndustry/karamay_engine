#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/_lua.h"

class lua_t
{
};

//nil, boolean, number, string, function, userdata, thread, and table.
class lua_nil : public lua_t
{
};

class lua_boolean : public lua_t
{

};

class lua_number : public lua_t
{

};

class lua_string : public lua_t
{

};

class lua_function : public lua_t
{};

class lua_userdata : public lua_t
{};

class lua_thread : public lua_t
{};

class lua_table : public lua_t
{};

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

//void create_clazz(lua_State* L, const char* metatable_name, const luaL_Reg* regs)
//{
//	// -1 Õ»¶¥
//	// 1 Õ»µ×
//
//	luaL_newmetatable(L, metatable_name); // -1 table, push onto top
//	lua_pushvalue(L, -1); // -1 table new -2 table old
//
//	lua_setfield(L, -2, "__index"); // set top table to -2 table's __index , -1 pop
//	luaL_setfuncs(L, regs, 0); // set funcs to top table
//	lua_pop(L, 1); // pop 1 element (-2)
//
//	lua_newtable(L); // create a new table on the top
//	luaL_setmetatable(L, metatable_name); // set the metatable to the top table
//	lua_setglobal(L, "gl_renderer");
//}
//
//void register_module(lua_State* L)
//{
//	//luaL_requiref(L, "karamay_RHI", testModelOpen, 0);
//	//create_clazz(L, "gl_renderer_clazz", funcs);
//}

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