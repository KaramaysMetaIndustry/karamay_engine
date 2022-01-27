#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/_lua.h"

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
	// nil, thread
	// boolean, number, string, userdata, table, function
	enum class lua_t : int
	{
		NONE = LUA_TNONE,
		NIL = LUA_TNIL,

		BOOLEAN = LUA_TBOOLEAN,
		NUMBER = LUA_TNUMBER,
		STRING = LUA_TSTRING,
		
		FUNCTION = LUA_TFUNCTION,
		
		TABLE = LUA_TTABLE,
		USERDATA = LUA_TUSERDATA,
		LIGHTUSERDATA = LUA_TLIGHTUSERDATA,
		
		THREAD = LUA_TTHREAD,

		NUMTYPES = LUA_NUMTYPES
	};

	enum class lua_status : int
	{
		OK = LUA_OK, // : no errors.
		ERR_RUN = LUA_ERRRUN, // : a runtime error.
		ERR_MEM = LUA_ERRMEM, // : memory allocation error.For such errors, Lua does not call the message handler.
		ERR_ERR = LUA_ERRERR, //: error while running the message handler.
		ERR_SYNTAX = LUA_ERRSYNTAX, // : syntax error during precompilation.
		YIELD = LUA_YIELD, //: the thread(coroutine) yields.
		ERR_FILE = LUA_ERRFILE // : a file - related error; e.g., it cannot open or read the file.
	};

	enum class lua_compare_op : int
	{
		EQ = LUA_OPEQ, // ==
		LT = LUA_OPLT, // <
		LE = LUA_OPLE // <=
	};

	enum class lua_gc_option : int
	{
		GCCOLLECT = LUA_GCCOLLECT, //Performs a full garbage - collection cycle.
		GCSTOP = LUA_GCSTOP, //Stops the garbage collector.
		GCRESTART = LUA_GCRESTART, //Restarts the garbage collector.
		GCCOUNT = LUA_GCCOUNT, //Returns the current amount of memory(in Kbytes) in use by Lua.
		GCCOUNTB = LUA_GCCOUNTB, //Returns the remainder of dividing the current amount of bytes of memory in use by Lua by 1024.
		GCSTEP = LUA_GCSTEP, //Performs an incremental step of garbage collection, corresponding to the allocation of stepsize Kbytes.
		GCISRUNNING = LUA_GCISRUNNING, //Returns a boolean that tells whether the collector is running(i.e., not stopped).
		GCINC = LUA_GCINC, //Changes the collector to incremental mode with the given parameters(see ¡ì2.5.1).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
		GCGEN = LUA_GCGEN //Changes the collector to generational mode with the given parameters(see ¡ì2.5.2).Returns the previous mode(LUA_GCGEN or LUA_GCINC).
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
		static bool check_stack(lua_State* l, int32 n)
		{
			return lua_checkstack(l, n) == 1;
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
		static void close(lua_State* l)
		{
			lua_close(l);
		}

		/*
		* Compares two Lua values.
		* Returns 1 if the value at index index1 satisfies op when compared with the value at index index2,
		* following the semantics of the corresponding Lua operator (that is, it may call metamethods).
		* Otherwise returns 0. Also returns 0 if any of the indices is not valid.
		*/
		static bool compare(lua_State* l, int32 left_index, int32 right_index, lua_compare_op op)
		{
			return lua_compare(l, left_index, right_index, static_cast<int>(op)) == 1;
		}

		/*
		* Concatenates the n values at the top of the stack, pops them, and leaves the result on the top.
		* If n is 1, the result is the single value on the stack (that is, the function does nothing);
		* if n is 0, the result is the empty string.
		* Concatenation is performed following the usual semantics of Lua.
		*/
		static void concat(lua_State* l, int32 n)
		{
			lua_concat(l, n);
		}

		/*
		* Copies the element at index src_index into the valid index dst_index, replacing the value at that position.
		* Values at other positions are not affected.
		*/
		static void copy(lua_State* l, int32 src_index, int32  dst_index)
		{
			lua_copy(l, src_index, dst_index);
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
		static lua_status dump(lua_State* l, lua_Writer writer, void* data, int strip)
		{
			return static_cast<lua_status>(lua_dump(l, writer, data, strip));
		}

		/*
		* Raises a Lua error, using the value on the top of the stack as the error object.
		* This function does a long jump, and therefore never returns (see luaL_error).
		*/
		static int32 error(lua_State* l)
		{
			return lua_error(l);
		}

		/*
		*
		*/
		static int32 gc(lua_State* l, lua_gc_option option)
		{
			//lua_gc(L, static_cast<int>(option), )
			return 0;
		}

		/*
		* Returns the index of the top element in the stack.
		* Because indices start at 1, this result is equal to the number of elements in the stack; in particular, 0 means an empty stack.
		* @return stack top index (1 ~ N)
		*/
		static int32 top_index(lua_State* l)
		{
			return lua_gettop(l);
		}

		/*
		* Accepts any index, or 0, and sets the stack top to this index.
		* If the new top is greater than the old one, then the new elements are filled with nil.
		* If index is 0, then all stack elements are removed.
		* This function can run arbitrary code when removing an index marked as to-be-closed from the stack.
		*/
		static void set_top(lua_State* l, int32 index)
		{
			lua_settop(l, index);
		}

		/*
		* Pops n elements from the stack. It is implemented as a macro over lua_settop.
		*/
		static void pop(lua_State* l, int32 n)
		{
			lua_pop(l, n);
		}

		/*
		* Removes the element at the given valid index, 
		* shifting down the elements above this index to fill the gap. 
		* This function cannot be called with a pseudo-index, 
		* because a pseudo-index is not an actual stack position.
		*/
		static void remove(lua_State* l, int32 index)
		{
			lua_remove(l, index);
		}

		/*
		* Moves the top element into the given valid index without shifting any element 
		* (therefore replacing the value at that given index),
		* and then pops the top element.
		*/
		static void replace(lua_State* l, int32 index)
		{
			lua_replace(l, index);
		}

		/*
		* Rotates the stack elements between the valid index idx and the top of the stack. 
		* The elements are rotated n positions in the direction of the top, for a positive n, or -n positions 
		* in the direction of the bottom, for a negative n. 
		* The absolute value of n must not be greater than the size of the slice being rotated. 
		* This function cannot be called with a pseudo-index, because a pseudo-index is not an actual stack position.
		*/
		static void rotate(lua_State* l, int32 index, int32 num)
		{
			lua_rotate(l, index, num);
		}

		/*
		* Returns the type of the value in the given valid index, 
		* or LUA_TNONE for a non-valid but acceptable index. 
		* The types returned by lua_type are coded by the following constants defined in lua.h: 
		* NIL, THREAD, 
		* NUMBER, BOOLEAN,  STRING,  TABLE, 
		* FUNCTION,  USERDATA, LIGHTUSERDATA
		*/
		static lua_t type(lua_State* l, int32 index)
		{
			return static_cast<lua_t>(lua_type(l, index));
		}

		/*
		* 
		*/
		static bool is_type(lua_State* l, int32 index, lua_t t)
		{
			return t == type(l, index);
		}

		template<typename T>
		static bool is(lua_State* l, int32 index)
		{
			return false;
		}

		template<>
		static bool is<bool>(lua_State* l, int32 index) { return is_type(l, index, lua_t::BOOLEAN); }
		template<>
		static bool is<uint8>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<uint16>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<uint32>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<uint64>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<int8>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<int16>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<int32>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<int64>(lua_State* l, int32 index) { return is_type(l, index, lua_t::NUMBER); }
		template<>
		static bool is<std::string>(lua_State* l, int32 index) { return is_type(l, index, lua_t::STRING); }

		// lua boolean
		static void push(lua_State* l, bool value) { lua_pushboolean(l, static_cast<int>(value)); }
		// lua number
		static void push(lua_State* l, uint8 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, uint16 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, uint32 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, uint64 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, int8 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, int16 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, int32 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, int64 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		static void push(lua_State* l, float value) { lua_pushnumber(l, static_cast<lua_Number>(value)); }
		static void push(lua_State* l, double value) { lua_pushnumber(l, static_cast<lua_Number>(value)); }
		// lua userdata
		template<typename T>
		static void push(lua_State* l, T* value)
		{
			static_assert(std::is_class_v<T>, "must be class or struct pointer");
			lua_pushlightuserdata(l, (void*)value);
			/*if (!luaL_testudata(l, -1, ""))
			{
				luaL_setmetatable(l, "");
			}*/
		}
		template<typename T>
		static void push(lua_State* l, const T* value)
		{
			static_assert(std::is_class_v<T>, "must be class or struct pointer");
			lua_pushlightuserdata(l, (void*)value);
			/*if (!luaL_testudata(l, -1, ""))
			{
				luaL_setmetatable(l, "");
			}*/
		}
		// lua string
		static void push(lua_State* l, char* value)
		{
			lua_pushstring(l, value);
		}
		static void push(lua_State* l, const char* value)
		{
			lua_pushstring(l, value);
		}
		static void push(lua_State* l, std::string&& value)
		{
			lua_pushstring(l, value.c_str());
		}
		static void push(lua_State* l, std::string& value)
		{
			lua_pushstring(l, value.c_str());
		}
		static void push(lua_State* l, const std::string& value)
		{
			lua_pushstring(l, value.c_str());
		}
		static void push(lua_State* l, const std::string_view& value)
		{
			value.data();
		}
		// nil, thread
		static void push_nil(lua_State* l) { lua_pushnil(l); }
		static void push_table(lua_State* l)
		{
			lua_pushglobaltable(l);
		}
		static void push_thread(lua_State* l) { lua_pushthread(l); }
		static void push_value(lua_State* l, int32 index)
		{
			lua_pushvalue(l, index);
		}
		
		template<typename T>
		static T to(lua_State* l, int32 index) { static_assert(false, "to<T> , T is not supported"); return T(); }
		// bool 
		template<> // 1-byte
		static bool to<bool>(lua_State* l, int32 index) { return static_cast<bool>(lua_toboolean(l, index)); }
		// number
		template<> // 1-byte
		static int8 to<int8>(lua_State* l, int32 index) { return static_cast<int8>(lua_tointeger(l, index)); }
		template<> // 2-byte
		static int16 to<int16>(lua_State* l, int32 index) { return static_cast<int16>(lua_tointeger(l, index)); }
		template<> // 4-byte
		static int32 to<int32>(lua_State* l, int32 index) { return static_cast<int32>(lua_tointeger(l, index)); }
		template<> // 8-byte
		static int64 to<int64>(lua_State* l, int32 index) { return static_cast<int64>(lua_tointeger(l, index)); }
		template<>
		static uint8 to<uint8>(lua_State* l, int32 index) { return static_cast<uint8>(lua_tointeger(l, index)); }
		template<>
		static uint16 to<uint16>(lua_State* l, int32 index) { return static_cast<uint16>(lua_tointeger(l, index)); }
		template<>
		static uint32 to<uint32>(lua_State* l, int32 index) { return static_cast<uint32>(lua_tointeger(l, index)); }
		template<>
		static uint64 to<uint64>(lua_State* l, int32 index) { return static_cast<uint64>(lua_tointeger(l, index)); }
		template<> // 4 - byte
		static float to<float>(lua_State* l, int32 index) { return static_cast<float>(lua_tonumber(l, index)); }
		template<> // 8 - byte
		static double to<double>(lua_State* l, int32 index) { return static_cast<double>(lua_tonumber(l, index)); }
		// string
		template<> // 8 - byte
		static const char* to<const char*>(lua_State* l, int32 index) { return lua_tostring(l, index); }
		template<> // 40 - byte
		static std::string to<std::string>(lua_State* l, int32 index) { return std::string(lua_tostring(l, index)); }
		template<> // 16 - byte
		static std::string_view to<std::string_view>(lua_State* l, int32 index) { return std::string_view(lua_tostring(l, index)); }
		// userdata
		template<>
		static void* to<void*>(lua_State* l, int32 index) { return lua_touserdata(l, index); }
		template<>
		static const void* to<const void*>(lua_State* l, int32 index) { return static_cast<const void*>(lua_touserdata(l, index)); }
		// function
		template<>
		static lua_CFunction to<lua_CFunction>(lua_State* l, int32 index) { return lua_tocfunction(l, index); }
		
		/*
		* Creates a new empty table and pushes it onto the stack.
		* It is equivalent to createtable(L, 0, 0).
		*/
		static void create_table(lua_State* l)
		{
			lua_newtable(l);
		}

		/*
		* Creates a new empty table and pushes it onto the stack. (-1)
		* Parameter narr is a hint for how many elements the table will have as a sequence; 
		* parameter nrec is a hint for how many other elements the table will have. 
		* Lua may use these hints to preallocate memory for the new table. 
		* This preallocation may help performance when you know in advance how many elements the table will have. 
		* Otherwise you can use the function lua_newtable.
		*/
		static void create_table(lua_State* l, int32 narr, int32 nrec)
		{
			lua_createtable(l, narr, nrec);
		}

		/*
		* This function creates and pushes on the stack a new full userdata,
		* with nuvalue associated Lua values, called user values, plus an associated block of raw memory with size bytes.
		* (The user values can be set and read with the functions lua_setiuservalue and lua_getiuservalue.)
		* The function returns the address of the block of memory.
		* Lua ensures that this address is valid as long as the corresponding userdata is alive (see ¡ì2.5).
		* Moreover, if the userdata is marked for finalization (see ¡ì2.5.3), its address is valid at least until the call to its finalizer.
		*/
		static void new_userdata(lua_State* l, size_t size, int32 nuvalue)
		{
			std::vector<int> a;
			void* _nuserdata = lua_newuserdatauv(l, size, nuvalue);
		}

		/*
		*
		*/
		static void new_userdata(lua_State* L, void* userdata)
		{
			void** p_userdata = (void**)lua_newuserdata(L, sizeof(void*));
			*p_userdata = userdata;
		}
		
		/*
		* Pops a value from the stack 
		* and sets it as the new n-th user value associated to the full userdata at the given index. 
		* Returns 0 if the userdata does not have that value.
		*/
		static int32 set_uservalue(lua_State* l, int32 index, int32 n)
		{
			return lua_setiuservalue(l, index, n);
		}

		/*
		* Pushes onto the stack the n-th user value associated with the full userdata at the given index
		* and returns the type of the pushed value.
		* If the userdata does not have that value, pushes nil and returns LUA_TNONE.
		*/
		static int32 get_uservalue(lua_State* l, int32 index, int32 n)
		{
			return lua_getiuservalue(l, index, n);
		}

		
		static lua_State* to_thread(lua_State* L, int32 stack_index) 
		{ 
			return lua_tothread(L, stack_index); 
		}

#ifdef _DEBUG
		static const void* to_pointer(lua_State* L, int32 stack_index)
		{
			return lua_topointer(L, stack_index);
		}
#endif

		/*
		* Pushes onto the stack the value of the global name. 
		* Returns the type of that value.
		* @return the type of value
		*/
		static int32 get_global(lua_State* l, const char* name)
		{
			return lua_getglobal(l, name);
		}

		/*
		* _G : global table
		* Pops a value from the stack and sets it as the new value of global name.
		*/
		static void set_global(lua_State* l, const char* name)
		{
			lua_setglobal(l, name);
		}

		/*
		* Pushes onto the stack the value t[i], where t is the value at the given index. 
		* As in Lua, this function may trigger a metamethod for the "index" event (see ¡ì2.4).
		* Returns the type of the pushed value.
		* @return the type of value
		*/
		static int32 geti(lua_State* l, int32 stack_index, int32 index)
		{
			return lua_geti(l, stack_index, index);
		}

		/*
		* Does the equivalent to t[n] = v,
		* where t is the value at the given index and
		* v is the value on the top of the stack.
		* This function pops the value from the stack.
		* As in Lua, this function may trigger a metamethod for the "newindex" event.
		*/
		static void seti(lua_State* L, int32 stack_index, int64 n)
		{
			lua_seti(L, stack_index, n);
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index and k is the value on the top of the stack.
		* This function pops the key from the stack, pushing the resulting value in its place. 
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		static lua_t get_table(lua_State* l, int32 index)
		{
			return static_cast<lua_t>(lua_gettable(l , index));
		}

		/*
		* Does the equivalent to t[k] = v, 
		* where t is the value at the given index, 
		* v is the value on the top of the stack, 
		* and k is the value just below the top.
		* This function pops both the key and the value from the stack. 
		* As in Lua, this function may trigger a metamethod for the "__newindex" event
		*/
		static void set_table(lua_State* l, int32 index)
		{
			lua_settable(l, index);
		}

		/*
		* Similar to lua_gettable, but does a raw access (i.e., without metamethods).
		*/
		static lua_t raw_get(lua_State* l, int32 index)
		{
			return static_cast<lua_t>(lua_rawget(l, index));
		}
		
		/*
		* Similar to lua_settable, but does a raw assignment (i.e., without metamethods).
		*/
		static void raw_set(lua_State* l, int32 index)
		{
			lua_rawset(l, index);
		}

		/*
		* Pushes onto the stack the value t[n], where t is the table at the given index.
		* The access is raw, that is, it does not use the __index metavalue.
		* Returns the type of the pushed value.
		*/
		static lua_t raw_get(lua_State* l, int32 index, int64 key)
		{
			return static_cast<lua_t>(lua_rawgeti(l, index, key));
		}

		/*
		* Does the equivalent of t[i] = v, where t is the table at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack. 
		* The assignment is raw, that is, it does not use the __newindex metavalue.
		*/
		static void raw_set(lua_State* l, int32 index, int64 key)
		{
			lua_rawseti(l, index, key);
		}

		/*
		* Returns the raw "length" of the value at the given index: 
		* for strings, this is the string length; for tables, 
		* this is the result of the length operator ('#') with no metamethods; for userdata, 
		* this is the size of the block of memory allocated for the userdata. 
		* For other values, this call returns 0.
		*/
		static uint64 raw_len(lua_State* l, int32 index)
		{
			return lua_rawlen(l, index);
		}

		/*
		* Pops a key from the stack, and pushes a key¨Cvalue pair from the table at the given index, 
		* the "next" pair after the given key. 
		* If there are no more elements in the table, 
		* then lua_next returns 0 and pushes nothing.
		*/
		static bool table_next(lua_State* l, int32 index)
		{
			return lua_next(l, index) == 1;
		}

		/*
		* Pushes onto the stack the value t[k], where t is the value at the given index.
		* As in Lua, this function may trigger a metamethod for the "index" event
		*/
		static lua_t get_field(lua_State* l, int32 index, const char* key)
		{
			return static_cast<lua_t>(lua_getfield(l, index, key));
		}

		/*
		* Does the equivalent to t[k] = v, where t is the value at the given index and v is the value on the top of the stack.
		* This function pops the value from the stack. 
		* As in Lua, this function may trigger a metamethod for the "newindex" event
		*/
		static void set_field(lua_State* l, int32 index, const char* key)
		{
			// v, ..., t 
			lua_setfield(l, index, key);
		}

		/*
		* If the value at the given index has a metatable, the function pushes that metatable onto the stack and returns 1.
		* Otherwise, the function returns 0 and pushes nothing on the stack.
		* @return 1 has metatable and push the metatable onto stack, 0 has no metatable and push nothing
		*/
		static bool get_metatable(lua_State* l, int32 index)
		{
			return lua_getmetatable(l, index) == 1;
		}

		/*
		* sets top value as the new metatable for the value at the given index
		* and Pops it( table or nil) from the stack and
		* @return type of value
		*/
		static void set_metatable(lua_State* l, int32 index)
		{
			lua_setmetatable(l, index);
		}

		static void set_warnf(lua_State* L, lua_WarnFunction f, void* ud)
		{

		}

		static void set_allocf(lua_State* L, lua_Alloc f, void* ud)
		{
			lua_setallocf(L, f, ud);
		}

	
		/*
		* Loads a Lua chunk without running it.
		* If there are no errors, lua_load pushes the compiled chunk as a Lua function on top of the stack.
		* Otherwise, it pushes an error message.
		*
		* The lua_load function uses a user-supplied reader function to read the chunk (see lua_Reader).
		* The data argument is an opaque value passed to the reader function.
		* The chunkname argument gives a name to the chunk, which is used for error messages and in debug information (see ¡ì4.7).
		* lua_load automatically detects whether the chunk is text or binary and loads it accordingly (see program luac).
		* The string mode works as in function load, with the addition that a NULL value is equivalent to the string "bt".
		*
		* lua_load uses the stack internally, so the reader function must always leave the stack unmodified when returning.
		* lua_load can return LUA_OK, LUA_ERRSYNTAX, or LUA_ERRMEM. The function may also return other values corresponding to errors raised by the read function (see ¡ì4.4.1).
		* If the resulting function has upvalues, its first upvalue is set to the value of the global environment stored at index LUA_RIDX_GLOBALS in the registry (see ¡ì4.3).
		* When loading main chunks, this upvalue will be the _ENV variable (see ¡ì2.2). Other upvalues are initialized with nil.
		*/
		static lua_status load(lua_State* L, lua_Reader reader, void* data, const char* chunk_name, const char* mode)
		{
			return static_cast<lua_status>(lua_load(L, reader, data, chunk_name, mode));
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
		static int32 new_metatable(lua_State* l, const char* name)
		{
			return luaL_newmetatable(l, name);
		}

		/*
		* Pushes onto the stack the metatable associated with the name tname in the registry,
		* or nil if there is no metatable associated with that name. 
		* 
		* Returns the type of the pushed value.
		*/
		static int32 get_metatable(lua_State* l, const char* name)
		{
			return luaL_getmetatable(l, name);
		}

		/*
		* Sets the metatable of the object on the top of the stack 
		* as the metatable associated with name tname in the registry (see luaL_newmetatable).
		*/
		static void set_metatable(lua_State* l, const char* name)
		{
			luaL_setmetatable(l, name);
		}

		/*
		* Registers all functions in the array l  
		* into the table on the top of the stack (below optional upvalues, see next).
		* When nup is not zero, all functions are created with nup upvalues, 
		* initialized with copies of the nup values previously pushed on the stack on top of the library table. 
		* These values are popped from the stack after the registration.
		*/
		static void set_funcs(lua_State* l, const luaL_Reg* funcs, int32 nup)
		{
			luaL_setfuncs(l, funcs, nup);
		}

		static const char* check_string()
		{
			//luaL_checkstring()
			return "";
		}

		static void* check_userdata(lua_State* l, int32 n, const char* metatable)
		{
			return luaL_checkudata(l, n, metatable);
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

		static char* buff_addr(luaL_Buffer* B) {}

		static void buf_init_size(lua_State* L, luaL_Buffer* B, size_t sz) {}

		static void buff_sub() {}

		static void open_libs(lua_State* L)
		{
			luaL_openlibs(L);
		}

		/*
		* If package.loaded[modname] is not true, calls the function openf with the string modname as an argument and sets the call result to package.loaded[modname], 
		* as if that function has been called through require.
		* If glb is true, also stores the module into the global modname.
		* Leaves a copy of the module on the stack.
		*/
		static void requiref(lua_State* L, const char* modname, lua_CFunction openf, int glb)
		{
			luaL_requiref(L, modname, openf, glb);
		}

		static lua_State* new_state()
		{
			return luaL_newstate();
		}

		/*
		* Loads a string as a Lua chunk. This function uses lua_load to load the chunk in the zero-terminated string s.
		* This function returns the same results as lua_load.
		* Also as lua_load, this function only loads the chunk; it does not run it.
		*/
		static lua_status load_string(lua_State* L, const char* str)
		{
			return static_cast<lua_status>(luaL_loadstring(L, str));
		}

		static lua_status do_string(lua_State* L, const char* str)
		{
			return static_cast<lua_status>(luaL_dostring(L, str));
		}

		static lua_status load_file(lua_State* L, const char* file_name)
		{
			return static_cast<lua_status>(luaL_loadfile(L, file_name));
		}

		static lua_status load_file(lua_State* L, const char* file_name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadfilex(L, file_name, mode));
		}

		static lua_status do_file(lua_State* L, const char* file_name)
		{
			return static_cast<lua_status>(luaL_dofile(L, file_name));
		}

		static lua_status load_buffer(lua_State* L, const char* buff, size_t sz, const char* name, const char* mode)
		{
			return static_cast<lua_status>(luaL_loadbufferx(L, buff, sz, name, mode));
		}

		static lua_status load_buffer(lua_State* L, const char* buff, size_t sz, const char* name)
		{
			return static_cast<lua_status>(luaL_loadbuffer(L, buff, sz, name));
		}

	}

	namespace debug
	{

	}

	namespace helper
	{
		static bool is_table_vectorizable(lua_State* l, int32 index)
		{
			if (!basic::is_type(l, index, lua_t::TABLE)) return false;

			return  true;
		}
		static bool is_table_sequenceable(lua_State* l, int32 index)
		{

			return true;
		}
	}

	static void* to_cpp_instance(lua_State* l, int32 index, const char* metatable_name)
	{
		void* pp_userdata = (void*)luaL_testudata(l, index, metatable_name);
		return pp_userdata;
	}

	template<typename T>
	static T* to_instance(lua_State* l, int32 index)
	{
		std::string s = typeid(T).name();
		T* pp_userdata = (T*)luaL_checkudata(l, index, s.c_str());
		return pp_userdata;
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
	template<class T>
	concept Integral = std::is_integral<T>::value;
	template<class T>
	concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
	template<class T>
	concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

	template<typename T>
	concept compatible_with_lua_t = true;

	/*
	* std common t => lua t
	* 
	*/
	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, T value)
	{
		basic::push(l, value);
	}

	/*
	* std container => lua table
	* 
	*/
	template<typename T, size_t SIZE> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::array<T, SIZE>& c) noexcept
	{
		// ...
		basic::create_table(l, SIZE, 0);
		// table, ...
		for (size_t _index = 0; _index < SIZE; ++_index)
		{
			push(l, _index + 1);
			// key, table, ...
			push(l, c[_index]);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template <typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::vector<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		for (std::size_t _index = 0; _index < c.size(); ++_index)
		{
			push(l, _index + 1);
			// key, table, ...
			push(l, c[_index]);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::deque<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		for (std::size_t _index = 0; _index < c.size(); ++_index)
		{
			push(l, _index + 1);
			// key, table, ...
			push(l, c[_index]);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::list<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}
	
	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::forward_list<T>& c) noexcept
	{
		// ...
		basic::create_table(l);
		// table, ...
		size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::set<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::unordered_set<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto it = c.cbegin(); it != c.cend(); ++it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::multiset<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *_it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<typename T> requires compatible_with_lua_t<T>
	static void push(lua_State* l, const std::unordered_multiset<T>& c) noexcept
	{
		// ...
		basic::create_table(l, c.size(), 0);
		// table, ...
		std::size_t _index = 1;
		for (auto _it = c.cbegin(); _it != c.cend(); ++_it, ++_index)
		{
			push(l, _index);
			// key, table, ...
			push(l, *_it);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<
		typename key_t, typename value_t,
		typename pred = std::less<key_t>, 
		typename alloc = std::allocator<std::pair<const key_t, value_t>>
	> requires compatible_with_lua_t<key_t> && compatible_with_lua_t<value_t>
	static void push(lua_State* l, const std::map<key_t, value_t>& c) noexcept
	{
		// ...
		basic::create_table(l, 0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(l, pair.first);
			// key, table, ...
			push(l, pair.second);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}

	template<
		typename key_t, typename value_t, 
		typename hasher = std::hash<key_t>,
		typename key_eq = std::equal_to<key_t>,
		typename alloc = std::allocator<std::pair<const key_t, value_t>>
	> requires compatible_with_lua_t<key_t> && compatible_with_lua_t<key_t>
	static void push(lua_State* l, const std::unordered_map<key_t, value_t>& c) noexcept
	{
		// ...
		basic::create_table(l, 0, c.size());
		// table, ...
		for (const auto& pair : c)
		{
			push(l, pair.first);
			// key, table, ...
			push(l, pair.second);
			// value, key, table, ...
			basic::set_table(l, -3);
			// table, ...
		}
	}
	
	/*
	* lua boolean, number, string => 
	* bool,uint8,uint16,uint32,uint64,int8,int16,int32,int64,
	* C-style string, std::string, std::string_view,
	* 
	*/

	template<typename T> requires compatible_with_lua_t<T>
	static std::optional<T> to(lua_State* l, int32 index) noexcept
	{
		if (!basic::is<T>(l, index))
			return std::nullopt;
		return basic::to<T>(l, index);
	}

	/*
	* lua table => 
	* std container<T> requires compatible_with_lua_t<T>
	* 
	*/

	template<typename T, size_t SIZE> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::array<T, SIZE>& c) noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len > SIZE) return false;

		lua_pushnil(l);
		size_t _array_index = 0;
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}

			c[_array_index] = _optional_v.value();
			++_array_index;
		}
		return true;
	}

	template <typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::vector<T>& c) noexcept
	{
		if (!helper::is_table_vectorizable(l, index))
		{
			return false;
		}
		auto _len = basic::raw_len(l, index);
		if (_len < 1)
		{
			return true;
		}
		c.reserve(_len);
		// table, ...
		lua_pushnil(l);
		// key, table, ...
		while (basic::table_next(l, index))
		{
			// value, key, table, ...
			auto _result = to<T>(l, -1);
			if (!_result.has_value())
			{
				basic::pop(l, 2);
				// table, ...
				return false;
			}
			c.push_back(_result.value());
			basic::pop(l, 1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template <typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::deque<T>& c) noexcept
	{
		auto _len = basic::raw_len(l, index);
		if (_len < 1)
		{
			return true;
		}
		// table, ...
		lua_pushnil(l);
		// key, table, ...
		while (basic::table_next(l, index))
		{
			// value, key, table, ...
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				// table, ...
				return false;
			}
			c.push_back(_optional_v.value());
			basic::pop(l, 1);
			// key, table, ...
		}
		// table, ...
		return true;
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::list<T>& c) noexcept
	{	
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.push_back(_optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::forward_list<T>& c) noexcept
	{
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.push_front(_optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::set<T>& c) noexcept
	{
		size_t _len = basic::raw_len(l, index);
		if (_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::multiset<T>& c) noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(l, 1);
		}
		return true; 
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::unordered_set<T>& c)  noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename T> requires compatible_with_lua_t<T>
	static bool to(lua_State* l, int32 index, std::unordered_multiset<T>& c) noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_v = to<T>(l, -1);
			if (!_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.insert(_optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename KT, typename VT> requires compatible_with_lua_t<KT> && compatible_with_lua_t<VT>
	static bool to(lua_State* l, int32 index, std::map<KT, VT>& c) noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_k = to<KT>(l, -1);
			auto _optional_v = to<VT>(l, -1);
			if (!_optional_k.has_value() || !_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.emplace(_optional_k.value(), _optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	template<typename KT, typename VT> requires compatible_with_lua_t<KT>&& compatible_with_lua_t<VT>
	static bool to(lua_State* l, int32 index, std::unordered_map<KT, VT>& c) noexcept
	{
		auto _table_len = basic::raw_len(l, index);
		if (_table_len < 1) return true;

		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			auto _optional_k = to<KT>(l, -2);
			auto _optional_v = to<VT>(l, -1);
			if (!_optional_k.has_value() || !_optional_v.has_value())
			{
				basic::pop(l, 2);
				return false;
			}
			c.emplace(_optional_k.value(), _optional_v.value());
			basic::pop(l, 1);
		}
		return true;
	}

	/*
	* 
	*/

	struct lua_class
	{
		std::string name;
		const luaL_Reg* funcs;
	};

	class lua_vm
	{
	public:

		lua_vm() = default;

		static void register_class(const char* name, const luaL_Reg* funcs)
		{
			std::cout << "register class : " << name << std::endl;
			auto _class = new lua_class();
			_class->name = name;
			_class->funcs = funcs;
			_classes.push_back(_class);
		}

		static void register_functions(const luaL_Reg* funcs)
		{

		}

	private:

		lua_State* _state = nullptr;

		std::unique_ptr<std::thread> _vm_thread = {};

		bool _should_exit = false;

		static std::vector<lua_class*> _classes;

	private:

		void _load_class(const std::string& class_name, const luaL_Reg* funcs)
		{
			const auto _clazz_name = class_name + "_clazz";

			// stack : null
			lua_api::auxiliary::new_metatable(_state, _clazz_name.c_str());
			// stack : metatable
			lua_api::basic::push_value(_state, -1);
			// stack : metatable, metatable
			lua_api::basic::set_field(_state, -2, "__index");
			// stack : metable
			lua_api::auxiliary::set_funcs(_state, funcs, 0);
			lua_api::basic::pop(_state, 1);
			// stack : null

			lua_api::basic::create_table(_state);
			// stack : table
			lua_api::auxiliary::set_metatable(_state, _clazz_name.c_str());
			lua_api::basic::set_global(_state, class_name.c_str());
			// stack : null

			std::cout << "load class : " << class_name << std::endl;
		}

		void _load_libs()
		{
			lua_api::auxiliary::open_libs(_state); // std

			//luaL_requiref(_state, "karamay_RHI", testModelOpen, 0);

			for (auto _class : _classes)
			{
				_load_class(_class->name, _class->funcs);
			}
		}

	public:

		bool start()
		{
			_state = lua_api::auxiliary::new_state();
			if (!_state) return false;
			_load_libs();

			// start dispatcher thread
			/*_vm_thread = std::make_unique<std::thread>(
				[this](int i)
				{
					while (!_should_exit)
					{
						std::cout << "lvm tick" << std::endl;

						int ret = luaL_dofile(_state, "G:\\PrivateRepos\\Karamays\\_KaramayEngine\\karamay_engine_graphics_unit_cmake\\karamay_engine_graphics_unit\\scripts\\blue_freckle\\Test.lua");
						if (ret != 0)
						{
							printf("%s", lua_tostring(_state, -1));
						}

						std::this_thread::sleep_for(std::chrono::milliseconds(100));
					}

					lua_close(_state);
					std::cout << "Lua virtual machine exit." << std::endl;
					_should_exit = false;
				}, 1
			);*/

			std::cout << "Lua virtual machine has been initialized, now is running." << std::endl;
			//_vm_thread->detach();
		}

		void notify_to_exit()
		{
			_should_exit = true;

			while (_should_exit) {}
		}

	public:

		bool do_file(const std::string& path)
		{
			int _result = luaL_dofile(_state, path.c_str());
			switch (_result)
			{
			case LUA_OK(0): std::cout << "no errors." << std::endl; break;
			case LUA_ERRRUN: std::cout << "a runtime error." << std::endl; break;
			case LUA_ERRMEM: std::cout << "memory allocation error.For such errors, Lua does not call the message handler." << std::endl; break;
			case LUA_ERRERR: std::cout << "error while running the message handler." << std::endl; break;
			case LUA_ERRSYNTAX: std::cout << "syntax error during precompilation." << std::endl; break;
			case LUA_YIELD: std::cout << "the thread(coroutine) yields." << std::endl; break;
			case LUA_ERRFILE: std::cout << "a file - related error; e.g., it cannot open or read the file." << std::endl; break;
			default:
				break;
			}
			if (_result != 0)
			{
				printf("%s", lua_tostring(_state, -1));
				return false;
			}

			return true;
		}

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