#pragma once

#include "lvm.h"

#define LUA_TYPE_EXPORTER(TYPE_NAME)\
static lua_exporter exporter_##TYPE_NAME = {#TYPE_NAME};\
template<>\
struct lua_api::lua_userdata_meta_info<std::shared_ptr<TYPE_NAME>>\
{\
    const char* get_type_name()\
    {\
        return #TYPE_NAME;\
    }\
\
    static lua_userdata_meta_info ref;\
};\
lua_api::lua_userdata_meta_info<std::shared_ptr<TYPE_NAME>> lua_api::lua_userdata_meta_info<std::shared_ptr<TYPE_NAME>>::ref = {};



#define LUA_TYPE_STATIC_FUNCTION(TYPE_NAME, FUNCTION_NAME, FUNCTION_PTR)\
static lua_api::cpp_function_delegate delegate_##FUNCTION_NAME = lua_api::cpp_function_delegate(#FUNCTION_NAME, FUNCTION_PTR);\
\
static int call_delegate_##FUNCTION_NAME##(lua_State* l)\
{\
    return lua_api::call_cpp_func(l, delegate_##FUNCTION_NAME.callable);\
}\
\
struct lua_cpp_function_exporter_##FUNCTION_NAME\
{\
    lua_cpp_function_exporter_##FUNCTION_NAME()\
    {\
        exporter_##TYPE_NAME.funcs.emplace(delegate_##FUNCTION_NAME.delegate_name, call_delegate_##FUNCTION_NAME);\
    }\
};\
\
static lua_cpp_function_exporter_##FUNCTION_NAME function_exporter_##FUNCTION_NAME;


#define LUA_TYPE_MEMBER_FUNCTION(TYPE_NAME, FUNCTION_NAME, FUNCTION_PTR)\
static lua_api::cpp_member_function_delegate delegate_##FUNCTION_NAME = lua_api::cpp_member_function_delegate(#FUNCTION_NAME, FUNCTION_PTR);\
static int call_delegate_##FUNCTION_NAME(lua_State* l)\
{\
    return lua_api::call_cpp_member_func(l, delegate_##FUNCTION_NAME.callable);\
}\
struct lua_cpp_function_exporter_##FUNCTION_NAME\
{\
    lua_cpp_function_exporter_##FUNCTION_NAME()\
    {\
        exporter_##TYPE_NAME.funcs.emplace(delegate_##FUNCTION_NAME.delegate_name, call_delegate_##FUNCTION_NAME); \
    }\
}; \
static lua_cpp_function_exporter_##FUNCTION_NAME function_exporter_##FUNCTION_NAME;




#define LUA_LIB_FUNCTION(LIB_NAME, FUNCTION_NAME, FUNCTION_PTR)