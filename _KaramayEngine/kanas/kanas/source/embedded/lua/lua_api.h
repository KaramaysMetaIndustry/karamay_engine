#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/lua.h"

/*
* cpp data <=> lua data
* 
* bool <=> boolean
* uint8, uint16, uint32, uint64, int8, int16, int32, int64 <=> integer
* float, double <=> number
* c-style string, std::string <=> string
* void*, const void* <=> userdata
* lua_CFuntion <=> function
* std::containers <=> tables
*
*/
namespace lua_api
{
	enum class lua_t : int
	{
		none = LUA_TNONE,
		nil = LUA_TNIL, //nil
		boolean = LUA_TBOOLEAN, // boolean
		number = LUA_TNUMBER, // number
		string = LUA_TSTRING, // string
		function = LUA_TFUNCTION, // function
		table = LUA_TTABLE, // table
		userdata = LUA_TUSERDATA, // userdata
		light_userdata = LUA_TLIGHTUSERDATA, // userdata
		thread = LUA_TTHREAD, // thread
		num_types = LUA_NUMTYPES
	};

	enum class lua_status : int
	{
		ok = LUA_OK, // no errors.
		err_run = LUA_ERRRUN, // a runtime error.
		err_mem = LUA_ERRMEM, // memory allocation error.For such errors, Lua does not call the message handler.
		err_err = LUA_ERRERR, // error while running the message handler.
		err_syntax = LUA_ERRSYNTAX, // syntax error during precompilation.
		yield = LUA_YIELD, // the thread(coroutine) yields.
		err_file = LUA_ERRFILE // a file - related error; e.g., it cannot open or read the file.
	};

	enum class lua_compare_op : int
	{
		eq = LUA_OPEQ, // ==
		lt = LUA_OPLT, // <
		le = LUA_OPLE // <=
	};

	enum class lua_gc_option : int
	{
		gc_collect = LUA_GCCOLLECT, //Performs a full garbage - collection cycle.
		gc_stop = LUA_GCSTOP, //Stops the garbage collector.
		gc_restart = LUA_GCRESTART, //Restarts the garbage collector.
		gc_count = LUA_GCCOUNT, //Returns the current amount of memory(in Kbytes) in use by Lua.
		gc_count_b = LUA_GCCOUNTB, //Returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
		gc_step = LUA_GCSTEP, //Performs an incremental step of garbage collection, corresponding to the allocation of stepsize Kbytes.
		gc_is_running = LUA_GCISRUNNING, //Returns a boolean that tells whether the collector is running(i.e., not stopped).
		gc_inc = LUA_GCINC, //Changes the collector to incremental mode with the given parameters(see ��2.5.1).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
		gc_gen = LUA_GCGEN //Changes the collector to generational mode with the given parameters(see ��2.5.2).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
	};

	static lua_t type(lua_State* l, std::int32_t idx)
	{
		return static_cast<lua_t>(lua_type(l, idx));
	}
	
	// concepts
	template<class T>
	concept lua_boolean_acceptable =
		std::is_same_v<std::remove_cvref_t<T>, bool>;

	template<class T>
	concept lua_integer_number_acceptable =
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t>;

	template<typename T>
	concept lua_real_number_acceptable = 
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::float_t, std::double_t>;
	
	template<typename T>
	concept lua_number_acceptable =
		lua_integer_number_acceptable<T> or lua_real_number_acceptable<T>;

	template<typename T>
	concept lua_string_acceptable_c_style =
		std::is_same_v<T, const char*>;

	template<typename T>
	concept lua_string_acceptable_std_str =
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::string>;

	template<typename T>
	concept lua_string_acceptable_std_str_view = 
		std::_Is_any_of_v<std::remove_cvref_t<T>, std::string_view>;
	
	template<typename T>
	concept lua_string_acceptable =
		lua_string_acceptable_c_style<T> or lua_string_acceptable_std_str<T> or lua_string_acceptable_std_str_view<T>;

	template<typename T>
	constexpr bool is_shared_ptr_v = false;

	template<typename T>
	constexpr bool is_shared_ptr_v<std::shared_ptr<T>> = true;
	
	
	template<typename T>
	concept lua_userdata_acceptable =
		is_shared_ptr_v<std::remove_cvref_t<T>>;
	
	template<typename T>
	concept lua_t_acceptable_non_container =
		lua_boolean_acceptable<T> or lua_number_acceptable<T> or lua_string_acceptable<T> or lua_userdata_acceptable<T>;
	

	template<typename T>
	constexpr bool is_array_v = false;

	template<typename T, std::size_t size>
	constexpr bool is_array_v<std::array<T, size>> = true;


	template<typename T>
	constexpr bool is_vector_v = false;

	template<typename T>
	constexpr bool is_vector_v<std::vector<T>> = true;

	template<typename T, typename U>
	constexpr bool is_vector_v<std::vector<T, U>> = true;


	template<typename T>
	constexpr bool is_deque_v = false;

	template<typename T>
	constexpr bool is_deque_v<std::deque<T>> = true;

	template<typename T, typename U>
	constexpr bool is_deque_v<std::deque<T, U>> = true;


	template<typename T>
	constexpr bool is_list_v = false;

	template<typename T>
	constexpr bool is_list_v<std::list<T>> = true;

	template<typename T, typename U>
	constexpr bool is_list_v<std::list<T, U>> = true;


	template<typename T>
	constexpr bool is_forward_list_v = false;

	template<typename T>
	constexpr bool is_forward_list_v<std::forward_list<T>> = true;

	template<typename T, typename U>
	constexpr bool is_forward_list_v<std::forward_list<T, U>> = true;


	template<typename T>
	constexpr bool is_stack_v = false;

	template<typename T>
	constexpr bool is_stack_v<std::stack<T>> = true;

	template<typename T, typename U>
	constexpr bool is_stack_v<std::stack<T, U>> = true;


	template<typename T>
	constexpr bool is_queue_v = false;

	template<typename T>
	constexpr bool is_queue_v<std::queue<T>> = true;

	template<typename T, typename U>
	constexpr bool is_queue_v<std::queue<T, U>> = true;


	template<typename T>
	constexpr bool is_priority_queue_v = false;

	template<typename T>
	constexpr bool is_priority_queue_v<std::priority_queue<T>> = true;

	template<typename T, typename U>
	constexpr bool is_priority_queue_v<std::priority_queue<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_priority_queue_v<std::priority_queue<T, U, W>> = true;


	template<typename T>
	constexpr bool is_set_v = false;

	template<typename T>
	constexpr bool is_set_v<std::set<T>> = true;

	template<typename T, typename U>
	constexpr bool is_set_v<std::set<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_set_v<std::set<T, U, W>> = true;


	template<typename T>
	constexpr bool is_unordered_set_v = false;

	template<typename T>
	constexpr bool is_unordered_set_v<std::unordered_set<T>> = true;

	template<typename T, typename U>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_set_v<std::unordered_set<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_multiset_v = false;

	template<typename T>
	constexpr bool is_multiset_v<std::multiset<T>> = true;

	template<typename T, typename U>
	constexpr bool is_multiset_v<std::multiset<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_multiset_v<std::multiset<T, U, W>> = true;


	template<typename T>
	constexpr bool is_unordered_multiset_v = false;

	template<typename T>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T>> = true;

	template<typename T, typename U>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_multiset_v<std::unordered_multiset<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_map_v = false;

	template<typename T, typename U>
	constexpr bool is_map_v<std::map<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_map_v<std::map<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_map_v<std::map<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_multimap_v = false;

	template<typename T, typename U>
	constexpr bool is_multimap_v<std::multimap<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_multimap_v<std::multimap<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_multimap_v<std::multimap<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_unordered_map_v = false;

	template<typename T, typename U>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_map_v<std::unordered_map<T, U, W, X>> = true;


	template<typename T>
	constexpr bool is_unordered_multimap_v = false;

	template<typename T, typename U>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U>> = true;

	template<typename T, typename U, typename W>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U, W>> = true;

	template<typename T, typename U, typename W, typename X>
	constexpr bool is_unordered_multimap_v<std::unordered_multimap<T, U, W, X>> = true;


	template<typename T>
	concept lua_table_acceptable_std_array =
		is_array_v<T> && 
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_vector =
		is_vector_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_stack =
		is_stack_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_queue =
		is_queue_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_priority_queue =
		is_priority_queue_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_deque =
		is_deque_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_list =
		is_list_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_forward_list =
		is_forward_list_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_set =
		is_set_v<T> && 
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_set =
		is_unordered_set_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_multiset =
		is_multiset_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_multiset =
		is_unordered_multiset_v<T> &&
		lua_t_acceptable_non_container<typename T::value_type>;

	template<typename T>
	concept lua_table_acceptable_std_map = 
		is_map_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_map =
		is_unordered_map_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_multimap = 
		is_multimap_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;

	template<typename T>
	concept lua_table_acceptable_std_unordered_multimap =
		is_unordered_multimap_v<T> &&
		lua_t_acceptable_non_container<typename T::key_type> &&
		lua_t_acceptable_non_container<typename T::mapped_type>;


	template<typename T>
	concept lua_t_acceptable = 
		lua_t_acceptable_non_container<T> or 
		lua_table_acceptable_std_array<T> or
		lua_table_acceptable_std_vector<T> or
		lua_table_acceptable_std_stack<T> or
		lua_table_acceptable_std_queue<T> or
		lua_table_acceptable_std_priority_queue<T> or
		lua_table_acceptable_std_deque<T> or
		lua_table_acceptable_std_list<T> or
		lua_table_acceptable_std_forward_list<T> or
		lua_table_acceptable_std_set<T> or
		lua_table_acceptable_std_unordered_set<T> or
		lua_table_acceptable_std_multiset<T> or
		lua_table_acceptable_std_unordered_multiset<T> or
		lua_table_acceptable_std_map<T> or
		lua_table_acceptable_std_unordered_map<T> or
		lua_table_acceptable_std_multimap<T> or
		lua_table_acceptable_std_unordered_multimap<T>;
	
	template<typename Ty>
	struct lua_userdata_meta_info
	{
		const char* get_type_name()
		{
			return "nullptr";
		}

		static lua_userdata_meta_info ref;

	};

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

	
	template<lua_t_acceptable T>
	static bool is(lua_State* l, std::int32_t idx) noexcept
	{
		if constexpr (lua_boolean_acceptable<T>)
		{
			return lua_isboolean(l, idx);
		}
		else if constexpr (lua_integer_number_acceptable<T>)
		{
			return lua_isinteger(l, idx);
		}
		else if constexpr (lua_real_number_acceptable<T>)
		{
			return lua_isnumber(l, idx);
		}
		else if constexpr (lua_string_acceptable<T>)
		{
			return lua_isstring(l, idx) && !lua_isnumber(l, idx);
		}
		else if constexpr (lua_userdata_acceptable<T>)
		{
			return lua_isuserdata(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_array<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_vector<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_deque<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_list<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_forward_list<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_set<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_unordered_set<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_unordered_multiset<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_map<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_unordered_map<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_multimap<T>)
		{
			return lua_istable(l, idx);
		}
		else if constexpr (lua_table_acceptable_std_unordered_multimap<T>)
		{
			return lua_istable(l, idx);
		}
		else
		{
			return false;
		}
	}


	template<lua_t_acceptable T>
	static std::optional<T> to(lua_State* l, std::int32_t idx)
	{
		if(!is<T>(l, idx)) {
			return std::nullopt;
		}

		if constexpr (lua_boolean_acceptable<T>) {
			return static_cast<T>(lua_toboolean(l, idx));
		}
		else if constexpr (lua_integer_number_acceptable<T>) {
			return static_cast<T>(lua_tointeger(l, idx));
		}
		else if constexpr (lua_real_number_acceptable<T>) {
			return static_cast<T>(lua_tonumber(l, idx));
		}
		else if constexpr (lua_string_acceptable<T>) {
			return lua_tostring(l, idx);
		}
		else if constexpr (lua_userdata_acceptable<T>) {
			T* userdata = static_cast<T*>(lua_touserdata(l, idx));
			return *userdata;
		}
		else if constexpr (lua_table_acceptable_std_vector<T>) {
			const auto len = static_cast<std::size_t>(lua_rawlen(l, idx));
			if (len < 1)
			{
				return std::nullopt;
			}

			// table, ...
			lua_pushnil(l);
			// key, table, ...

			T c;
			c.reserve(len);

			while (lua_next(l, idx))
			{
				// value, key, table, ...
				auto v = to<typename T::value_type>(l, -1);
				if (!v)
				{
					lua_pop(l, 2);
					// table, ...
					return std::nullopt;
				}

				c.push_back(v.value());
				lua_pop(l, 1);
				// key, table, ...
			}
			// table, ...
			return c;
		}
		else if constexpr (lua_table_acceptable_std_unordered_map<T>)
		{
			T c;

			// table, ...
			lua_pushnil(l);
			// nil, table, ...
			while (lua_next(l, idx))
			{
				// value, key, table, ...
				auto _optional_k = to<typename T::key_type>(l, -2);
				auto _optional_v = to<typename T::mapped_type>(l, -1);
				if (!_optional_k || !_optional_v)
				{
					lua_pop(l, 2);
					// table, ...
					return std::nullopt;
				}
				c.emplace(_optional_k.value(), _optional_v.value());
				lua_pop(l, 1);
				// key, table, ...
			}
			// table, ...
			return c;
		}
		else {
			return std::nullopt;
		}
	}

	template<lua_t_acceptable T, std::size_t idx>
	static std::optional<T> static_to(lua_State* l)
	{
		return to<T>(l, idx);
	}
	
	// template<typename t, size_t size> 
	// static bool to(std::int32_t index, std::array<t, size>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	const auto _table_len = basic::raw_len(index);
	// 	if (_table_len != size)
	// 	{
	// 		return false;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	size_t _array_index = 0;
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ....
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ....
	// 			return false;
	// 		}
	// 		c[_array_index++] = _optional_v.value();
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//

	// template <typename t> 
	// static bool to(std::int32_t index, std::deque<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	const auto table_len = basic::raw_len(index);
	// 	if (table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// key, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.push_back(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<typename t> 
	// static bool to(std::int32_t index, std::list<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			return false;
	// 		}
	// 		c.push_back(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<typename t> 
	// static bool to(std::int32_t index, std::forward_list<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.push_front(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, value, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<typename t> 
	// static bool to(std::int32_t index, std::set<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	size_t _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ....
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.insert(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<typename t> 
	// static bool to(std::int32_t index, std::multiset<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.insert(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true; 
	// }
	//
	// template<typename t> 
	// static bool to(lua_State* l, std::int32_t index, std::unordered_set<t>& c)  noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(l, -1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.insert(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, value, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<typename t> 
	// static bool to(std::int32_t index, std::unordered_multiset<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_v = to<t>(-1);
	// 		if (!_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.insert(_optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	// template<
	// 	typename key_t, typename value_t,
	// 	typename predicate = std::less<key_t>,
	// 	typename allocator = std::allocator<std::pair<const key_t, value_t>>
	// > 
	// static bool to(std::int32_t index, std::map<key_t, value_t, predicate, allocator>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	auto _table_len = basic::raw_len(index);
	// 	if (_table_len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	// table, ...
	// 	basic::push_nil();
	// 	// nil, table, ...
	// 	while (basic::table_next(index))
	// 	{
	// 		// value, key, table, ...
	// 		auto _optional_k = to<key_t>(l, -1);
	// 		auto _optional_v = to<value_t>(l, -1);
	// 		if (!_optional_k.has_value() || !_optional_v.has_value())
	// 		{
	// 			basic::pop(2);
	// 			// table, ...
	// 			return false;
	// 		}
	// 		c.emplace(_optional_k.value(), _optional_v.value());
	// 		basic::pop(1);
	// 		// key, table, ...
	// 	}
	// 	// table, ...
	// 	return true;
	// }
	//
	 template<
	 	typename key_t, typename value_t,
	 	typename hasher = std::hash<key_t>,
	 	typename predicate = std::equal_to<key_t>,
	 	typename allocator = std::allocator<std::pair<const key_t, value_t>>
	 > 
	 static bool to(std::int32_t index, std::unordered_map<key_t, value_t, hasher, predicate, allocator>& c) noexcept
	 {
	 	// if (!basic::is_type(index, lua_t::table))
	 	// {
	 	// 	return false;
	 	// }
	
	 	
	 }

	template<typename... Args, std::size_t... N, bool bottom = true, std::size_t offset = 0>
	static std::optional<std::tuple<Args...>> to_tuple_impl(lua_State* l, std::index_sequence<N...>)
	{
		if (lua_gettop(l) != sizeof...(Args))
		{
			return std::nullopt;
		}

		std::tuple<std::optional<Args>...> opt_parameters =
		{
			static_to<Args, (N + 1 + offset) * (bottom ? 1 : -1)>(l)...
		};

		bool is_ok = true;

		( ( is_ok = ( is_ok ? std::get<N>(opt_parameters).has_value() : false ) ), ... );

		if( !is_ok )
		{
			return std::nullopt;
		}
		
		return { { (std::get<N>(opt_parameters).value())... } };
	}

	template<typename ...Args>
	static std::optional<std::tuple<Args...>> to_tuple(lua_State* l)
	{
		return to_tuple_impl<Args...>(l, std::index_sequence_for<Args...>());
	}

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
			std::clog << "[Lua -> Cpp] Parameters are not valid." << std::endl;
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
			std::clog << "[Lua -> Cpp] Parameters are not valid." << std::endl;
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