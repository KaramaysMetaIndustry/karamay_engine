#ifndef LVM_H
#define LVM_H

#include "public/stl.h"
#include "public/_lua.h"

namespace lua_api
{
	//nil, boolean, number, string, function, userdata, thread, and table.
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

		template<typename T> 
		static void push(lua_State* l, T value) 
		{ 
			static_assert(false, "lua_api::basic::push<T> , T is not supported"); 
		}
		template<typename T>
		static void push(lua_State* l, T* value)
		{
			static_assert(std::is_class_v<T>, "must be class or struct pointer");
			lua_pushlightuserdata(l, (void*)value);
		}
		template<typename T>
		static void push(lua_State* l, const T* value)
		{
			static_assert(std::is_class_v<T>, "must be class or struct pointer");
			lua_pushlightuserdata(l, (void*)value);
		}

		template<> 
		static void push(lua_State* l, bool value) { lua_pushboolean(l, static_cast<int>(value)); }
		template<> 
		static void push(lua_State* l, uint8 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, uint16 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, uint32 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, uint64 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, int8 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, int16 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, int32 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, int64 value) { lua_pushinteger(l, static_cast<lua_Integer>(value)); }
		template<> 
		static void push(lua_State* l, float value) { lua_pushboolean(l, static_cast<lua_Number>(value)); }
		template<> 
		static void push(lua_State* l, double value) { lua_pushboolean(l, static_cast<lua_Number>(value)); }
		
		template<> 
		static void push(lua_State* l, char* value)
		{
			lua_pushstring(l, value);
		}
		template<> 
		static void push(lua_State* l, const char* value)
		{
			lua_pushstring(l, value);
		}
		template<> 
		static void push(lua_State* l, std::string& value)
		{
			lua_pushstring(l, value.c_str());
		}
		template<> 
		static void push(lua_State* l, const std::string value)
		{
			lua_pushstring(l, value.c_str());
		}
		template<>
		static void push(lua_State* l, const std::string& value)
		{
			lua_pushstring(l, value.c_str());
		}
		template<> 
		static void push(lua_State* l, std::string&& value)
		{
			lua_pushstring(l, value.c_str());
		}
		
		struct lua_nil_t {};
		template<>
		static void push(lua_State* l, lua_nil_t nil) { lua_pushnil(l); }
		struct lua_table_t {};
		template<>
		static void push(lua_State* l, lua_table_t table)
		{
			lua_pushglobaltable(l);
		}
		struct lua_thread_t {};
		template<>
		static void push(lua_State* l, lua_thread_t thread) { lua_pushthread(l); }
		
		static void push_value(lua_State* l, int32 index)
		{
			lua_pushvalue(l, index);
		}
		

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


		template<typename T> 
		static T to(lua_State* l, int32 index) { static_assert(false, "to<T> , T is not supported"); return T(); }
		template<> 
		static int8 to<int8>(lua_State* l, int32 index) { return static_cast<int8>(lua_tointeger(l, index)); }
		template<> 
		static int16 to<int16>(lua_State* l, int32 index) { return static_cast<int16>(lua_tointeger(l, index)); }
		template<> 
		static int32 to<int32>(lua_State* l, int32 index) { return static_cast<int32>(lua_tointeger(l, index)); }
		template<> 
		static int64 to<int64>(lua_State* l, int32 index) { return static_cast<int64>(lua_tointeger(l, index)); }
		template<> 
		static uint8 to<uint8>(lua_State* l, int32 index) { return static_cast<uint8>(lua_tointeger(l, index)); }
		template<> 
		static uint16 to<uint16>(lua_State* l, int32 index) { return static_cast<uint16>(lua_tointeger(l, index)); }
		template<> 
		static uint32 to<uint32>(lua_State* l, int32 index) { return static_cast<uint32>(lua_tointeger(l, index)); }
		template<> 
		static uint64 to<uint64>(lua_State* l, int32 index) { return static_cast<uint64>(lua_tointeger(l, index)); }
		template<> 
		static float to<float>(lua_State* l, int32 index) { return static_cast<float>(lua_tonumber(l, index)); }
		template<> 
		static double to<double>(lua_State* l, int32 index) { return static_cast<double>(lua_tonumber(l, index)); }
		template<> 
		static bool to<bool>(lua_State* l, int32 index) { return static_cast<bool>(lua_toboolean(l, index)); }
		template<> 
		static std::string to<std::string>(lua_State* l, int32 index) { return std::string(lua_tostring(l, index)); }
		template<> 
		static void* to<void*>(lua_State* l, int32 index) { return lua_touserdata(l, index); }
		template<> 
		static const void* to<const void*>(lua_State* l, int32 index) { return static_cast<const void*>(lua_touserdata(l, index)); }
		template<> 
		static lua_CFunction to<lua_CFunction>(lua_State* l, int32 index) { return lua_tocfunction(l ,index); }
		
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

		/*
		* _G : global table
		* Pops a value from the stack and sets it as the new value of global name.
		*/
		static void set_global(lua_State* l, const char* name)
		{
			lua_setglobal(l, name);
		}

		static void set_allocf(lua_State* L, lua_Alloc f, void* ud)
		{
			lua_setallocf(L, f, ud);
		}

		static lua_t type(lua_State* l, int32 index) 
		{ 
			return static_cast<lua_t>(lua_type(l, index));
		}

		static bool is_type(lua_State* l, int32 index, lua_t t)
		{
			return t == type(l, index);
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

	// vector, list, forward_list,  deque,
	// set, unordered_set, map, unordered_map
	// stack, queue

	// Containerizable
	static bool is_table_vectorizable(lua_State* l, int32 index)
	{
		if(!basic::is_type(l, index, lua_t::TABLE)) return false;

		return  true;
	}

	template <typename T>
	static bool vector_from_table(lua_State* l, int32 index, std::vector<T>& container) 
	{
		if (!is_table_vectorizable(l, index)) return false;
		size_t len = basic::raw_len(l, index);
		container.reserve(len);

		lua_pushnil(l);
		while (basic::table_next(l, index)) 
		{
			container.push_back(basic::to<T>(l, -1));
			lua_pop(l, 1);
		}
		return true;
	}

	template <typename T>
	static bool push(lua_State* l, const std::vector<T>& container)
	{
		basic::create_table(l);
		//basic::create_table(l, 10, 10);
		// table
		for (size_t i = 0; i < container.size(); ++i) {
			lua_api::basic::push(l, i + 1);
			// key, table
			lua_api::basic::push(l, container.at(i));
			// value, key, table
			lua_api::basic::set_table(l, -3);
			// table
		}
		return true;
	}

	template<typename T>
	static bool push(lua_State* l, const std::list<T>& container)
	{


		return true;
	}

	template<typename T>
	static bool push(lua_State* l, const std::set<T>& container)
	{

		return true;
	}

	template<typename KT, typename VT>
	static bool push(lua_State* l, const std::unordered_map<KT, VT>& container)
	{
		basic::create_table(l);
		// table
		for (const auto& pair : container)
		{
			lua_api::basic::push(l, pair.first);
			// key, table
			lua_api::basic::push(l, pair.second);
			// value, key, table
			lua_api::basic::set_table(l, -3);
			// table
		}
		return true;
	}

	template<typename KT, typename VT>
	static bool push(lua_State* l, const std::unordered_multimap<KT, VT>& container)
	{

		return true;
	}
	

	template<typename T>
	static bool list_from_table(lua_State* l, int32 index, std::list<T>& container)
	{
		//if (!is_table_vectorizable(l, index)) return false;
		size_t len = basic::raw_len(l, index);
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			printf("%s - %s\n",
				lua_typename(l, lua_type(l, -2)),
				lua_typename(l, lua_type(l, -1)));
			container.push_back(basic::to<T>(l, -1));
			lua_pop(l, 1);
		}
		return true;
	}

	template<typename T>
	static bool set_from_table(lua_State* l, int32 index, std::set<T>& container)
	{
		size_t len = basic::raw_len(l, index);
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			container.insert(basic::to<T>(l, -1));
			lua_pop(l, 1);
		}
		return true;
	}

	template<typename KT, typename VT>
	static bool umap_from_table(lua_State* l, int32 index, std::unordered_map<KT, VT>& container) 
	{
		size_t len = basic::raw_len(l, index);
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			container.emplace(basic::to<KT>(l, -2), basic::to<VT>(l, -1));
			lua_pop(l, 1);
		}
		return true;
	}

	template<typename KT, typename VT>
	static bool umap_from_table(lua_State* l, int32 index, std::unordered_multimap<KT, VT>& container)
	{
		size_t len = basic::raw_len(l, index);
		lua_pushnil(l);
		while (basic::table_next(l, index))
		{
			container.emplace(basic::to<KT>(l, -2), basic::to<VT>(l, -1));
			lua_pop(l, 1);
		}
		return true;
	}



	static void* to_userdata_fast(lua_State* L, int32 stack_index, bool two_level_ptr)
	{
		bool _two_level_ptr = false;
		void* _userdata = nullptr;

	}

	static void* to_userdata(lua_State* L, int32 stack_index, bool* two_level_ptr)
	{
		if (stack_index < 0 && stack_index > LUA_REGISTRYINDEX)
		{
			int32 _top = basic::top_index(L);
			stack_index += _top + 1;
		}

		void* _userdata = nullptr;
		bool _two_level_ptr = false, _class_metatable = false;

		lua_t _type = basic::type(L, stack_index);
		switch (_type)
		{
		case lua_t::TABLE:
		{
			basic::push(L, "Object");
			_type = basic::raw_get(L, stack_index);
			if (_type == lua_t::USERDATA)
			{
				_userdata = basic::to<void*>(L, -1);
			}
			else {
				basic::pop(L, 1);
				basic::push(L, "ClassDesc");
				_type = basic::raw_get(L, stack_index);
				if (_type == lua_t::LIGHTUSERDATA)
				{
					_userdata = basic::to<void*>(L, -1);
					_class_metatable = true;
				}
			}
			_two_level_ptr = true;
			basic::pop(L, 1);
		}
		break;
		case lua_t::USERDATA: 
		{
		}
		break;
		default:
			break;
		}

		void** _instance_ptr = (void**)lua_touserdata(L, stack_index);
		if (!_instance_ptr || !(*_instance_ptr))
		{
			luaL_argcheck(L, false, stack_index, "input val test, invalid user data");
			return nullptr;
		}
		return (void*)*_instance_ptr;
	}

	static void* to_cpp_instance(lua_State* L, int32 stack_index)
	{
		bool _two_level_ptr = false;
		void* _userdata = to_userdata(L, stack_index, &_two_level_ptr);
		if (_userdata)
		{
			return _two_level_ptr ? *((void**)_userdata) : _userdata;
		}
		return nullptr;
	}

	static void* to_cpp_instance(lua_State* L, int32 stack_index, const char* metatable_name)
	{
		//void** pp_userdata = (void**)luaL_checkudata(L, stack_index, metatable_name);
		//return (void*)*pp_userdata;
		void* pp_userdata = (void*)luaL_checkudata(L, stack_index, metatable_name);
		return pp_userdata;
	}

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