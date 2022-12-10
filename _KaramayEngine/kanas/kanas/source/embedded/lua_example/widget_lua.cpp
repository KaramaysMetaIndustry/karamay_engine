#include "widget.h"
#include "embedded/lua/lvm_helper.h"

LUA_TYPE_EXPORTER(widget)
LUA_TYPE_STATIC_FUNCTION(widget, new, &widget::new_lua)
LUA_TYPE_STATIC_FUNCTION(widget, __gc, &widget::wrap_collector)
LUA_TYPE_STATIC_FUNCTION(widget, calc, &widget::calc)
LUA_TYPE_MEMBER_FUNCTION(widget, get_v, &widget::get_v)
LUA_TYPE_MEMBER_FUNCTION(widget, replace, &widget::replace)
