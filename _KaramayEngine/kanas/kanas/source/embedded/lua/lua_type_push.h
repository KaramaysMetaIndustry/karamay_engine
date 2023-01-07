#ifndef LUA_TYPE_PUSH_H
#define LUA_TYPE_PUSH_H

#include "public/lua.h"

#include "lua_type_def.h"
#include "lua_type_concepts.h"



namespace lua_api
{
    template<lua_t_acceptable T>
	void push(lua_State* l, T&& v)
	{
		if constexpr (lua_boolean_acceptable<T>)
		{
			lua_pushboolean(l, v);
		}
		else if constexpr (lua_integer_number_acceptable<T>)
		{
			lua_pushinteger(l, v);
		}
		else if constexpr (lua_real_number_acceptable<T>)
		{
			lua_pushnumber(l, v);
		}
		else if constexpr (lua_string_acceptable_c_style<T>)
		{
			lua_pushstring(l, v);
		}
		else if constexpr(lua_string_acceptable_std_str<T>)
		{
			lua_pushstring(l, v.c_str());
		}
		else if constexpr (lua_string_acceptable_std_str_view<T>)
		{
			lua_pushstring(l, v.data());
		}
		else if constexpr (lua_userdata_acceptable<T>)
		{
			void* userdata = lua_newuserdata(l, sizeof(std::remove_cvref_t<T>));
			new(userdata) std::remove_cvref_t<T>(v);
			
			luaL_setmetatable(l, lua_userdata_meta_info<std::remove_cvref_t<T>>::ref.get_type_name());
		}
	}

	template<typename ...Args>
	static void push_c_closure(lua_State* l, lua_CFunction f, Args&& ...args)
	{
		(push(l, args), ...);
		lua_pushcclosure(l, f, sizeof...(args));
	}

	template<lua_t_acceptable T, size_t size>
	static void push(lua_State* l, const std::array<T, size>& c) noexcept
	{
		// ...
		lua_createtable(l, size, 0);
		// table, ...
		for (size_t idx = 0; idx < size; ++idx)
		{
			push(l, idx + 1);
			// key, table, ...
			push(l, c[idx]);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template <lua_t_acceptable T, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::vector<T, allocator>& c) noexcept
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

	template<lua_t_acceptable T, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::deque<T, allocator>& c) noexcept
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

	template<lua_t_acceptable T, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::list<T, allocator>& c) noexcept
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

	template<lua_t_acceptable T, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::forward_list<T, allocator>& c) noexcept
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

	template<lua_t_acceptable T, typename predicate = std::less<T>, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::set<T, predicate, allocator>& c) noexcept
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

	template<lua_t_acceptable T, typename predicate = std::less<T>, typename allocator = std::allocator<T>>
	static void push(lua_State* l, const std::multiset<T, predicate, allocator>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *_it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<
		lua_t_acceptable T,
		typename hasher = std::hash<T>,
		typename predicate = std::equal_to<T>,
		typename allocator = std::allocator<T>
	>
	static void push(lua_State* l, const std::unordered_set<T, hasher, predicate, allocator>& c) noexcept
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

	template<
		lua_t_acceptable T,
		typename hasher = std::hash<T>,
		typename predicate = std::equal_to<T>,
		typename allocator = std::allocator<T>
	>
	static void push(lua_State* l, const std::unordered_multiset<T, hasher, predicate, allocator>& c) noexcept
	{
		// ...
		lua_createtable(l, c.size(), 0);
		// table, ...
		std::size_t idx = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++idx)
		{
			push(l, idx);
			// key, table, ...
			push(l, *_it);
			// value, key, table, ...
			lua_settable(l, -3);
			// table, ...
		}
	}

	template<
		lua_t_acceptable key_t, lua_t_acceptable value_t,
		typename predicate = std::less<key_t>,
		typename allocator = std::allocator<std::pair<const key_t, value_t>>
	>
	static void push(lua_State* l, const std::map<key_t, value_t, predicate, allocator>& c) noexcept
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

	template<
		lua_t_acceptable key_t, lua_t_acceptable value_t,
		typename hasher = std::hash<key_t>,
		typename predicate = std::equal_to<key_t>,
		typename allocator = std::allocator<std::pair<const key_t, value_t>>
	>
	static void push(lua_State* l, const std::unordered_map<key_t, value_t, hasher, predicate, allocator>& c) noexcept
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