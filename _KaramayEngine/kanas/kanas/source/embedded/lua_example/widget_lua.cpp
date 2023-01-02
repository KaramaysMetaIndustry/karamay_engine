#include "widget.h"
#include "embedded/lua/lvm_helper.h"

//#define LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION___GC(TYPE_NAME, CPP_FUNCTION_NAME) LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(TYPE_NAME, __gc, CPP_FUNCTION_NAME)
//#define LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION___STRING(TYPE_NAME, CPP_FUNCTION_NAME) LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(TYPE_NAME, __string, CPP_FUNCTION_NAME)

LUA_TYPE_EXPORTER(widget)

LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(widget, new, new_lua)
LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(widget, __gc, wrap_collector)
LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(widget, __tostring, to_string)
LUA_TYPE_PUBLIC_CPP_STATIC_FUNCTION(widget, calc, calc)
LUA_TYPE_PUBLIC_CPP_STATIC_PROPERTY(widget, static_public_v)
LUA_TYPE_PUBLIC_CPP_MEMBER_FUNCTION(widget, get_v, get_v)
LUA_TYPE_PUBLIC_CPP_MEMBER_FUNCTION(widget, replace, replace)
LUA_TYPE_PUBLIC_CPP_MEMBER_FUNCTION(widget, set_values, set_values)
LUA_TYPE_PUBLIC_CPP_MEMBER_PROPERTY(widget, public_v)
