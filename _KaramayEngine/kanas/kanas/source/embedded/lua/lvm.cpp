#include "lvm.h"

bool lua_vm::initialize() noexcept
{
	std::cout << "lvm starts to initialize." << std::endl;

	std::cout << "lvm has initialized." << std::endl;
	return true;
}

void lua_vm::run() noexcept
{
	state_ = luaL_newstate();
	
	if (!state_)
	{
		return;
	}
	
	_load_libs();
}

bool lua_vm::do_file(const std::string& path)
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

void lua_vm::_load_class(const std::string& class_name, const luaL_Reg* funcs)
{
	const auto _clazz_name = class_name + "_clazz";

	// stack : null
	luaL_newmetatable(state_, _clazz_name.c_str());
	// stack : metatable
	lua_pushvalue(state_, -1);
	// stack : metatable, metatable
	lua_setfield(state_, -2, "__index");
	// stack : metatable
	luaL_setfuncs(state_, funcs, 0);
	lua_pop(state_, 1);
	// stack : null

	lua_newtable(state_);
	// stack : table
	luaL_setmetatable(state_, _clazz_name.c_str());
	lua_setglobal(state_, class_name.c_str());
	// stack : null

	std::cout << "load class : " << class_name << std::endl;
}

void lua_vm::_load_libs()
{
	luaL_openlibs(state_);

	//luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);

	for (auto& type : types)
	{
		_load_class(type.first, type.second.data());
	}
}

void lua_vm::register_type(const std::string& name,  const std::vector<luaL_Reg>& regs)
{
	std::cout << "register class : " << name << std::endl;
	types.emplace(name, regs);
}
