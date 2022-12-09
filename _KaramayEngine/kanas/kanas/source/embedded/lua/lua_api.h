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
* 
* 
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

	/*
	* Ensures that the stack has space for at least n extra elements,
	* that is, that you can safely push up to n values into it.
	* It returns false if it cannot fulfill the request,
	* either because it would cause the stack to be greater than a fixed maximum size
	* (typically at least several thousand elements) or
	* because it cannot allocate memory for the extra space.
	* This function never shrinks the stack; if the stack already has space for the extra elements,
	* it is left unchanged.
	*/

	/*
	* Close all active to-be-closed variables in the main thread,
	* release all objects in the given Lua state (calling the corresponding garbage-collection metamethods, if any),
	* and frees all dynamic memory used by this state.
	* On several platforms, you may not need to call this function,
	* because all resources are naturally released when the host program ends.
	* On the other hand, long-running programs that create multiple states,
	* such as daemons or web servers, will probably need to close states as soon as they are not needed.
	*/

	/*
	* Compares two Lua values.
	* Returns 1 if the value at index index1 satisfies op when compared with the value at index index2,
	* following the semantics of the corresponding Lua operator (that is, it may call metamethods).
	* Otherwise, returns 0. Also returns 0 if any of the indices is not valid.
	*/

	/*
	* Concatenates the n values at the top of the stack, pops them, and leaves the result on the top.
	* If n is 1, the result is the single value on the stack (that is, the function does nothing);
	* if n is 0, the result is the empty string.
	* Concatenation is performed following the usual semantics of Lua.
	*/

	/*
	* Copies the element at index src_index into the valid index dst_index, replacing the value at that position.
	* Values at other positions are not affected.
	*/

	/*
	* Dumps a function as a binary chunk.
	* Receives a Lua function on the top of the stack and produces a binary chunk that,
	* if loaded again, results in a function equivalent to the one dumped.
	* As it produces parts of the chunk,
	* lua_dump calls function writer (see lua_Writer) with the given data to write them.
	* If strip is true, the binary representation may not include all debug information about the function, to save space.
	* The value returned is the error code returned by the last call to the writer;
	* 0 means no errors.
	* This function does not pop the Lua function from the stack.
	*/

	/*
	* Raises a Lua error, using the value on the top of the stack as the error object.
	* This function does a long jump, and therefore never returns (see luaL_error).
	*/

	/*
	* Returns the index of the top element in the stack.
	* Because indices start at 1, this result is equal to the number of elements in the stack; in particular, 0 means an empty stack.
	* @return stack top index (1 ~ N)
	*/

	/*
	* Accepts any index, or 0, and sets the stack top to this index.
	* If the new top is greater than the old one, then the new elements are filled with nil.
	* If index is 0, then all stack elements are removed.
	* This function can run arbitrary code when removing an index marked as to-be-closed from the stack.
	*/

	/*
	* Pops n elements from the stack. It is implemented as a macro over lua_settop.
	*/

	/*
	* Removes the element at the given valid index, 
	* shifting down the elements above this index to fill the gap. 
	* This function cannot be called with a pseudo-index, 
	* because a pseudo-index is not an actual stack position.
	*/

	/*
	* Moves the top element into the given valid index without shifting any element 
	* (therefore replacing the value at that given index),
	* and then pops the top element.
	*/

	/*
	* Rotates the stack elements between the valid index idx and the top of the stack. 
	* The elements are rotated n positions in the direction of the top, for a positive n, or -n positions 
	* in the direction of the bottom, for a negative n. 
	* The absolute value of n must not be greater than the size of the slice being rotated. 
	* This function cannot be called with a pseudo-index, because a pseudo-index is not an actual stack position.
	*/

	/*
	* Returns the type of the value in the given valid index, 
	* or LUA_TNONE for a non-valid but acceptable index. 
	* The types returned by lua_type are coded by the following constants defined in lua.h: 
	* NIL, THREAD, 
	* NUMBER, BOOLEAN,  STRING,  TABLE, 
	* FUNCTION,  USERDATA, LIGHTUSERDATA
	*/
	static lua_t type(lua_State* l, std::int32_t idx)
	{
		return static_cast<lua_t>(lua_type(l, idx));
	}

	// [array], vector, list, forward_list, deque,
	// set, unordered_set, multiset, unordered_multiset
	// map, unordered_map, [ multimap, unordered_multimap]
	// [stack, queue]

	// bool, uint8/16/32/64, int8/16/32/64, float, double, 
	// const char*, std::string
	// void*, const void*

	//  nil, thread,
	// boolean, number, string, 
	// userdata, 
	// table,
	// function
	
	// concepts

	// boolean
	template<class T>
	concept lua_boolean_acceptable =
		std::is_same_v<bool, T>;

	// number
	template<class T>
	concept lua_integer_number_acceptable =
		std::_Is_any_of_v<std::remove_cv_t<T>, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t>;

	template<typename T>
	concept lua_real_number_acceptable = 
		std::_Is_any_of_v<std::remove_cv_t<T>, std::float_t, std::double_t>;
	
	template<typename T>
	concept lua_number_acceptable =
		lua_integer_number_acceptable<T> or lua_real_number_acceptable<T>;

	// string
	template<typename T>
	concept lua_string_acceptable_c_style =
		std::is_same_v<T, const char*>;

	template<typename T>
	concept lua_string_acceptable_std_str =
		std::_Is_any_of_v<std::remove_cv_t<T>, std::string>;

	template<typename T>
	concept lua_string_acceptable_std_str_view = 
		std::_Is_any_of_v<std::remove_cv_t<T>, std::string_view>;
	
	template<typename T>
	concept lua_string_acceptable =
		lua_string_acceptable_c_style<T> or lua_string_acceptable_std_str<T> or lua_string_acceptable_std_str_view<T>;

	// userdata
	template<typename T>
	constexpr bool is_shared_ptr_v = false;

	template<typename T>
	constexpr bool is_shared_ptr_v<std::shared_ptr<T>> = true;

	

	template<typename T>
	constexpr bool is_lua_exporter_registered = false;

	template<typename T>
	concept has_lua_exporter = is_lua_exporter_registered<T>;
	
	
	template<typename T>
	concept lua_userdata_acceptable =
		is_shared_ptr_v<T>;
	
	// types 
	template<typename T>
	concept lua_t_acceptable =
		lua_boolean_acceptable<T> or lua_number_acceptable<T> or lua_string_acceptable<T> or lua_userdata_acceptable<T>;
	
	template<typename Ty>
	struct lua_userdata_meta_info
	{
		const char* get_type_name()
		{
			return "nullptr";
		}

		static lua_userdata_meta_info ref;

	};

	/*template<typename Ty>
	struct lua_userdata_meta_info<std::shared_ptr<Ty>>
	{
		constexpr const char* typename_name = 
	};*/

	template<lua_t_acceptable T>
	void push(lua_State* l, T v)
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
			void* userdata = lua_newuserdata(l, sizeof(T));
			new(userdata) T(v);
			//auto _object = static_cast<T*>(new(userdata) T);
			//*_object = v;
			luaL_setmetatable(l, lua_userdata_meta_info<T>::ref.get_type_name());
		}
	}
	
	/**
	 *lua (light)userdata
	 */
	// template<typename T>
	// static void push(const T* value)
	// {
	// 	static_assert(std::is_class_v<T>, "must be class or struct pointer");
	// 	lua_pushlightuserdata(l.get(), reinterpret_cast<void*>(value));
	// 	/*if (!luaL_testudata(l, -1, ""))
	// 	{
	// 		luaL_setmetatable(l, "");
	// 	}*/
	// }

	static void push_nil(lua_State* l)
	{
		lua_pushnil(l);
	}
	static void push_table(lua_State* l)
	{
		lua_pushglobaltable(l);
	}
	static void push_thread(lua_State* l)
	{
		lua_pushthread(l);
	}

	template<typename ...Args>
	static void push_c_closure(lua_State* l, lua_CFunction&& f, Args&& ...args)
	{
		(push(l, args), ...);
		lua_pushcclosure(l, f, sizeof...(args));
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
			T* userdata = static_cast<T*>(lua_touserdata(l, idx)); //luaL_testudata
			return *userdata;
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

	
	/*
	* std container => lua table
	* 
	*/
	// template<typename t, size_t size> 
	// static void push(const std::array<t, size>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(size, 0);
	// 	// table, ...
	// 	for (size_t idx = 0; idx < size; ++idx)
	// 	{
	// 		push(idx + 1);
	// 		// key, table, ...
	// 		push(c[idx]);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template <typename t, typename allocator = std::allocator<t>> 
	// static void push(const std::vector<t, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(c.size(), 0);
	// 	// table, ...
	// 	for (std::size_t idx = 0; idx < c.size(); ++idx)
	// 	{
	// 		push(idx + 1);
	// 		// key, table, ...
	// 		push(c[idx]);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }

	// template<typename t, typename allocator = std::allocator<t>> 
	// static void push(const std::deque<t, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(l, c.size(), 0);
	// 	// table, ...
	// 	for (std::size_t _index = 0; _index < c.size(); ++_index)
	// 	{
	// 		push(_index + 1);
	// 		// key, table, ...
	// 		push(c[_index]);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<typename t, typename allocator = std::allocator<t>>
	// static void push(const std::list<t, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(c.size(), 0);
	// 	// table, ...
	// 	size_t _idx = 1;
	// 	for (auto it = c.cbegin(); it != c.cend(); ++it, ++_idx)
	// 	{
	// 		push(_idx);
	// 		// key, table, ...
	// 		push(l, *it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<typename t, typename allocator = std::allocator<t>>
	// static void push(const std::forward_list<t, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table();
	// 	// table, ...
	// 	size_t _index = 1;
	// 	for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
	// 	{
	// 		push(_index);
	// 		// key, table, ...
	// 		push(*it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<typename t, typename predicate = std::less<t>, typename allocator = std::allocator<t>>
	// static void push(const std::set<t, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(c.size(), 0);
	// 	// table, ...
	// 	std::size_t _index = 1;
	// 	for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
	// 	{
	// 		push(_index);
	// 		// key, table, ...
	// 		push(*it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<typename t, typename predicate = std::less<t>, typename allocator = std::allocator<t>> 
	// static void push(const std::multiset<t, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(c.size(), 0);
	// 	// table, ...
	// 	std::size_t _index = 1;
	// 	for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
	// 	{
	// 		push(_index);
	// 		// key, table, ...
	// 		push(*_it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<
	// 	typename t,
	// 	typename hasher = std::hash<t>,
	// 	typename predicate = std::equal_to<t>,
	// 	typename allocator = std::allocator<t>
	// >
	// static void push(const std::unordered_set<t, hasher, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(l, c.size(), 0);
	// 	// table, ...
	// 	std::size_t _index = 1;
	// 	for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
	// 	{
	// 		push(_index);
	// 		// key, table, ...
	// 		push(l, *it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<
	// 	typename t,
	// 	typename hasher = std::hash<t>,
	// 	typename predicate = std::equal_to<t>,
	// 	typename allocator = std::allocator<t>
	// >
	// static void push(const std::unordered_multiset<t, hasher, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(l, c.size(), 0);
	// 	// table, ...
	// 	std::size_t _index = 1;
	// 	for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
	// 	{
	// 		push(_index);
	// 		// key, table, ...
	// 		push(l, *_it);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<
	// 	typename key_t, typename value_t,
	// 	typename predicate = std::less<key_t>, 
	// 	typename allocator = std::allocator<std::pair<const key_t, value_t>>
	// > 
	// static void push(const std::map<key_t, value_t, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(0, c.size());
	// 	// table, ...
	// 	for (const auto& pair : c)
	// 	{
	// 		push(pair.first);
	// 		// key, table, ...
	// 		push(pair.second);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	//
	// template<
	// 	typename key_t, typename value_t, 
	// 	typename hasher = std::hash<key_t>,
	// 	typename predicate = std::equal_to<key_t>,
	// 	typename allocator = std::allocator<std::pair<const key_t, value_t>>
	// > 
	// static void push(const std::unordered_map<key_t, value_t, hasher, predicate, allocator>& c) noexcept
	// {
	// 	// ...
	// 	basic::create_table(0, c.size());
	// 	// table, ...
	// 	for (const auto& pair : c)
	// 	{
	// 		push(pair.first);
	// 		// key, table, ...
	// 		push(pair.second);
	// 		// value, key, table, ...
	// 		basic::set_table(-3);
	// 		// table, ...
	// 	}
	// }
	
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
	// static bool to(std::int32_t index, std::vector<t>& c) noexcept
	// {
	// 	// if (!basic::is_type(index, lua_t::table))
	// 	// {
	// 	// 	return false;
	// 	// }
	//
	// 	if (!helper::is_table_vectorizable(index))
	// 	{
	// 		return false;
	// 	}
	// 	
	// 	auto len = basic::raw_len(index);
	// 	if (len < 1)
	// 	{
	// 		return true;
	// 	}
	//
	// 	c.reserve(len);
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
	// template<
	// 	typename key_t, typename value_t,
	// 	typename hasher = std::hash<key_t>,
	// 	typename predicate = std::equal_to<key_t>,
	// 	typename allocator = std::allocator<std::pair<const key_t, value_t>>
	// > 
	// static bool to(std::int32_t index, std::unordered_map<key_t, value_t, hasher, predicate, allocator>& c) noexcept
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
	// 		auto _optional_k = to<key_t>(l, -2);
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

	template<typename ...Args, std::size_t... N, bool bottom = true, std::size_t offset = 0>
	static std::optional<std::tuple<Args...>> to_tuple_impl(lua_State* l, std::index_sequence<N...>)
	{
		// check the parameters num
		if (lua_gettop(l) != sizeof...(Args))
		{
			return std::nullopt;
		}

		std::tuple<std::optional<Args>...> opt_parameters;

		// (N + 1 + offset) * (bottom ? 1 : -1)
		((std::get<N>(opt_parameters) = static_to<Args, (N + 1 + offset)* (bottom ? 1 : -1)>(l)), ...);

		bool is_ok = true;

		((is_ok = (is_ok ? std::get<N>(opt_parameters).has_value() : false)), ...);

		if(!is_ok)
		{
			return std::nullopt;
		}
		
		std::tuple<Args...> parameters;
		
		((std::get<N>(parameters) = std::get<N>(opt_parameters).value()), ...);
		
		return parameters;
	}

	template<typename ...Args>
	static std::optional<std::tuple<Args...>> to_tuple(lua_State* l)
	{
		return to_tuple_impl<Args...>(l, std::index_sequence_for<Args...>());
	}

	
	template<typename Ret, typename... Args, typename... TupleArgs, std::size_t... N>
	static Ret call_cpp_func_impl(const std::function<Ret(Args...)>& func, std::tuple<TupleArgs...>&& parameters, std::index_sequence<N...>)
	{
		if constexpr (std::is_void_v<Ret>)
		{
			func(std::get<N>(parameters)...);
		} else {
			return func(std::get<N>(parameters) ...);
		}
	}

	template<typename Ret, typename... Args>
	static std::int32_t call_cpp_func(lua_State* l, std::function<Ret(Args...)> func)
	{
		// get parameters from lua stack begin at bottom ( 1 ~ N )
		auto parameters = to_tuple<std::remove_cvref_t<Args>...>(l);

		if(!parameters.has_value())
		{
			//luaL_execresult()
			//luaL_error(l, "loading parameters failed");
			std::clog << "parameters are not valid" << std::endl;
			push_nil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_func_impl(func, std::move(parameters.value()), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, call_cpp_func_impl(func, std::move(parameters.value()), std::index_sequence_for<Args...>()));
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
	static Ret call_cpp_member_func_impl(const std::function<Ret(Ty*, Args...)>& func, std::tuple<std::shared_ptr<Ty>, TupleArgs...>&& parameters, std::index_sequence<N...>)
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

		if(!opt_parameters.has_value())
		{
			//luaL_error(l, "loading parameters failed.");
			std::clog << "parameters are not valid" << std::endl;
			push_nil(l);
			return 1;
		}
		
		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_member_func_impl(func, std::move(opt_parameters.value()), std::index_sequence_for<Args...>());
			return 0;
		} else {
			// if the func has return result, push it into the stack
			lua_api::push(l, call_cpp_member_func_impl(func, std::move(opt_parameters.value()), std::index_sequence_for<Args...>()));
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

	template<typename Ret, typename Ty, typename... Args>
	struct cpp_member_function_raw
	{
		std::function<Ret(Ty*, Args...)> callable;
	};

	template<typename... FuncTypes>
	struct cpp_member_function_delegate_tuple
	{
		cpp_member_function_delegate_tuple(std::string&& delegate_name, FuncTypes&&... funcs) :
			name(delegate_name),
			functions(funcs...)
		{}

		std::string name;
		std::tuple<FuncTypes...> functions;
	};

	template<typename Ret, typename Ty, typename... Args, typename... TupleArgs, std::size_t... N>
	static Ret call_cpp_member_func_multi_impl(const std::function<Ret(Ty*, Args...)>& func, std::tuple<std::shared_ptr<Ty>, TupleArgs...>&& parameters, std::index_sequence<N...>)
	{
		if constexpr (std::is_void_v<Ret>)
		{
			func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		}
		else {
			return func(std::get<0>(parameters).get(), std::get<N + 1>(parameters)...);
		}
	}

	template<typename Ret, typename Ty, typename... Args>
	static std::int32_t call_cpp_member_func_multi(lua_State* l, std::function<Ret(Ty*, Args...)> func)
	{
		// get parameters from lua stack begin at bottom ( 1 ~ N )
		auto opt_parameters = to_tuple<std::shared_ptr<Ty>, std::remove_cvref_t<Args>...>(l);

		if (!opt_parameters.has_value())
		{
			luaL_error(l, "loading parameters failed.");
			return 0;
		}

		if constexpr (std::is_void_v<Ret>)
		{
			call_cpp_member_func_impl(func, std::move(opt_parameters.value()), std::index_sequence_for<Args...>());
			return 0;
		}
		else {
			// if the func has return result, push it into the stack
			lua_api::push(l, call_cpp_member_func_impl(func, std::move(opt_parameters.value()), std::index_sequence_for<Args...>()));
			return 1;
		}
	}
	
}

#endif