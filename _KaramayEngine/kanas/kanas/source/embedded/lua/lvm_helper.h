#pragma once

#include "lvm.h"

#define DEFINE_LUA_EXPORTER_BEG(TYPE_NAME)\
namespace lua_exporter_##TYPE_NAME\
{\
    static lua_exporter<TYPE_NAME> exporter = {#TYPE_NAME};\





#define DEFINE_LUA_EXPORTER_END()\
}



#define DEFINE_LUA_FUNCTION(FUNCTION_NAME, FUNCTION_PTR)\
namespace func_##FUNCTION_NAME\
{\
    static lua_api::cpp_function_delegate ded = lua_api::cpp_function_delegate(#FUNCTION_NAME, FUNCTION_PTR);\
    \
    static int call_delegate(lua_State* l)\
    {\
        lua_api::call_cpp_func(l, ded.callable);\
        return 1;\
    }\
    \
}

#define DEFINE_LUA_MEMBER_FUNCTION(LUA_FUNCTION_NAME, FUNCTION_PTR)\
namespace lua_##LUA_FUNCTION_NAME\
{\
    static lua_api::cpp_member_function_delegate ded = lua_api::cpp_member_function_delegate(#LUA_FUNCTION_NAME, FUNCTION_PTR);\
\
    static int call_delegate(lua_State* l)\
    {\
        lua_api::call_cpp_member_func(l, ded.callable);\
        return 1;\
    }\
}


#define LUA_CLASS_MODULE_BEGIN(CLASS_NAME)\
lua_api::basic::function_registry lua_api::basic::lua_exporter<CLASS_NAME>::registry ={};\
std::function<void(lua_api::basic::function_registry&)> lua_api::basic::lua_exporter<CLASS_NAME>::registry_delegate =  [](function_registry& fr)\
{\

#define LUA_CLASS_MODULE_END(CLASS_NAME)\
};\
lua_api::basic::lua_exporter<CLASS_NAME> lua_api::basic::lua_exporter<CLASS_NAME>::exporter = {};\
template<>\
constexpr bool lua_api::basic::is_lua_exporter_registered<CLASS_NAME> = true;