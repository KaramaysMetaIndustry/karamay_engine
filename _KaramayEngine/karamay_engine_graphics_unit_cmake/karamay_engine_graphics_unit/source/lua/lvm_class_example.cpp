#include "lvm_class_example.h"
#include "lvm.h"

#define __GC(FULL_FUNC_NAME)\
{"__gc", FULL_FUNC_NAME}\

#define __CALL(FULL_FUNC_NAME)\
{"__call", FULL_FUNC_NAME}\

#define FUNC(FUNC_NAME, FUNC_PTR)\
{FUNC_NAME, FUNC_PTR}\

struct CTest_lua_proxy
{
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

static const luaL_Reg libs[] =
{
	/*{"gl_renderer", CTest::lua_construct},*/
	{NULL, NULL},
};

static const luaL_Reg funcs[] =
{
	FUNC("TestGetA", CTest_lua_proxy::lua_getA),
	FUNC("TestSetA", CTest_lua_proxy::lua_setA),
	FUNC("FinishTest", CTest_lua_proxy::lua_finishNewCTest),
	__GC(CTest_lua_proxy::desctroy),
	__CALL(CTest_lua_proxy::lua_construct),
	{NULL, NULL}
};

struct CTest_export_helper
{
	static CTest_export_helper instance;

	CTest_export_helper()
	{
		std::cout << "aaa" << std::endl;
		lua_vm::register_class_t("gl_renderer", funcs);
	}

	~CTest_export_helper() {}
};

CTest_export_helper CTest_export_helper::instance;


int CTest::getA()
{
	return value;
}



