#include "widget.h"
#include "embedded/lua/lvm_helper.h"

DEFINE_LUA_EXPORTER(widget)

template<>
struct lua_api::lua_userdata_meta_info<std::shared_ptr<widget>>
{
	const char* get_type_name()
	{
		return "widget";
	}

	static lua_userdata_meta_info ref;
};

lua_api::lua_userdata_meta_info<std::shared_ptr<widget>> lua_api::lua_userdata_meta_info<std::shared_ptr<widget>>::ref = {};


//lua_api::cpp_function_delegate dd = lua_api::cpp_function_delegate("aaa", &widget::calc);
//
//static int test(lua_State* l)
//{
//	lua_api::call_cpp_func(l, dd.callable);
//}

//lua_api::cpp_member_function_delegate ddm = lua_api::cpp_member_function_delegate("xxx", &widget::get_v);
//
//static int test1(lua_State* l)
//{
//	lua_api::call_cpp_member_func(l, ddm.callable);
//}

DEFINE_LUA_FUNCTION(widget, new, &widget::new_lua)
DEFINE_LUA_FUNCTION(widget, __close, &widget::wrap_collector)
DEFINE_LUA_FUNCTION(widget, calc, &widget::calc)
DEFINE_LUA_MEMBER_FUNCTION(widget, getv, &widget::get_v)
DEFINE_LUA_MEMBER_FUNCTION(widget, replace, &widget::replace)
