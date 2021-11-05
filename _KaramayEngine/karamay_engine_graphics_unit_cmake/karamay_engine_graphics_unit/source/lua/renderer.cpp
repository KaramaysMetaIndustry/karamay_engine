#include "renderer.h"

renderer::renderer()
{
}

int renderer::launch(int a, float b)
{
	return 0;
}


static int renderer_construct(lua_State* L)
{
}

static int launch(lua_State* L)
{
	renderer** ppTest = (renderer**)luaL_checkudata(L, 1, "test");
	luaL_argcheck(L, ppTest != NULL, 1, "invalid user data");

	int a = (int)lua_tointeger(L, 2);
	(*ppTest)->launch(1, 1);
}

