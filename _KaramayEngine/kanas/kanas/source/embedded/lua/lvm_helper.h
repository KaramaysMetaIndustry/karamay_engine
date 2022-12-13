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
    std::clog<<"[Lua -> Cpp] [BEG] " << delegate_##FUNCTION_NAME.delegate_name <<std::endl;\
    int result = lua_api::call_cpp_func(l, delegate_##FUNCTION_NAME.callable);\
    std::clog<<"[Lua -> Cpp] [END] " << delegate_##FUNCTION_NAME.delegate_name <<std::endl;\
    return result;\
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
    std::clog<<"[Lua -> Cpp] [BEG] " << delegate_##FUNCTION_NAME.delegate_name <<std::endl;\
    int result = lua_api::call_cpp_member_func(l, delegate_##FUNCTION_NAME.callable);\
    std::clog<<"[Lua -> Cpp] [END] " << delegate_##FUNCTION_NAME.delegate_name <<std::endl;\
    return result;\
}\
struct lua_cpp_function_exporter_##FUNCTION_NAME\
{\
    lua_cpp_function_exporter_##FUNCTION_NAME()\
    {\
        exporter_##TYPE_NAME.funcs.emplace(delegate_##FUNCTION_NAME.delegate_name, call_delegate_##FUNCTION_NAME); \
    }\
}; \
static lua_cpp_function_exporter_##FUNCTION_NAME function_exporter_##FUNCTION_NAME;



#define LUA_LIB_EXPORTER(LIB_NAME)\
static std::vector<luaL_Reg> lib_funcs_##LIB_NAME;\
static int open_lib_##LIB_NAME(lua_State* l)\
{\
    luaL_newlib(l, lib_funcs_##LIB_NAME.data());\
    return 1;\
}\
static lua_lib lib_##LIB_NAME = { #LIB_NAME , &lib_funcs_##LIB_NAME, open_lib_##LIB_NAME };


#define LUA_LIB_FUNCTION(LIB_NAME, FUNC_NAME, FUNCTION_PTR)\
static lua_api::cpp_function_delegate delegate_##LIB_NAME##_##FUNC_NAME = lua_api::cpp_function_delegate("kanas_log", FUNCTION_PTR);\
static int call_delegate_##LIB_NAME##_##FUNC_NAME##(lua_State* l)\
{\
    return lua_api::call_cpp_func(l, delegate_##LIB_NAME##_##FUNC_NAME.callable);\
}\
struct lib_func_exporter_##LIB_NAME##_##FUNC_NAME\
{\
    lib_func_exporter_##LIB_NAME##_##FUNC_NAME()\
    {\
        lib_funcs_##LIB_NAME.push_back({ #FUNC_NAME, call_delegate_##LIB_NAME##_##FUNC_NAME });\
    }\
};\
static lib_func_exporter_##LIB_NAME##_##FUNC_NAME libexporter_##LIB_NAME##_##FUNC_NAME;



//static lua_api::cpp_member_function_delegate_tuple fdt = lua_api::cpp_member_function_delegate_tuple("get_v_multi", &widget::get_v);
