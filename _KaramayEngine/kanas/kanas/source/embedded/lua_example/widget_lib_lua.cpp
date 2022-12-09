#include "widget_lib.h"
#include "embedded/lua/lvm_helper.h"

static std::vector<luaL_Reg> lib_funcs;
static int open_kanas_lib(lua_State* l)
{
    luaL_newlib(l, lib_funcs.data());
    return 1;
}
static lua_lib kanas_lib = { "kanas" , open_kanas_lib };

static lua_api::cpp_function_delegate delegate_kanas_log = lua_api::cpp_function_delegate("kanas_log", &kanas::log);

static int call_delegate_kanas_log(lua_State* l)
{
    return lua_api::call_cpp_func(l, delegate_kanas_log.callable);
}

struct func_exporter_kanas_log
{
    func_exporter_kanas_log()
    {
        lib_funcs.push_back({"log", call_delegate_kanas_log});
        lib_funcs.push_back({nullptr, nullptr});
    }
};

static func_exporter_kanas_log exporter_kanas_log;


LUA_LIB_EXPORTER()

LUA_LIB_FUNCTION(kanas, create, &kanas_log)