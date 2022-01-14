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







class CTest 
{
public:
	CTest() : value(0) {}

	~CTest() = default;

	int getA() { return value; }
	
	void setA(int a) { value = a; }

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

class CTest_static_proxy
{
public:

	static int lua_construct(lua_State* L)
	{
		CTest** ppTest = (CTest**)lua_newuserdata(L, sizeof(CTest*)); // -1
		*ppTest = new CTest;
		luaL_getmetatable(L, "gl_renderer_clazz"); // -1 ; userdata -2
		lua_setmetatable(L, -2);  // set -1 as -2 's metatable
		return 1;
	}

	static int lua_getA(lua_State* L)
	{
		CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
		luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");
		lua_pushnumber(L, (int)(*ppTest)->getA());
		return 1;
	}

	static int lua_setA(lua_State* L)
	{
		int args_num = lua_gettop(L);

		CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
		luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

		int a = (int)lua_tointeger(L, 2);
		(*ppTest)->setA(a);

		return 0;
	}

	template<typename T>
	static T* get_parameter(lua_State* l, int index)
	{
		T** ppParam = (T**)lua_touserdata(l, index);
		luaL_argcheck(l, ppParam != NULL, index, "input val test, invalid user data");
		return ppParam;
	}

	/*
	* gl_renderer FinishTest(gl_renderer)
	*/
	static int lua_finishNewCTest(lua_State* L)
	{
		// when this func called, 调用改方法的metatable的userdata压入栈，并依次压入栈
		// get this pointer, param 1
		int top = lua_gettop(L);
		if (top != 2) return 0;

		std::cout << "params num : " << top << std::endl;

		CTest** ppTest = (CTest**)luaL_checkudata(L, 1, "gl_renderer_clazz");
		luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

		std::function<int(lua_State*)> lua_func;

		auto a = lua_func.target<lua_CFunction>();

		// get param 2
		CTest** ppParamTest = (CTest**)lua_touserdata(L, 2);
		luaL_argcheck(L, ppTest != NULL, 2, "input val test, invalid user data");

		// invoke
		CTest* pResult = (*ppTest)->finishNewCTest(*ppParamTest);

		// 返回传入参数
		lua_pushvalue(L, 2);

		return 1;
	}

	template<typename T>
	static int lua_desctroy_userdata(lua_State* l, const char* metatable_name)
	{
		T** pp_userdata = (T**)luaL_checkudata(l, 1, metatable_name);
		delete* pp_userdata;
		printf("userdata type of %s is deleted.", metatable_name);
		return 0;
	}

	static int desctroy(lua_State* L)
	{
		return lua_desctroy_userdata<CTest>(L, "gl_renderer_clazz");
	}
};

static const struct luaL_Reg libs[] =
{
	/*{"gl_renderer", CTest::lua_construct},*/
	{NULL, NULL},
};

static const luaL_Reg test_reg_mf[] =
{
	{"TestGetA", CTest_static_proxy::lua_getA},
	{"TestSetA", CTest_static_proxy::lua_setA},
	{"FinishTest", CTest_static_proxy::lua_finishNewCTest},
	{"__gc", CTest_static_proxy::desctroy},
	{"__call", CTest_static_proxy::lua_construct},
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

struct lua_module
{
	std::string name;

	const luaL_Reg* reg;

};


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
	
}

class lua_vm
{
public:
	lua_vm() = default;

private:

	lua_State* _state;

	std::unique_ptr<std::thread> _vm_thread;

	bool _should_exit = false;

private:

	std::vector<lua_module*> _modules;


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

	void register_module()
	{
		for (auto _module : _modules)
		{
			luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);
			create_test_metatable(_state, _module->name.c_str(), _module->reg);
		}
	}

public:

	bool start()
	{
		_state = luaL_newstate();
		if (!_state) return false;

		luaL_openlibs(_state);
		int top = lua_gettop(_state);

		// open std
		luaopen_base(_state);
		luaopen_package(_state);
		luaopen_coroutine(_state);
		luaopen_string(_state);
		luaopen_utf8(_state);
		luaopen_table(_state);
		luaopen_math(_state);
		luaopen_io(_state);
		luaopen_os(_state);
		luaopen_debug(_state);

		// register custom module
		register_testModel_module(_state);

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

public:

	void notify_to_exit()
	{
		_should_exit = true;

		while (_should_exit) {}
	}

};

#endif