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
	struct lua_machine
	{
		lua_State* state_;

		lua_State* get() {return state_;}

		lua_machine()
		{
			state_ = luaL_newstate();
		}

		~lua_machine()
		{
			lua_close(state_);
		}
	};

	static lua_machine l = {};

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

	namespace basic
	{
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
		static bool check_stack(std::int32_t n)
		{
			return lua_checkstack(l.get(), n) == 1;
		}

		static lua_State* new_state()
		{
			return luaL_newstate();
		}

		/*
		* Close all active to-be-closed variables in the main thread,
		* release all objects in the given Lua state (calling the corresponding garbage-collection metamethods, if any),
		* and frees all dynamic memory used by this state.
		* On several platforms, you may not need to call this function,
		* because all resources are naturally released when the host program ends.
		* On the other hand, long-running programs that create multiple states,
		* such as daemons or web servers, will probably need to close states as soon as they are not needed.
		*/
		static void close()
		{
			lua_close(l.get());
		}

		/*
		* Compares two Lua values.
		* Returns 1 if the value at index index1 satisfies op when compared with the value at index index2,
		* following the semantics of the corresponding Lua operator (that is, it may call metamethods).
		* Otherwise, returns 0. Also returns 0 if any of the indices is not valid.
		*/
		static bool compare(std::int32_t left_index, std::int32_t right_index, lua_compare_op op)
		{
			return lua_compare(l.get(), left_index, right_index, static_cast<int>(op)) == 1;
		}

		/*
		* Concatenates the n values at the top of the stack, pops them, and leaves the result on the top.
		* If n is 1, the result is the single value on the stack (that is, the function does nothing);
		* if n is 0, the result is the empty string.
		* Concatenation is performed following the usual semantics of Lua.
		*/
		static void concat(std::int32_t n)
		{
			lua_concat(l.get(), n);
		}

		/*
		* Copies the element at index src_index into the valid index dst_index, replacing the value at that position.
		* Values at other positions are not affected.
		*/
		static void copy(std::int32_t src_index, std::int32_t  dst_index)
		{
			lua_copy(l.get(), src_index, dst_index);
		}

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
		static lua_status dump(lua_Writer writer, void* data, int strip)
		{
			return static_cast<lua_status>(lua_dump(l.get(), writer, data, strip));
		}

		/*
		* Raises a Lua error, using the value on the top of the stack as the error object.
		* This function does a long jump, and therefore never returns (see luaL_error).
		*/
		static std::int32_t error()
		{
			return lua_error(l.get());
		}

		/*
		*
		*/
		static std::int32_t gc(lua_gc_option option)
		{
			//lua_gc(L, static_cast<int>(option), )
			return 0;
		}

		/*
		* Returns the index of the top element in the stack.
		* Because indices start at 1, this result is equal to the number of elements in the stack; in particular, 0 means an empty stack.
		* @return stack top index (1 ~ N)
		*/
		static std::int32_t top_index()
		{
			return lua_gettop(l.get());
		}

		/*
		* Accepts any index, or 0, and sets the stack top to this index.
		* If the new top is greater than the old one, then the new elements are filled with nil.
		* If index is 0, then all stack elements are removed.
		* This function can run arbitrary code when removing an index marked as to-be-closed from the stack.
		*/
		static void set_top(std::int32_t idx)
		{
			lua_settop(l.get(), idx);
		}

		/*
		* Pops n elements from the stack. It is implemented as a macro over lua_settop.
		*/
		static void pop(std::int32_t n)
		{
			lua_pop(l.get(), n);
		}

		/*
		* Removes the element at the given valid index, 
		* shifting down the elements above this index to fill the gap. 
		* This function cannot be called with a pseudo-index, 
		* because a pseudo-index is not an actual stack position.
		*/
		static void remove(std::int32_t idx)
		{
			lua_remove(l.get(), idx);
		}

		/*
		* Moves the top element into the given valid index without shifting any element 
		* (therefore replacing the value at that given index),
		* and then pops the top element.
		*/
		static void replace(std::int32_t idx)
		{
			lua_replace(l.get(), idx);
		}

		/*
		* Rotates the stack elements between the valid index idx and the top of the stack. 
		* The elements are rotated n positions in the direction of the top, for a positive n, or -n positions 
		* in the direction of the bottom, for a negative n. 
		* The absolute value of n must not be greater than the size of the slice being rotated. 
		* This function cannot be called with a pseudo-index, because a pseudo-index is not an actual stack position.
		*/
		static void rotate(std::int32_t idx, std::int32_t n)
		{
			lua_rotate(l.get(), idx, n);
		}

		/*
		* Returns the type of the value in the given valid index, 
		* or LUA_TNONE for a non-valid but acceptable index. 
		* The types returned by lua_type are coded by the following constants defined in lua.h: 
		* NIL, THREAD, 
		* NUMBER, BOOLEAN,  STRING,  TABLE, 
		* FUNCTION,  USERDATA, LIGHTUSERDATA
		*/
		static lua_t type(std::int32_t idx)
		{
			return static_cast<lua_t>(lua_type(l.get(), idx));
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
			is_shared_ptr_v<T> and has_lua_exporter<typename T::element_type>;
		
		// types 
		template<typename T>
		concept lua_t_acceptable =
			lua_boolean_acceptable<T> or lua_number_acceptable<T> or lua_string_acceptable<T> or lua_userdata_acceptable<T>;
		
		template<lua_t_acceptable T>
		void push(T v)
		{
			if constexpr (lua_boolean_acceptable<T>)
			{
				lua_pushboolean(l.get(), v);
			}
			else if constexpr (lua_integer_number_acceptable<T>)
			{
				lua_pushinteger(l.get(), v);
			}
			else if constexpr (lua_real_number_acceptable<T>)
			{
				lua_pushnumber(l.get(), v);
			}
			else if constexpr (lua_string_acceptable_c_style<T>)
			{
				lua_pushstring(l.get(), v);
			}
			else if constexpr(lua_string_acceptable_std_str<T>)
			{
				lua_pushstring(l.get(), v.c_str());
			}
			else if constexpr (lua_string_acceptable_std_str_view<T>)
			{
				lua_pushstring(l.get(), v.data());
			}
			else if constexpr (lua_userdata_acceptable<T>)
			{
				void* userdata = lua_newuserdata(l.get(), sizeof(T));
				auto _object = static_cast<T*>(new(userdata) T);
				*_object = v;
				luaL_setmetatable(l.get(), "shared_ptr_clazz");
			}

			std::cout<<"pushed v"<<std::endl;
			
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

		static void push_nil()
		{
			lua_pushnil(l.get());
		}
		static void push_table()
		{
			lua_pushglobaltable(l.get());
		}
		static void push_thread()
		{
			lua_pushthread(l.get());
		}
		static void push_value(std::int32_t idx)
		{
			lua_pushvalue(l.get(), idx);
		}

		template<typename ...Args>
		static void push_c_closure(lua_CFunction&& f, Args&& ...args)
		{
			(push(args), ...);
			lua_pushcclosure(l.get(), f, sizeof...(args));
		}

		struct lua_nil {};

		struct lua_thread {};
		
		/*
		* 
		*/
		template<lua_t_acceptable T>
		static bool is(std::int32_t idx) noexcept
		{
			if constexpr (lua_boolean_acceptable<T>)
			{
				return lua_isboolean(l.get(), idx);
			}
			else if constexpr (lua_integer_number_acceptable<T>)
			{
				return lua_isinteger(l.get(), idx);
			}
			else if constexpr (lua_real_number_acceptable<T>)
			{
				return lua_isnumber(l.get(), idx);
			}
			else if constexpr (lua_string_acceptable<T>)
			{
				return lua_isstring(l.get(), idx) && !lua_isnumber(l.get(), idx);
			}
			else if constexpr (lua_userdata_acceptable<T>)
			{
				return lua_isuserdata(l.get(), idx);
			}
			else
			{
				return false;
			}
		}
		
		// template<typename  T>
		// static bool is(std::int32_t idx)
		// {
		// 	// lua_iscfunction();
		// 	// lua_isfunction();
		// 	// lua_islightuserdata();
		// 	// lua_istable();
		//
		// 	// lua_isthread();
		// 	// lua_isnil();
		// 	// lua_isnone();
		// 	// lua_isnoneornil();
		// 	
		// 	return false;
		// }

		template<lua_t_acceptable T>
		static std::optional<T> to(std::int32_t idx)
		{
			if(!is<T>(idx)) {
				return std::nullopt;
			}

			if constexpr (lua_boolean_acceptable<T>) {
				return static_cast<T>(lua_toboolean(l.get(), idx));
			}
			else if constexpr (lua_integer_number_acceptable<T>) {
				return static_cast<T>(lua_tointeger(l.get(), idx));
			}
			else if constexpr (lua_real_number_acceptable<T>) {
				return static_cast<T>(lua_tonumber(l.get(), idx));
			}
			else if constexpr (lua_string_acceptable<T>) {
				return lua_tostring(l.get(), idx);
			}
			else if constexpr (lua_userdata_acceptable<T>) {
				T* userdata = static_cast<T*>(lua_touserdata(l.get(), idx)); //luaL_testudata
				return *userdata;
			}
			else {
				return std::nullopt;
			}
		}

		template<lua_t_acceptable T, std::size_t idx>
		static std::optional<T> static_to()
		{
			return to<T>(idx);
		}
		
		// template<>
		// lua_CFunction to<lua_CFunction>(std::int32_t idx)
		// {
		// 	return lua_tocfunction(l.get(), idx);
		// }

		static lua_State* to_thread(std::int32_t idx)
		{ 
			return lua_tothread(l.get(), idx); 
		}
		
		/*
		* Creates a new empty table and pushes it onto the stack.
		* It is equivalent to createtable(L, 0, 0).
		*/
		static void create_table()
		{
			lua_newtable(l.get());
		}

		/*
		* Creates a new empty table and pushes it onto the stack. (-1)
		* Parameter narr is a hint for how many elements the table will have as a sequence; 
		* parameter nrec is a hint for how many other elements the table will have. 
		* Lua may use these hints to preallocate memory for the new table. 
		* This preallocation may help performance when you know in advance how many elements the table will have. 
		* Otherwise you can use the function lua_newtable.
		*/
		static void create_table(std::int32_t narr, std::int32_t nrec)
		{
			lua_createtable(l.get(), narr, nrec);
		}

		/*
		* This function creates and pushes on the stack a new full userdata,
		* with nuvalue associated Lua values, called user values, plus an associated block of raw memory with size bytes.
		* (The user values can be set and read with the functions lua_setiuservalue and lua_getiuservalue.)
		* The function returns the address of the block of memory.
		* Lua ensures that this address is valid as long as the corresponding userdata is alive (see ��2.5).
		* Moreover, if the userdata is marked for finalization (see ��2.5.3), its address is valid at least until the call to its finalizer.
		*/
		static void new_userdata(size_t size, std::int32_t nuvalue)
		{
			void* _nuserdata = lua_newuserdatauv(l.get(), size, nuvalue);
		}

		/*
		*
		*/
		static void new_userdata(void* userdata)
		{
			void** p_userdata = (void**)lua_newuserdata(l.get(), sizeof(void*));
			*p_userdata = userdata;
		}
		
		/*
		* Pops a value from the stack 
		* and sets it as the new n-th user value associated to the full userdata at the given index. 
		* Returns 0 if the userdata does not have that value.
		*/
		static std::int32_t set_uservalue(std::int32_t index, std::int32_t n)
		{
			return lua_setiuservalue(l.get(), index, n);
		}

		/*
		* Pushes onto the stack the n-th user value associated with the full userdata at the given index
		* and returns the type of the pushed value.
		* If the userdata does not have that value, pushes nil and returns LUA_TNONE.
		*/
		static std::int32_t get_uservalue(std::int32_t index, std::int32_t n)
		{
			return lua_getiuservalue(l.get(), index, n);
		}

#ifdef _DEBUG
		static const void* to_pointer(std::int32_t idx)
		{
			return lua_topointer(l.get(), idx);
		}
#endif

		/*
		* Pushes onto the stack the value of the global name. 
		* Returns the type of that value.
		* @return the type of value
		*/
		static std::int32_t get_global(const char* name)
		{
			return lua_getglobal(l.get(), name);
		}

		/*
		* _G : global table
		* Pops a value from the stack and sets it as the new value of global name.
		*/
		static void set_global(const char* name)
		{
			lua_setglobal(l.get(), name);
		}

		/*
		* Pushes onto the stack the value t[i], where t is the value at the given index. 
		* As in Lua, this function may trigger a metamethod for the "index" event (see ��2.4).
		* Returns the type of the pushed value.
		* @return the type of value
		*/
		static std::int32_t geti(std::int32_t stack_index, std::int32_t index)
		{
			return lua_geti(l.get(), stack_index, index);
		}

		/*
		* Does the equivalent to t[n] = v,
		* where t is the value at the given index and
		* v is the value on the top of the stack.
		* This function pops the value from the stack.
		* As in Lua, this function may trigger a metamethod for the "newindex" event.
		*/
		static void seti(std::int32_t stack_index, std::int32_t n)
		{
			lua_seti(l.get(), stack_index, n);
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index and k is the value on the top of the stack.
		* This function pops the key from the stack, pushing the resulting value in its place. 
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		static lua_t get_table(std::int32_t index)
		{
			return static_cast<lua_t>(lua_gettable(l.get() , index));
		}

		/*
		* Does the equivalent to t[k] = v, 
		* where t is the value at the given index, 
		* v is the value on the top of the stack, 
		* and k is the value just below the top.
		* This function pops both the key and the value from the stack. 
		* As in Lua, this function may trigger a metamethod for the "__newindex" event
		*/
		static void set_table(std::int32_t index)
		{
			lua_settable(l.get(), index);
		}

		/*
		* Similar to lua_gettable, but does a raw access (i.e., without metamethods).
		*/
		static lua_t raw_get(std::int32_t index)
		{
			return static_cast<lua_t>(lua_rawget(l.get(), index));
		}
		
		/*
		* Similar to lua_settable, but does a raw assignment (i.e., without metamethods).
		*/
		static void raw_set(std::int32_t index)
		{
			lua_rawset(l.get(), index);
		}

		/*
		* Pushes onto the stack the value t[n], where t is the table at the given index.
		* The access is raw, that is, it does not use the __index metavalue.
		* Returns the type of the pushed value.
		*/
		static lua_t raw_get(std::int32_t index, std::int32_t key)
		{
			return static_cast<lua_t>(lua_rawgeti(l.get(), index, key));
		}

		/*
		* Does the equivalent of t[i] = v, where t is the table at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack. 
		* The assignment is raw, that is, it does not use the __newindex metavalue.
		*/
		static void raw_set(std::int32_t index, std::int64_t key)
		{
			lua_rawseti(l.get(), index, key);
		}

		/*
		* Returns the raw "length" of the value at the given index: 
		* for strings, this is the string length; for tables, 
		* this is the result of the length operator ('#') with no metamethods; for userdata, 
		* this is the size of the block of memory allocated for the userdata. 
		* For other values, this call returns 0.
		*/
		static std::uint64_t raw_len(std::int32_t index)
		{
			return lua_rawlen(l.get(), index);
		}

		/*
		* Pops a key from the stack, and pushes a key�Cvalue pair from the table at the given index, 
		* the "next" pair after the given key. 
		* If there are no more elements in the table, 
		* then lua_next returns 0 and pushes nothing.
		*/
		static bool table_next(std::int32_t index)
		{
			return lua_next(l.get(), index) == 1;
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index.
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		static lua_t get_field(std::int32_t index, const char* key)
		{
			return static_cast<lua_t>(lua_getfield(l.get(), index, key));
		}

		/*
		* Does the equivalent to t[k] = v, where t is the value at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack.
		* As in Lua, this function may trigger a metamethod for the "newindex" event
		*/
		static void set_field(std::int32_t index, const char* key)
		{
			// v, ..., t 
			lua_setfield(l.get(), index, key);
		}

		/*
		* If the value at the given index has a metatable, the function pushes that metatable onto the stack and returns 1.
		* Otherwise, the function returns 0 and pushes nothing on the stack.
		* @return 1 has metatable and push the metatable onto stack, 0 has no metatable and push nothing
		*/
		static bool get_metatable(std::int32_t index)
		{
			return lua_getmetatable(l.get(), index) == 1;
		}

		/*
		* sets top value as the new metatable for the value at the given index
		* and Pops it( table or nil) from the stack and
		* @return type of value
		*/
		static void set_metatable(std::int32_t index)
		{
			lua_setmetatable(l.get(), index);
		}

		static void set_warnf(lua_WarnFunction f, void* ud)
		{

		}

		static void set_allocf(lua_Alloc f, void* ud)
		{
			lua_setallocf(l.get(), f, ud);
		}

	
		/*
		* Loads a Lua chunk without running it.
		* If there are no errors, lua_load pushes the compiled chunk as a Lua function on top of the stack.
		* Otherwise, it pushes an error message.
		*
		* The lua_load function uses a user-supplied reader function to read the chunk (see lua_Reader).
		* The data argument is an opaque value passed to the reader function.
		* The chunkname argument gives a name to the chunk, which is used for error messages and in debug information (see ��4.7).
		* lua_load automatically detects whether the chunk is text or binary and loads it accordingly (see program luac).
		* The string mode works as in function load, with the addition that a NULL value is equivalent to the string "bt".
		*
		* lua_load uses the stack internally, so the reader function must always leave the stack unmodified when returning.
		* lua_load can return LUA_OK, LUA_ERRSYNTAX, or LUA_ERRMEM. The function may also return other values corresponding to errors raised by the read function (see ��4.4.1).
		* If the resulting function has upvalues, its first upvalue is set to the value of the global environment stored at index LUA_RIDX_GLOBALS in the registry (see ��4.3).
		* When loading main chunks, this upvalue will be the _ENV variable (see ��2.2). Other upvalues are initialized with nil.
		*/
		static lua_status load(lua_Reader reader, void* data, const char* chunk_name, const char* mode)
		{
			return static_cast<lua_status>(lua_load(l.get(), reader, data, chunk_name, mode));
		}

	}

	namespace auxiliary
	{
		/*
		* If the registry already has the key name, returns 0.
		*
		* Otherwise, creates a new table to be used as a metatable for userdata, 
		* adds to this new table the pair __name = name,
		* adds to the registry the pair [name] = new table, 
		* and returns 1.
		*
		* In both cases, 
		* the function pushes onto the stack the final value associated with tname in the registry.
		*/
		static std::int32_t new_metatable(const char* name)
		{
			return luaL_newmetatable(l.get(), name);
		}

		/*
		* Pushes onto the stack the metatable associated with the name tname in the registry,
		* or nil if there is no metatable associated with that name. 
		* 
		* Returns the type of the pushed value.
		*/
		static std::int32_t get_metatable(const char* name)
		{
			return luaL_getmetatable(l.get(), name);
		}

		/*
		* Sets the metatable of the object on the top of the stack 
		* as the metatable associated with name tname in the registry (see luaL_newmetatable).
		*/
		static void set_metatable(const char* name)
		{
			luaL_setmetatable(l.get(), name);
		}

		/*
		* Registers all functions in the array l  
		* into the table on the top of the stack (below optional upvalues, see next).
		* When nup is not zero, all functions are created with nup upvalues, 
		* initialized with copies of the nup values previously pushed on the stack on top of the library table. 
		* These values are popped from the stack after the registration.
		*/
		static void set_funcs(const luaL_Reg* funcs, std::int32_t nup)
		{
			luaL_setfuncs(l.get(), funcs, nup);
		}

		static const char* check_string()
		{
			//luaL_checkstring()
			return "";
		}

		static void* check_userdata(std::int32_t n, const char* metatable)
		{
			return luaL_checkudata(l.get(), n, metatable);
		}

		/*
		* Adds the byte c to the buffer B
		*/
		static void add_char(luaL_Buffer* B, char c)
		{
			luaL_addchar(B, c);
		}

		static void add_gsub() {}

		static void add_lstring() {}

		static void add_size() {}

		static void add_string() {}

		static void add_value() {}

		static void arg_check() {}

		static void arg_error() {}

		static void arg_expected() {}

		static char* buff_addr(luaL_Buffer* B) { return nullptr;}

		static void buf_init_size(luaL_Buffer* B, size_t sz) {}

		static void buff_sub() {}

		static void open_libs()
		{
			luaL_openlibs(l.get());
		}

		/*
		* If package.loaded[modname] is not true, calls the function openf with the string modname as an argument and sets the call result to package.loaded[modname], 
		* as if that function has been called through require.
		* If glb is true, also stores the module into the global modname.
		* Leaves a copy of the module on the stack.
		*/
		static void requiref(const char* modname, lua_CFunction openf, int glb)
		{
			luaL_requiref(l.get(), modname, openf, glb);
		}

		/*
		* Loads a string as a Lua chunk. This function uses lua_load to load the chunk in the zero-terminated string s.
		* This function returns the same results as lua_load.
		* Also, as lua_load, this function only loads the chunk; it does not run it.
		*/
		static lua_status load_string(const char* str)
		{
			return static_cast<lua_status>(luaL_loadstring(l.get(), str));
		}

		static lua_status do_string(const char* str)
		{
			return static_cast<lua_status>(luaL_dostring(l.get(), str));
		}

		static lua_status load_file(const char* file_name)
		{
			return static_cast<lua_status>(luaL_loadfile(l.get(), file_name));
		}

		static lua_status load_file(const char* file_name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadfilex(l.get(), file_name, mode));
		}

		static lua_status do_file(const char* file_name)
		{
			return static_cast<lua_status>(luaL_dofile(l.get(), file_name));
		}

		static lua_status load_buffer(const char* buff, size_t sz, const char* name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadbufferx(l.get(), buff, sz, name, mode));
		}

		static lua_status load_buffer(const char* buff, size_t sz, const char* name)
		{
			return static_cast<lua_status>(luaL_loadbuffer(l.get(), buff, sz, name));
		}

	}

	static void* to_cpp_instance(std::int32_t idx, const char* metatable_name)
	{
		void* pp_userdata = luaL_testudata(l.get(), idx, metatable_name);
		return pp_userdata;
	}

	template<typename T>
	static T* to_instance(std::int32_t idx)
	{
		std::string s = typeid(T).name();
		T* pp_userdata = (T*)luaL_checkudata(l.get(), idx, s.c_str());
		return pp_userdata;
	}

	/*
	* std common t => lua t
	* 
	*/
	template<typename t> 
	static void push(t value) noexcept
	{
		basic::push(value);
	}

	/*
	* std container => lua table
	* 
	*/
	template<typename t, size_t size> 
	static void push(const std::array<t, size>& c) noexcept
	{
		// ...
		basic::create_table(size, 0);
		// table, ...
		for (size_t idx = 0; idx < size; ++idx)
		{
			push(idx + 1);
			// key, table, ...
			push(c[idx]);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template <typename t, typename allocator = std::allocator<t>> 
	static void push(const std::vector<t, allocator>& c) noexcept
	{
		// ...
		basic::create_table(c.size(), 0);
		// table, ...
		for (std::size_t idx = 0; idx < c.size(); ++idx)
		{
			push(idx + 1);
			// key, table, ...
			push(c[idx]);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<typename t, typename allocator = std::allocator<t>> 
	static void push(const std::deque<t, allocator>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		for (std::size_t _index = 0; _index < c.size(); ++_index)
		{
			push(_index + 1);
			// key, table, ...
			push(c[_index]);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<typename t, typename allocator = std::allocator<t>>
	static void push(const std::list<t, allocator>& c) noexcept
	{
		// ...
		basic::create_table(c.size(), 0);
		// table, ...
		size_t _idx = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_idx)
		{
			push(_idx);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}
	
	template<typename t, typename allocator = std::allocator<t>>
	static void push(const std::forward_list<t, allocator>& c) noexcept
	{
		// ...
		basic::create_table();
		// table, ...
		size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(_index);
			// key, table, ...
			push(*it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<typename t, typename predicate = std::less<t>, typename allocator = std::allocator<t>>
	static void push(const std::set<t, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(_index);
			// key, table, ...
			push(*it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<typename t, typename predicate = std::less<t>, typename allocator = std::allocator<t>> 
	static void push(const std::multiset<t, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
		{
			push(_index);
			// key, table, ...
			push(*_it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<
		typename t,
		typename hasher = std::hash<t>,
		typename predicate = std::equal_to<t>,
		typename allocator = std::allocator<t>
	>
	static void push(const std::unordered_set<t, hasher, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(_index);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<
		typename t,
		typename hasher = std::hash<t>,
		typename predicate = std::equal_to<t>,
		typename allocator = std::allocator<t>
	>
	static void push(const std::unordered_multiset<t, hasher, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
		{
			push(_index);
			// key, table, ...
			push(l, *_it);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<
		typename key_t, typename value_t,
		typename predicate = std::less<key_t>, 
		typename allocator = std::allocator<std::pair<const key_t, value_t>>
	> 
	static void push(const std::map<key_t, value_t, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(pair.first);
			// key, table, ...
			push(pair.second);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}

	template<
		typename key_t, typename value_t, 
		typename hasher = std::hash<key_t>,
		typename predicate = std::equal_to<key_t>,
		typename allocator = std::allocator<std::pair<const key_t, value_t>>
	> 
	static void push(const std::unordered_map<key_t, value_t, hasher, predicate, allocator>& c) noexcept
	{
		// ...
		basic::create_table(0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(pair.first);
			// key, table, ...
			push(pair.second);
			// value, key, table, ...
			basic::set_table(-3);
			// table, ...
		}
	}
	
	template<typename t, size_t size> 
	static bool to(std::int32_t index, std::array<t, size>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		const auto _table_len = basic::raw_len(index);
		if (_table_len != size)
		{
			return false;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		size_t _array_index = 0;
		while (basic::table_next(index))
		{
			// value, key, table, ....
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ....
				return false;
			}
			c[_array_index++] = _optional_v.value();
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template <typename t> 
	static bool to(std::int32_t index, std::vector<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		if (!helper::is_table_vectorizable(index))
		{
			return false;
		}
		
		auto len = basic::raw_len(index);
		if (len < 1)
		{
			return true;
		}

		c.reserve(len);
		// table, ...
		basic::push_nil();
		// key, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.push_back(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template <typename t> 
	static bool to(std::int32_t index, std::deque<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		const auto table_len = basic::raw_len(index);
		if (table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// key, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.push_back(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template<typename t> 
	static bool to(std::int32_t index, std::list<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				return false;
			}
			c.push_back(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template<typename t> 
	static bool to(std::int32_t index, std::forward_list<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.push_front(_optional_v.value());
			basic::pop(1);
			// key, value, ...
		}
		// table, ...
		return true;
	}

	template<typename t> 
	static bool to(std::int32_t index, std::set<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		size_t _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ....
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template<typename t> 
	static bool to(std::int32_t index, std::multiset<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true; 
	}

	template<typename t> 
	static bool to(lua_State* l, std::int32_t index, std::unordered_set<t>& c)  noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}
		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(1);
			// key, value, ...
		}
		// table, ...
		return true;
	}

	template<typename t> 
	static bool to(std::int32_t index, std::unordered_multiset<t>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_v = to<t>(-1);
			if (!_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template<
		typename key_t, typename value_t,
		typename predicate = std::less<key_t>,
		typename allocator = std::allocator<std::pair<const key_t, value_t>>
	> 
	static bool to(std::int32_t index, std::map<key_t, value_t, predicate, allocator>& c) noexcept
	{
		// if (!basic::is_type(index, lua_t::table))
		// {
		// 	return false;
		// }

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_k = to<key_t>(l, -1);
			auto _optional_v = to<value_t>(l, -1);
			if (!_optional_k.has_value() || !_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.emplace(_optional_k.value(), _optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

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

		auto _table_len = basic::raw_len(index);
		if (_table_len < 1)
		{
			return true;
		}

		// table, ...
		basic::push_nil();
		// nil, table, ...
		while (basic::table_next(index))
		{
			// value, key, table, ...
			auto _optional_k = to<key_t>(l, -2);
			auto _optional_v = to<value_t>(l, -1);
			if (!_optional_k.has_value() || !_optional_v.has_value())
			{
				basic::pop(2);
				// table, ...
				return false;
			}
			c.emplace(_optional_k.value(), _optional_v.value());
			basic::pop(1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	struct lua_class
	{
		std::string name;
		const luaL_Reg* funcs;
	};


	struct function_registry
	{
		function_registry()
		{
			functions.push_back({nullptr, nullptr});
		}

		void set(const char* name, lua_CFunction f)
		{
			const auto it = std::ranges::find_if(functions,
				[name](const luaL_Reg& v)
			{
				return v.name == name;
			});

			if(it == functions.end())
			{
				functions.push_back({name, f});
			}else
			{
				it->func = f;
			}
		}

		[[nodiscard]] const std::vector<luaL_Reg>& list() const
		{
			return functions;
		}

	private:
		std::vector<luaL_Reg> functions;
	};
		
	template<typename T>
	struct lua_exporter
	{
		using meta_t = T;

		static function_registry registry;

		static std::function<void(function_registry&)> registry_delegate;

		static lua_exporter exporter;
			
		lua_exporter()
		{
			registry_delegate(registry);
			// register
			//lua_api::lua_vm::register_functions(functions.data());
		}
	};
	
	class lua_vm final
	{

		lua_State* state_ = nullptr;
		
	public:

		static function_registry registry;
	
		lua_vm() = default;
		
		lua_vm(const lua_vm&) = delete;
		lua_vm& operator=(const lua_vm&) = delete;
	
		~lua_vm()
		{
			if(!state_)
			{
				lua_close(state_);
			}
		}
	
		bool initialize() noexcept;
	
		void run() noexcept;
	
		bool do_file(const std::string& path);
	
	private:
	
		void _load_class(const std::string& class_name, const luaL_Reg* funcs);
	
		void _load_libs();
	
	public:
	
		static void register_class(const char* name, const luaL_Reg* funcs);
	
	private:
	
		static std::vector<lua_class*> _classes;
	
	};

}


#define LUA_LIBS_B()\
static const luaL_Reg libs[] =\
{\

#define LUA_LIBS_E()\
{nullptr}, {nullptr}\
};\


#define LUA_FUNCS_B() \
static const luaL_Reg functions[] =\
{\

#define LUA_FUNCS_E()\
{nullptr}, {nullptr}\
};\

/////////// metatable functions helper

// +
#define __ADD()\
{"__add", __add},\

// -
#define __SUB()\
{"__sub", __sub},\

// *
#define __MUL()\
{"__mul", __mul},\

// /
#define __DIV()\
{"__div", __div},\

// %
#define __MOD()\
{"__mod", __mod},\

// ^
#define __POW()\
{"__pow", __pow},\

// 
#define __UNM()\
{"__unm", __unm},\

// //
#define __IDIV()\
{"__idiv", __idiv},\

// &
#define __BAND()\
{"__band", __band},\

// |
#define __BOR()\
{"__bor", __bor},\

#define __BXOR()\
{"__bxor", __bxor},\

#define __BNOT()\
{"__bnot", __bnot},\

// <<
#define __SHL()\
{"__shl", __shl},\

// >>
#define __SHR()\
{"__shr", __shr},\

// ..
#define __CONCAT()\
{"__concat", __concat},\

// #
#define __LEN()\
{"__len", __len},\

// ==
#define __EQ()\
{"__eq", __eq},\

// <
#define __LT()\
{"__lt", __lt},\

// <=
#define __LE()\
{"__le", __le},\


#define __INDEX()\
{"__index", __index},\

#define __NEWINDEX()\
{"__newindex", __newindex},\

#define __CALL()\
{"__call", __call},\


#define __GC()\
{"__gc", __gc},\

#define __CLOSE()\
{"__close", __close},\

#define __NAME()\
{"__name", __name},\

#define __MODE()\
{"__mode", __mode},\

#define __PAIRS()\
{"__pairs", __pairs}\

#define FUNC(FUNC_PTR)\
{#FUNC_PTR, FUNC_PTR},\

#define IMPLEMENT_EXPORTER(NAME)\
struct NAME##_exporter\
{\
	static NAME##_exporter instance;\
	NAME##_exporter()\
	{\
		lua_api::lua_vm::register_class(#NAME, functions);\
	}\
	~NAME##_exporter() = default;\
};\
NAME##_exporter NAME##_exporter::instance;\


#endif