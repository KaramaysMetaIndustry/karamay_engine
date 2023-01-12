#ifndef LUA_TYPE_PUSH_H
#define LUA_TYPE_PUSH_H

#include "public/lua.h"

#include "lua_type_def.h"
#include "lua_type_concepts.h"

namespace lua_api
{

	template<lua_boolean_acceptable T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushboolean(l, v);
	}

	template<lua_integer_number_acceptable T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushinteger(l, v);
	}

	template<lua_real_number_acceptable T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushnumber(l, v);
	}

	template<lua_string_acceptable_c_style T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushstring(l, v);
	}

	template<lua_string_acceptable_std_str T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushstring(l, v.c_str());
	}

	template<lua_string_acceptable_std_str_view T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		lua_pushstring(l, v.data());
	}

	template<lua_userdata_acceptable T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		using raw_t = std::remove_cvref_t<T>;
		
		void* userdata = lua_newuserdata(l, sizeof(raw_t));
		new(userdata) std::remove_cvref_t<T>(v);
		luaL_setmetatable(l, lua_userdata_meta_info<raw_t>::ref.get_type_name());
	}


	template<typename ...Args>
	static void push_c_closure(lua_State* l, lua_CFunction f, Args&& ...args)
	{
		(push(l, args), ...);
		lua_pushcclosure(l, f, sizeof...(args));
	}
	
	template<lua_closure_acceptable T>
	static void push_impl(lua_State* l, T&& v) noexcept
	{
		push_c_closure(l, v.f, v.args);
	}
	

    template<lua_t_acceptable T>
	static void push(lua_State* l, T&& v) noexcept
	{
		push_impl(l, v);
	}
	
	
	template<lua_t_acceptable T, size_t Size>
	static void push(lua_State* l, const std::array<T, Size>& c) noexcept
	{
		// ...
		lua_createtable(l, Size, 0);
		// table, ...
		for (size_t idx = 0; idx < Size; ++idx)
		{
			push(l, idx + 1);
			// key, table, ...
			push(l, c[idx]);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template <lua_t_acceptable T, typename AllocatorT>
	static void push(lua_State* l, const std::vector<T, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, static_cast<int>(c.size()), 0);
		// table, ...
		for (std::size_t idx = 0; idx < c.size(); ++idx)
		{
			push(l, idx + 1);
			// key, table, ...
			push(l, c[idx]);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename AllocatorT>
	static void push(lua_State* l, const std::deque<T, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		for (std::size_t idx = 0; idx < c.size(); ++idx)
		{
			push(l, idx + 1);
			// key, table, ...
			push(l, c[idx]);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename AllocatorT>
	static void push(lua_State* l, const std::list<T, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		size_t idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename AllocatorT>
	static void push(lua_State* l, const std::forward_list<T, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, 0, 0);
		// table, ...
		size_t idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::set<T, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::multiset<T, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename HasherT, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::unordered_set<T, HasherT, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable T, typename HasherT, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::unordered_multiset<T, HasherT, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto id = c.cbegin(); id != c.cend(); ++id, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *id);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable KeyT, lua_t_acceptable ValueT, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::map<KeyT, ValueT, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, 0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(l, pair.first);
			// key, table, ...
			push(l, pair.second);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<lua_t_acceptable KeyT, lua_t_acceptable ValueT, typename HasherT, typename PredicateT, typename AllocatorT>
	static void push(lua_State* l, const std::unordered_map<KeyT, ValueT, HasherT, PredicateT, AllocatorT>& c) noexcept
	{
		// ...
		lua_createtable(l, 0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(l, pair.first);
			// key, table, ...
			push(l, pair.second);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}
	
}

#endif