#include "lvm.h"

lua_api::function_registry lua_api::lua_vm::registry = {};

std::vector<lua_api::lua_class*> lua_api::lua_vm::_classes = {};

bool lua_api::lua_vm::initialize() noexcept
{
	std::cout << "lvm starts to initialize." << std::endl;

	std::cout << "lvm has initialized." << std::endl;
	return true;
}

void lua_api::lua_vm::run() noexcept
{
	state_ = luaL_newstate();
	
	if (!state_)
	{
		return;
	}
	
	_load_libs();
}

bool lua_api::lua_vm::do_file(const std::string& path)
{
	int _result = luaL_dofile(state_, path.c_str());
	switch (_result)
	{
	case LUA_OK: std::cout << "no errors." << std::endl; break;
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
		printf("%s", lua_tostring(state_, -1));
		return false;
	}

	return true;
}

void lua_api::lua_vm::_load_class(const std::string& class_name, const luaL_Reg* funcs)
{
	const auto _clazz_name = class_name + "_clazz";

	// stack : null
	auxiliary::new_metatable(_clazz_name.c_str());
	// stack : metatable
	basic::push_value(-1);
	// stack : metatable, metatable
	basic::set_field(-2, "__index");
	// stack : metatable
	auxiliary::set_funcs(funcs, 0);
	basic::pop(1);
	// stack : null

	basic::create_table();
	// stack : table
	auxiliary::set_metatable(_clazz_name.c_str());
	basic::set_global(class_name.c_str());
	// stack : null

	std::cout << "load class : " << class_name << std::endl;
}

void lua_api::lua_vm::_load_libs()
{
	auxiliary::open_libs();

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
