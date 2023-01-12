#ifndef LVM_H
#define LVM_H

#include "lua_type_push.h"
#include "lua_type_is.h"
#include "lua_type_to.h"

#include <functional>
#include <iostream>

namespace lua_api
{
	template<typename Ret, typename... Args, typename... TupleArgs, std::size_t... N>
	static Ret call_cpp_func_impl(const std::function<Ret(Args...)>& func, std::tuple<TupleArgs...>& parameters, std::index_sequence<N...>)
	{
		if constexpr (std::is_void_v<Ret>)
		{
			func(std::get<N>(parameters)...);
		} else {
			return func(std::get<N>(parameters)...);
		}
	}

	template<typename Ret, typename... Args>
	static std::int32_t call_cpp_func(lua_State* l, const std::function<Ret(Args...)>& func)
	{
		auto parameters = to_tuple<std::remove_cvref_t<Args>...>(l);

		if(!parameters)
		{
			std::clog << "[lua -> cpp] Parameters are not valid." << std::endl;
			lua_pushnil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_func_impl(func, parameters.value(), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, call_cpp_func_impl(func, parameters.value(), std::index_sequence_for<Args...>()));
			return 1;
		}
	}

	template<typename Ret, typename... Args>
	struct cpp_function_delegate
	{
		cpp_function_delegate(const std::string& name, Ret(* f)(Args...))
		{
			delegate_name = name;
			callable = f;
		}
    
		std::string delegate_name;
		std::function<Ret(Args...)> callable;
	};


	template<typename Ret, typename Ty, typename... Args, typename... TupleArgs, std::size_t... N>
	static Ret call_cpp_member_func_impl(const std::function<Ret(Ty*, Args...)>& func, std::tuple<std::shared_ptr<Ty>, TupleArgs...>& parameters, std::index_sequence<N...>)
	{
		if constexpr (std::is_void_v<Ret>)
		{
			func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		} else {
			return func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		}
	}
	
	template<typename Ret, typename Ty, typename... Args>
	static std::int32_t call_cpp_member_func(lua_State* l, std::function<Ret(Ty*, Args...)> func)
	{
		// get parameters from lua stack begin at bottom ( 1 ~ N )
		auto opt_parameters = to_tuple<std::shared_ptr<Ty>, std::remove_cvref_t<Args>...>(l);

		if(!opt_parameters)
		{
			std::clog << "[lua -> cpp] Parameters are not valid." << std::endl;
			lua_pushnil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_member_func_impl(func, opt_parameters.value(), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, std::forward<Ret>(
				call_cpp_member_func_impl(func, opt_parameters.value(), std::index_sequence_for<Args...>())
				));
			return 1;
		}
	}
	
	template<typename Ret, typename Ty, typename... Args>
	struct cpp_member_function_delegate
	{
		cpp_member_function_delegate(const std::string& name, Ret(Ty::* f)(Args...))
		{
			delegate_name = name;
			callable = f;
		}

		std::string delegate_name;
		std::function<Ret(Ty*, Args...)> callable;
	};
	

	//template<typename... ParamTypes, typename... RetTypes>
	//static std::tuple<RetTypes...> call_lua_function(lua_State* l, const std::string& func_name, ParamTypes&& ...args)
	//{
	//	// lua加载字符，生成lua全局函数LuaCode_MyAdd
	//	//luaL_dostring(l, "function LuaCode_MyAdd (x,y) return x+y end");
	//	// lua栈和压入数据
	//	lua_getglobal(l, func_name.c_str());

	//	(push(l, args), ...);
	//	//lua_pushinteger(l, 100);
	//	//lua_pushinteger(l, 200);
	//	
	//	// C调用lua中的函数，2个传入参数，1个返回参数
	//	lua_call(l, sizeof...(ParamTypes), sizeof...(RetTypes));

	//	auto results = to_tuple<RetTypes...>(l);

	//	//cout << "lua function ret:" << lua_tointeger(lua, -1) << endl;
	//	lua_pop(l, sizeof...(RetTypes));

	//	return results;
	//}
}

#endif