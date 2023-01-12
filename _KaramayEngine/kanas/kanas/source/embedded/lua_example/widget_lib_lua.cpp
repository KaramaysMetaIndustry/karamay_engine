#include "widget_lib.h"
#include "embedded/lua/lvm_helper.h"

LUA_LIB_EXPORTER(kanas)

LUA_LIB_FUNCTION(kanas, clog, &kanas::log)
LUA_LIB_FUNCTION(kanas, clogf, &kanas::logf)

LUA_GLOBAL_FUNCTION(clog, &kanas::log)


void test()
{
    
    std::vector<float> a;

    std::unordered_map<int, float> x;
    
    lua_api::push(nullptr, x);
}