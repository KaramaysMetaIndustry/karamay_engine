#ifndef LVM_H
#define LVM_H

#include <format>

#include "lua_type_push.h"
#include "lua_type_is.h"
#include "lua_type_to.h"

#include <functional>
#include <iostream>

namespace lua_api
{

	namespace debug
	{
		static void trace(lua_State* l)
		{
			lua_Debug entry;
			int depth = 0; 

			while (lua_getstack(l, depth, &entry))
			{
				lua_getinfo(l, "Slntu", &entry);
				std::cout<< "" <<std::endl;
				
				printf("%s(%d): %s\n", entry.short_src, entry.currentline, entry.name ? entry.name : "?");
				++depth;
			}
		}
	}
	
	
	template<typename Ret, typename... Args, std::size_t... N>
	static Ret call_cpp_func_impl(const std::function<Ret(Args...)>& func, std::tuple<std::optional<std::remove_cvref_t<Args>>...>& parameters, std::index_sequence<N...>)
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
#if _DEBUG
		debug::trace(l);
#endif
		const auto vars = to_tuple<std::remove_cvref_t<Args>...>(l);

		if(!vars)
		{
			std::clog << "[lua -> cpp] parameters are not valid." << std::endl;
			lua_pushnil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_func_impl(func, vars.value(), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, call_cpp_func_impl(func, vars.value(), std::index_sequence_for<Args...>()));
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


	template<typename Ret, typename This, typename... Args, typename... OptArgs, std::size_t... N>
	static Ret call_cpp_member_func_impl(const std::function<Ret(This*, Args...)>& func, std::tuple<std::shared_ptr<This>, OptArgs...>& parameters, std::index_sequence<N...>)
	{
		if constexpr (std::is_void_v<Ret>)
		{
			func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		} else {
			return func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		}
	}
	
	template<typename Ret, typename This, typename... Args>
	static std::int32_t call_cpp_member_func(lua_State* l, std::function<Ret(This*, Args...)> func)
	{
#if _DEBUG
		debug::trace(l);
#endif
		// get parameters from lua stack begin at bottom ( 1 ~ N )
		const auto vars = to_tuple<std::shared_ptr<This>, std::remove_cvref_t<Args>...>(l);
		
		if(!vars)
		{
			std::clog << "[lua -> cpp] parameters are invalid." << std::endl;
			lua_pushnil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_member_func_impl(func, vars.value(), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, std::forward<Ret>(
				call_cpp_member_func_impl(func, vars.value(), std::index_sequence_for<Args...>())
				));
			return 1;
		}
	}
	
	template<typename Ret, typename This, typename... Args>
	struct cpp_member_function_delegate
	{
		cpp_member_function_delegate(const std::string& name, Ret(This::* f)(Args...))
		{
			delegate_name = name;
			callable = f;
		}

		std::string delegate_name;
		std::function<Ret(This*, Args...)> callable;
	};

	



	
	// template<typename... Args, typename... Rets>
	// static std::tuple<Rets...> call_lua_method(lua_State* l, const std::string_view method_name, Args&& ...args)
	// {
	// 	lua_getglobal(l, method_name.data());
	// 	(push(l, args), ...);
	// 	lua_call(l, sizeof...(Args), sizeof...(Rets));
	// 	const auto rets = to_tuple<Rets...>(l);
	// 	lua_pop(l, sizeof...(Rets));
	// 	return rets;
	// }
}

#endif