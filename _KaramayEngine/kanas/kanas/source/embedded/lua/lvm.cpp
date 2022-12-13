#include "lvm.h"

std::vector<lua_exporter*> lua_vm::type_exporters = {};
std::vector<lua_lib*> lua_vm::libs = {};

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

	do_file("G:\\karamay_engine\\_KaramayEngine\\kanas\\kanas\\scripts\\lua\\Main.lua");
	//do_file("E:\\PrivateRepos\\karamay_engine\\_KaramayEngine\\kanas\\kanas\\scripts\\lua\\Main.lua");
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
		//printf("%s", lua_tostring(state_, -1));
		return false;
	}

	return true;
}

void lua_vm::_load_class(const std::string& class_name, const luaL_Reg* funcs)
{
	//const auto _clazz_name = class_name + "_clazz";

	//// stack : null
	//luaL_newmetatable(state_, _clazz_name.c_str());
	//// stack : metatable
	//lua_pushvalue(state_, -1);
	//// stack : metatable, metatable
	//lua_setfield(state_, -2, "__index");
	//// stack : metatable
	//luaL_setfuncs(state_, funcs, 0);
	//lua_pop(state_, 1);
	//// stack : null

	//lua_newtable(state_);
	//// stack : table
	//luaL_setmetatable(state_, _clazz_name.c_str());
	//lua_setglobal(state_, class_name.c_str());
	//// stack : null

	luaL_getmetatable(state_, class_name.c_str());
	if (lua_isnil(state_, -1))
	{
		luaL_newmetatable(state_, class_name.c_str());

		/*for (int i = 0; st[i].func; i++)
		{
			lua_pushstring(L, st[i].name);
			lua_pushcfunction(L, st[i].func);
			lua_rawset(L, -3);
		}*/
		luaL_setfuncs(state_, funcs, 0);
	}
	lua_setglobal(state_, class_name.c_str());
}

static int wrap_index_event(lua_State* L)
{
	if (!lua_isuserdata(L, 1))
	{
		lua_error(L);
		return 0;
	}

	if (lua_getmetatable(L, 1))
	{
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);
		if (lua_isfunction(L, -1))
			return 1;
		else
			lua_error(L);
	}

	return 0;
}

void lua_vm::_load_libs()
{
	luaL_openlibs(state_);

	for(auto lib : libs)
	{
		lib->lib_funcs->push_back({ nullptr, nullptr });
		luaL_requiref(state_, lib->name.c_str(), lib->open_func, 0);
		lua_pop(state_, 1);
	}
	
	std::vector<luaL_Reg> raw_funcs;
	for (auto exporter : type_exporters)
	{
		raw_funcs.clear();

		for (const auto& pair : exporter->funcs)
		{
			raw_funcs.push_back({ pair.first.c_str(), pair.second });
		}
		raw_funcs.push_back({ "__index", wrap_index_event });
		raw_funcs.push_back({ nullptr, nullptr });

		_load_class(exporter->type_name, raw_funcs.data());
	}
}

void lua_vm::register_type_exporter(lua_exporter* exporter)
{
	type_exporters.push_back(exporter);
}

void lua_vm::register_lib(lua_lib* lib)
{
	libs.push_back(lib);
}
