#include "lvm.h"

std::vector<lua_api::lua_class*> lua_api::lua_vm::_classes = {};

bool lua_api::lua_vm::initialize() noexcept
{
	std::cout << "lvm starts to initialize." << std::endl;

	std::cout << "lvm has initialized." << std::endl;
	return true;
}

void lua_api::lua_vm::run() noexcept
{
	std::cout << "Lua virtual machine is running." << std::endl;

	_state = lua_api::auxiliary::new_state();
	if (!_state) return;
	_load_libs();

	while (!_should_exit)
	{
		//std::cout << "lvm tick" << std::endl;

		/*int ret = luaL_dofile(_state, "C:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\blue_freckle\\test.lua");
		if (ret != 0)
		{
			printf("%s", lua_tostring(_state, -1));
		}*/

		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	lua_close(_state);

	std::cout << "Lua virtual machine has exited." << std::endl;
}

void lua_api::lua_vm::notify_to_exit() noexcept
{
	_should_exit = true;
}

bool lua_api::lua_vm::do_file(const std::string& path)
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
		return false;
	}

	return true;
}

void lua_api::lua_vm::_load_class(const std::string& class_name, const luaL_Reg* funcs)
{
	const auto _clazz_name = class_name + "_clazz";

	// stack : null
	lua_api::auxiliary::new_metatable(_state, _clazz_name.c_str());
	// stack : metatable
	lua_api::basic::push_value(_state, -1);
	// stack : metatable, metatable
	lua_api::basic::set_field(_state, -2, "__index");
	// stack : metable
	lua_api::auxiliary::set_funcs(_state, funcs, 0);
	lua_api::basic::pop(_state, 1);
	// stack : null

	lua_api::basic::create_table(_state);
	// stack : table
	lua_api::auxiliary::set_metatable(_state, _clazz_name.c_str());
	lua_api::basic::set_global(_state, class_name.c_str());
	// stack : null

	std::cout << "load class : " << class_name << std::endl;
}

void lua_api::lua_vm::_load_libs()
{
	lua_api::auxiliary::open_libs(_state); // std

	//luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);

	for (auto _class : _classes)
	{
		_load_class(_class->name, _class->funcs);
	}
}

void lua_api::lua_vm::register_class(const char* name, const luaL_Reg* funcs)
{
	std::cout << "register class : " << name << std::endl;
	auto _class = new lua_class();
	_class->name = name;
	_class->funcs = funcs;
	_classes.push_back(_class);
}

void lua_api::lua_vm::register_functions(const luaL_Reg* funcs)
{
}
